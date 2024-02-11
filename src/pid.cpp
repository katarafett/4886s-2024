#include "../include/main.h"
#include "stddefs.h"
#include "vex_global.h"
#include "vex_units.h"

PID::PID() {}

PID::PID(double init_kP, double init_kI, double init_kD) {
    kP = init_kP;
    kI = init_kI;
    kD = init_kD;

    error = 0;
    sum = 0;
    prev_error = 0;
    deriv = 0;

    // For debug and tuning
    do_print_val = false;
}

double PID::pid_adjust(double setpoint, double current_value) {
    error = setpoint - current_value;
    if (kI != 0) sum += error;
    deriv = error - prev_error;
    prev_error = error;

    return (error * kP) + (sum * kI) + (deriv * kD);
}

void PID::tune_kP(float stick_mod) {
    kP += (BTN_UP.pressing() - BTN_DOWN.pressing()) * stick_mod;
    printf("kP: %lf\n", kP);
    B_SCRN.setCursor(3, 4);
    B_SCRN.print("kP: %lf", kP);
}

void PID::tune_kI(float stick_mod) {
    kI += (BTN_RIGHT.pressing() - BTN_LEFT.pressing()) * stick_mod;
    printf("kI: %lf\n", kI);
    B_SCRN.setCursor(5, 4);
    B_SCRN.print("kI: %lf", kI);
}

void PID::tune_kD(float stick_mod) {
    kD += (BTN_X.pressing() - BTN_B.pressing()) * stick_mod;
    printf("kD: %lf\n", kD);
    B_SCRN.setCursor(7, 4);
    B_SCRN.print("kD: %lf", kD);
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
 
void drive_straight(float inches, float target_ips, float ips_per_sec, bool do_decel) {
    inches *= 1.2;
    printf("enter drive straight\n");
    drive_r.stop(vex::brakeType::coast);
    drive_l.stop(vex::brakeType::coast);

    PID pid_drive_l = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID pid_drive_r = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID pid_dir = PID(DIR_KP, DIR_KI, DIR_KD);

    float ips = 0, pos = 0;
    float pos_start_l = POS_DRIVE_L, pos_start_r = POS_DRIVE_R;
    float pos_l, pos_r;

    // adjusts velocity for positive/negative distances
    float dir_mod = (inches > 0) ? 1 : -1;

    float pid_adjustment_l;
    float pid_adjustment_r;
    float pid_adjustment_dir;

    float vel_rpm;

    while (ips >= 0 && std::abs(POS_DRIVE_L - pos_start_l) < std::abs(inches)) {
        // Handles getting to speed
        if (std::abs(pos) + stop_dist(ips, ips_per_sec) >= std::abs(inches) && do_decel)
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
        wait(20, vex::msec);
    }
    if (do_decel) {
        drive_r.stop(vex::brakeType::brake);
        drive_l.stop(vex::brakeType::brake);
    }
    else {
        drive_r.stop(vex::brakeType::coast);
        drive_l.stop(vex::brakeType::coast);
    }
}

// TODO: get rid of reversed and just use a negative outer_radius
/* Currently bugged
 * can't arc backwards
 * to turn right, degrees > 0 and reversed = false
 * to turn left, degrees < 0 and reversed = true
 */
void drive_turn(float degrees, float outer_radius, float target_ips, float ips_per_sec, bool reversed) {
    target_heading += degrees;      // update target heading

    PID pid_drive_l = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID pid_drive_r = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);

    float pid_adjustment_l;
    float pid_adjustment_r;

    float ips = 0;
    float outer_vel_rpm, inner_vel_rpm;
    float outer_pos = 0, inner_pos;    // expected distance that outer side has travelled
    float pos_start_l = POS_DRIVE_L, pos_start_r = POS_DRIVE_R;     // start positions
    float pos_l, pos_r;     // current positions for each drive side
    
    float degrees_remaining;
    
    // Does what it says. Also, implicity sets inner side negative if turning in place
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
        if (std::abs(degrees_remaining / RAD__DEG * outer_radius) - stop_dist(ips, ips_per_sec) <= 0) {
            ips -= ips_per_sec / 50.0;
        }
        else if (ips < target_ips)
            ips += ips_per_sec / 50.0;   // 50 cycles per second
        else ips = target_ips;

        // Translate ips to rpm
        outer_vel_rpm = ips / DRIVE_REV__IN * 60 * ((reversed) ? -1 : 1);         // fixes the stupid thing;
        inner_vel_rpm = outer_vel_rpm * radius_ratio * ((reversed) ? -1 : 1);     // try not to touch

        // Track position
        outer_pos += ips / 50;    // 50 cycles per second
        inner_pos = outer_pos * radius_ratio;


        // Get PID adjustments
        if ((reversed && degrees > 0) || (!reversed && !(degrees > 0))) {      // left is inner side
            pid_adjustment_l = -1 * pid_drive_l.pid_adjust(inner_pos, pos_l);
            pid_adjustment_r = pid_drive_r.pid_adjust(outer_pos, pos_r);

            drive_l.spin(DIR_FWD, inner_vel_rpm + pid_adjustment_l, VEL_RPM);
            drive_r.spin(DIR_FWD, outer_vel_rpm + pid_adjustment_r, VEL_RPM);
        }
        else {      // right is inner side
            pid_adjustment_l = pid_drive_l.pid_adjust(outer_pos, pos_l);
            pid_adjustment_r = -1 * pid_drive_r.pid_adjust(inner_pos, pos_r);

            drive_l.spin(DIR_FWD, outer_vel_rpm + pid_adjustment_l, VEL_RPM);
            drive_r.spin(DIR_FWD, inner_vel_rpm + pid_adjustment_r, VEL_RPM);
        }

        // Exit if we're past the desired angle
        if (degrees_remaining * dir_mod < 0)
            break;
        
        target_time += 20;
        while (sands_of_time.time(vex::msec) < target_time);    // wait for next cycle
    }
    drive_l.stop(vex::brakeType::brake);
    drive_r.stop(vex::brakeType::brake);
}

