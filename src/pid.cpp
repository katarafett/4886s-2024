#include "../include/main.h"

PID::PID() {}

PID::PID(double init_kP, double init_kI, double init_kD) {
    kP = init_kP;
    kI = init_kI;
    kD = init_kD;

    do_p = (kP != 0);
    do_i = (kI != 0);
    do_d = (kD != 0);

    error = 0;
    sum = 0;
    prev_error = 0;
    deriv = 0;

    do_print_val = true;
}

double PID::pid_adjust(double setpoint, double current_value) {
    error = setpoint - current_value;
    if (do_i) sum += error;
    if (do_d) deriv = error - prev_error;
    prev_error = error;

    return (error * kP) + (sum * kI) + (deriv * kD);
}

void PID::tune_kP(float stick_mod) {
    kP += LEFT_STICK_Y * stick_mod;
    printf("kP: %lf\n", kP);
}

void PID::tune_kI(float stick_mod) {
    kI += RIGHT_STICK_Y * stick_mod;
    printf("kI: %lf\n", kI);
}

void PID::tune_kD(float stick_mod) {
    kD += RIGHT_STICK_X * stick_mod;
    printf("kD: %lf\n", kD);
}

float PID::get_const(char constant) {
    if (constant == 'p')
        return this->kP;
    if (constant == 'i')
        return this->kI;
    if (constant == 'd')
        return this->kD;
    else return '\0';
}
 
void drive_straight(float inches, float target_ips, float ips_per_sec) {
    PID pid_drive_l (DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID pid_drive_r (DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID pid_dir (DIR_KP, DIR_KI, DIR_KD);

    float ips = 0, pos = 0;
    float pos_start_l = POS_DRIVE_L, pos_start_r = POS_DRIVE_R;
    float pos_l, pos_r;

    // adjusts velocity for positive/negative distances
    float dir_mod = (inches > 0) ? 1 : -1;

    float pid_adjustment_l;
    float pid_adjustment_r;
    float pid_adjustment_dir;

    int target_time = sands_of_time.time(vex::msec);

    float vel_rpm;

    while (ips >= 0) {
        // Handles getting to speed
        if (std::abs(pos) + stop_dist(ips, ips_per_sec) >= std::abs(inches))
            ips -= ips_per_sec / 50;    // 50 hz
        else if (ips < target_ips)
            ips += target_ips / 50;
        else ips = target_ips;

        // Find expected position
        pos += ips / 50 * dir_mod;    // divide by 50 bc loop occurs 50 times a second; dir_mod adjusts for fwd/bwd

        // Update actual positions
        pos_l = POS_DRIVE_L - pos_start_l;
        pos_r = POS_DRIVE_R - pos_start_r;

        // Maintain speed
        pid_adjustment_l = pid_drive_l.pid_adjust(pos, pos_l);
        pid_adjustment_r = pid_drive_r.pid_adjust(pos, pos_r);
        pid_adjustment_dir = pid_dir.pid_adjust(target_heading, ROTATION * GYRO_CORRECTION);

        vel_rpm = ips / DRIVE_REV__IN * 60;

        drive_l.spin(DIR_FWD, dir_mod * vel_rpm + pid_adjustment_l + pid_adjustment_dir, VEL_RPM);
        drive_r.spin(DIR_FWD, dir_mod * vel_rpm + pid_adjustment_r - pid_adjustment_dir, VEL_RPM);

        target_time += 20;
        while (sands_of_time.time(vex::msec) < target_time);   // wait for next iteration;
    }
    drive_l.stop(vex::brakeType::coast);
    drive_r.stop(vex::brakeType::coast);
}

void drive_turn(float degrees, float outer_radius, float target_ips, float ips_per_sec, bool reversed) {
    target_heading += degrees;      // update target heading

    PID pid_drive_l (DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID pid_drive_r (DRIVE_KP, DRIVE_KI, DRIVE_KD);

    float pid_adjustment_l;
    float pid_adjustment_r;

    float ips = 0;
    float outer_vel_rpm, inner_vel_rpm;
    float outer_pos = 0, inner_pos;    // expected distance that outer side has travelled
    float pos_start_l = POS_DRIVE_L, pos_start_r = POS_DRIVE_R;     // start positions
    float pos_l, pos_r;     // current positions for each drive side
    
    float degrees_remaining;
    
    float inner_radius = outer_radius - WHEEL_TO_WHEEL_DIST;
    float radius_ratio = inner_radius / outer_radius;

    // adjusts for different outer wheel sides
    int dir_mod = (degrees > 0) ? 1 : -1;

    int target_time = sands_of_time.time(vex::msec);

    while (ips >= 0) {
        // Update values
        pos_l = POS_DRIVE_L - pos_start_l;
        pos_r = POS_DRIVE_R - pos_start_r;

        degrees_remaining = target_heading - ROTATION * GYRO_CORRECTION;

        // Handle acceleration
        if (std::abs(degrees_remaining / RAD__DEG * outer_radius) - stop_dist(ips, ips_per_sec) <= 0)
            ips -= ips_per_sec / 50.0;
        else if (ips < target_ips)
            ips += ips_per_sec / 50.0;   // 50 cycles per second
        else ips = target_ips; master.rumble(".");

        // Translate ips to rpm
        outer_vel_rpm = ips / DRIVE_REV__IN * 60;
        inner_vel_rpm = outer_vel_rpm * radius_ratio;

        // Track position
        outer_pos += ips / 50;    // 50 cycles per second
        inner_pos = outer_pos * radius_ratio;


        // Get PID adjustments
        if ((reversed && degrees > 0) || (!reversed && !(degrees > 0))) {      // left is inner side
            pid_adjustment_l = -1 * pid_drive_l.pid_adjust(inner_pos, pos_l);
            pid_adjustment_r = pid_drive_r.pid_adjust(outer_pos, pos_r);

            drive_l.spin(DIR_FWD, dir_mod * inner_vel_rpm + pid_adjustment_l, VEL_RPM);
            drive_r.spin(DIR_FWD, dir_mod * outer_vel_rpm + pid_adjustment_r, VEL_RPM);
        }
        else {      // right is inner side
            pid_adjustment_l = pid_drive_l.pid_adjust(outer_pos, pos_l);
            pid_adjustment_r = -1 * pid_drive_r.pid_adjust(inner_pos, pos_r);

            drive_l.spin(DIR_FWD, dir_mod * outer_vel_rpm + pid_adjustment_l, VEL_RPM);
            drive_r.spin(DIR_FWD, dir_mod * inner_vel_rpm + pid_adjustment_r, VEL_RPM);
        }

        // Exit if we're past the desired angle
        if (degrees_remaining * dir_mod < 0)
            break;

        target_time += 20;
        while (sands_of_time.time(vex::msec) < target_time);    // wait for next cycle
    }
    drive_l.stop(vex::brakeType::coast);
    drive_r.stop(vex::brakeType::coast);
}
