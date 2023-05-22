#include "../include/main.h"

PID::PID() {}

PID::PID(double init_kP, double init_kI, double init_kD, bool do_loopP, bool do_loopI,
        bool do_loopD) {
    kP = init_kP;
    kI = init_kI;
    kD = init_kD;

    do_p = do_loopP;
    do_i = do_loopI;
    do_d = do_loopD;

    error = 0;
    sum = 0;
    prev_error = 0;
    deriv = 0;

    do_print_val = true;
}

double PID::pid_adjust(double setpoint, double current_value) {
    error = setpoint - current_value;
    sum += error;
    deriv = error - prev_error;
    prev_error = error;

    if (do_p) kP = 0;
    if (do_i) sum = 0;
    if (do_d) deriv = 0;

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



void drive_straight_a(float dist, float max_vel, float accel) {
    PID pid_drive_r (0, 0, 0, true, false, true);
    PID pid_drive_l (0, 0, 0, true, false, true);
    PID pid_dir (0, 0, 0, true, false, true);
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
    
    int dir_mod = 0;

    if (dist > 0) dir_mod = 1;
    if (dist < 0) dir_mod = -1;

    while (vel >= 0) {
        current_l = POS_DRIVE_L - start_pos_l;
        current_r = POS_DRIVE_R - start_pos_r;
        // Increment velocity
        if (std::abs(pos) + stop_dist(vel, accel) >= std::abs(dist)) vel -= accel / tps;    // handles forward and backward
        else if (vel < max_vel) vel += accel / tps;
        else vel = max_vel;

        pos += vel * dir_mod / tps;

        r_pid_adjustment = pid_drive_r.pid_adjust(pos, current_r * DRIVE_REV__IN);
        l_pid_adjustment = pid_drive_l.pid_adjust(pos, current_l * DRIVE_REV__IN);
        dir_pid_adjustment = pid_dir.pid_adjust(current_heading, ROTATION * GYRO_CORRECTION);
        vel_rpm = vel  / DRIVE_REV__IN * 60;
    }
}