// In testing
void drive_linear(float inches, float max_ips, float ips_per_sec, bool do_decel) {
    const int TPS = 50;     // ticks per second

    // Initialize PID objects
    PID pid_r = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID pid_l = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);      // needs a seperate controller because they'll rack up error at different rates
    PID pid_dir = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
    float pid_r_adj, pid_l_adj, pid_dir_adj;

    // Various positions in inches
    float start_pos_r = POS_DRIVE_R;
    float start_pos_l = POS_DRIVE_L;
    float current_pos_r = POS_DRIVE_R - start_pos_r;
    float current_pos_l = POS_DRIVE_L - start_pos_l;
    float avg_pos = (current_pos_r + current_pos_l) / 2.0;

    // Velocities
    float target_vel_r = VEL_DRIVE_R;
    float target_vel_l = VEL_DRIVE_L;
    float r_vel_rpm, l_vel_rpm;

    // Direction of travel - 1 for fwd, -1 for bwd
    int dir_mod = (inches > 0) ? 1 : -1;

    float start_time = sands_of_time.time(vex::msec);
    float next_cycle = start_time;      // tracks time between cycles

    while (std::abs(avg_pos) < std::abs(inches)) {      // cuts if we've reached target position
        // Update positions
        current_pos_r = POS_DRIVE_R - start_pos_r;
        current_pos_l = POS_DRIVE_L - start_pos_l;
        avg_pos = (current_pos_r + current_pos_l) / 2.0;

        // Handle accelerations
        handle_accel(current_pos_r, inches, &target_vel_r, max_ips, ips_per_sec, TPS, do_decel);
        handle_accel(current_pos_l, inches, &target_vel_l, max_ips, ips_per_sec, TPS, do_decel);

        // Get PID values
        pid_r_adj = pid_r.pid_adjust(target_vel_r, VEL_DRIVE_R);
        pid_l_adj = pid_l.pid_adjust(target_vel_l, VEL_DRIVE_L);
        pid_dir_adj = pid_dir.pid_adjust(target_heading, ROTATION * GYRO_CORRECTION);

        r_vel_rpm = target_vel_r / DRIVE_REV__IN * 60;
        l_vel_rpm = target_vel_l / DRIVE_REV__IN * 60;

        // Move drive
        drive_r.spin(DIR_FWD, dir_mod * r_vel_rpm + pid_r_adj + pid_dir_adj, VEL_RPM);
        drive_l.spin(DIR_FWD, dir_mod * l_vel_rpm + pid_l_adj - pid_dir_adj, VEL_RPM);

        // Wait for next cycle
        next_cycle += 1000.0 / TPS;
        while (sands_of_time.time(vex::msec) < next_cycle);     // wait for next cycle
    }
    if (do_decel) {
        drive_l.stop(vex::brakeType::brake);
        drive_r.stop(vex::brakeType::brake);
    }
    else {
        drive_l.stop(vex::brakeType::coast);
        drive_r.stop(vex::brakeType::coast);
    }
}

