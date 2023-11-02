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
 
void drive(float inches, float target_ips, float ips_per_sec) {
    PID pid_drive_l (DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID pid_drive_r (DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID pid_dir (DIR_KP, DIR_KI, DIR_KD);

    float avg_pos = 0, ips = 0;
    float pos_start_l = POS_DRIVE_L, pos_start_r = POS_DRIVE_R;
    float pos_l, pos_r;
    float time = sands_of_time.time(vex::msec);

    // adjusts velocity for positive/negative distances
    float dir_mod = (inches > 0) ? 1 : -1;

    float pid_adjustment_l;
    float pid_adjustment_r;
    float pid_adjustment_dir;

    float target_time = 0;

    float vel_rpm;

    while (ips >= 0) {
        // Handles getting to speed
        if (ips >= target_ips)
            ips = target_ips;
        else if (std::abs(pos) + stop_dist(ips, ips_per_sec) >= std::abs(inches))
            ips -= ips_per_sec;
        else ips += ips_per_sec;

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

        drive_l.spin(DIR_FWD, vel_rpm + pid_adjustment_l + pid_adjustment_dir, VEL_RPM);
        drive_r.spin(DIR_FWD, vel_rpm + pid_adjustment_r - pid_adjustment_dir, VEL_RPM);

        target_time += 20;
        while (sands_of_time.time(vex::msec) < target_time);    // wait for next iteration;
}

void drive_straight_a(float dist, float max_vel, float accel) {
    // PID objects (?) for drive sides and steering control
    PID pid_drive_l (drive_pid.kP, DRIVE_KI, DRIVE_KD);
    PID pid_drive_r (drive_pid.kP, DRIVE_KI, DRIVE_KD);
    PID pid_dir (DIR_KP, DIR_KI, DIR_KD);

    float r_pid_adjustment;
    float l_pid_adjustment;
    float dir_pid_adjustment;
    float vel_rpm;

    float vel = 0, pos = 0;
    float start_pos_l = POS_DRIVE_L;
    float start_pos_r = POS_DRIVE_R;
    float current_l, current_r;
    int tps = 50;
    int current_time = sands_of_time.time(vex::msec);
    
    int dir_mod = 0; // directional modifier

    if (dist > 0)
        dir_mod = 1;
    if (dist < 0)
        dir_mod = -1;

    while (vel >= 0) {
        current_l = POS_DRIVE_L - start_pos_l;
        current_r = POS_DRIVE_R - start_pos_r;
        // Increment velocity
        if (std::abs(pos) + stop_dist(vel, accel) >= std::abs(dist))
            vel -= accel / tps;    // handles forward and backward
        else if (vel < max_vel)
            vel += accel / tps;
        else vel = max_vel;

        pos += vel * dir_mod / tps;

        r_pid_adjustment = pid_drive_r.pid_adjust(pos, current_r * DRIVE_REV__IN);
        l_pid_adjustment = pid_drive_l.pid_adjust(pos, current_l * DRIVE_REV__IN);
        // dir_pid_adjustment = pid_dir.pid_adjust(current_heading, ROTATION * GYRO_CORRECTION);
        vel_rpm = vel  / DRIVE_REV__IN * 60;
    }
}