void drive_arc(float degrees, float outer_radius, float max_ips, float ips_per_sec, bool do_decel, bool reversed) {
    target_heading += degrees;

    vex::motor_group outer_drive;
    vex::motor_group inner_drive;

    // Check which side of the drive will be on the inside of the turn
    // If moving backward and turning left or going forward and turning right
    if ((reversed && degrees > 0) || (!reversed && !(degrees > 0))) {
        outer_drive = vex::motor_group(drive_rf, drive_rb, drive_rt);
        inner_drive = vex::motor_group(drive_lf, drive_lb, drive_lt);
    }
    else {
        outer_drive = vex::motor_group(drive_lf, drive_lb, drive_lt);
        inner_drive = vex::motor_group(drive_rf, drive_rb, drive_rt);
    }

    PID pid_drive_o = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID pid_drive_i = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
    float pid_adjustment_o;
    float pid_adjustment_i;

    float outer_ips = 0;
    float outer_vel_rpm, inner_vel_rpm;
    float pos_start_o = outer_drive.position(ROT_REV) * DRIVE_REV__IN;
    float pos_start_i = inner_drive.position(ROT_REV) * DRIVE_REV__IN;     // start positions

    float outer_pos, inner_pos;
    float trg_outer_pos = 0, trg_inner_pos;     // distance sides have travelled along circle

    float degrees_remaining = target_heading - ROTATION * GYRO_CORRECTION;

    float inner_radius = outer_radius - WHEEL_TO_WHEEL_DIST;
    float radius_ratio = inner_radius / outer_radius;

    while (std::abs(degrees_remaining) > 0) {
        // Update values
        outer_pos = outer_drive.position(ROT_REV) * DRIVE_REV__IN - pos_start_o;
        inner_pos = inner_drive.position(ROT_REV) * DRIVE_REV__IN - pos_start_i;

        degrees_remaining = target_heading - ROTATION * GYRO_CORRECTION;

        // Handle acceleration
        if (std::abs(degrees_remaining / RAD__DEG * outer_radius) - stop_dist(outer_ips, ips_per_sec) <= 0 && do_decel)
            outer_ips -= ips_per_sec / 50.0;
        else if (outer_ips < max_ips)
            outer_ips += ips_per_sec / 50.0;   // 50 cycles per second
        else outer_ips = max_ips;

        trg_outer_pos += outer_ips / 50;
        trg_inner_pos = trg_outer_pos * radius_ratio;

        outer_vel_rpm = outer_ips / DRIVE_REV__IN * 60 * ((reversed) ? -1 : 1);
        inner_vel_rpm = outer_vel_rpm * radius_ratio * ((reversed) ? -1 : 1);

        pid_adjustment_i = 1 * pid_drive_i.pid_adjust(trg_inner_pos, inner_pos);
        pid_adjustment_o = 1 * pid_drive_o.pid_adjust(trg_outer_pos, outer_pos);

        inner_drive.spin(DIR_FWD, inner_vel_rpm + pid_adjustment_i, VEL_RPM);
        outer_drive.spin(DIR_FWD, outer_vel_rpm + pid_adjustment_o, VEL_RPM);

        vex::wait(20, vex::msec);
    }
    if (do_decel)
        drive_full.stop(vex::brake);
    else drive_full.stop(vex::coast);
}

void turn_pid (float degrees, float ratio, int direction) {
    target_heading += degrees;
    PID drive_pid = PID(turn_kp_l, turn_ki_l, turn_kd_l);

    float speed_l;
    float speed_r;

    int time_still = 0;
    while (1) {
        if (time_still >= 80)
            break;
        if (within_range(ROTATION * GYRO_CORRECTION, target_heading, 3))
            time_still += 20;
        else
            time_still = 0;

        speed_l = drive_pid.pid_adjust(target_heading, ROTATION * GYRO_CORRECTION) * direction;
        speed_r = speed_l * ratio;

        // Limit to max speed
        if (speed_l > 12)
            speed_l = 12;
        else if (speed_l < -12)
            speed_l = -12;
        if (speed_r > 12 * std::abs(ratio))
            speed_r = 12 * std::abs(ratio);
        else if (speed_r < -12 * std::abs(ratio))
            speed_r = -12 * std::abs(ratio);

        drive_l.spin(DIR_FWD, speed_l, VLT_VLT);
        drive_r.spin(DIR_FWD, speed_r, VLT_VLT);
        wait(20, vex::msec);
    }
}

void straight_pid (float dist) {
    PID drive_pid = PID(0, 0, 0);
}
