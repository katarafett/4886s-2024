#include "../include/main.h"
#include "stddefs.h"

void drive_straight(float inches, float target_ips, float ips_per_sec, bool do_decel) {
    const int TICKS_PER_SEC = 50;
    const int MSEC_PER_TICK = 1000.0 / 20.0;

    drive_r.stop(vex::brakeType::coast);
    drive_l.stop(vex::brakeType::coast);

    PID pid_drive_l = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID pid_drive_r = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID pid_dir = PID(DIR_KP, DIR_KI, DIR_KD);

    float ips = 0, pos = 0;
    float pos_start_l = pos_drive_l(), pos_start_r = POS_DRIVE_R;
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
            ips -= ips_per_sec / 50; // 50 hz
        else if (ips < target_ips)
            ips += target_ips / 50;
        else
            ips = target_ips;

        // Find expected position
        pos += ips / 50 * dir_mod; // divide by 50 bc loop occurs 50 times a second; dir_mod adjusts for fwd/bwd

        // Update actual positions
        pos_l = POS_DRIVE_L - pos_start_l;
        pos_r = POS_DRIVE_R - pos_start_r;

        // Maintain speed
        pid_adjustment_l = pid_drive_l.adjust(pos, pos_l);
        pid_adjustment_r = pid_drive_r.adjust(pos, pos_r);
        pid_adjustment_dir = pid_dir.adjust(target_heading, ROTATION * GYRO_CORRECTION);

        vel_rpm = ips / DRIVE_REV__IN * 60;

        drive_l.spin(DIR_FWD, dir_mod * vel_rpm + pid_adjustment_l + pid_adjustment_dir, VEL_RPM);
        drive_r.spin(DIR_FWD, dir_mod * vel_rpm + pid_adjustment_r - pid_adjustment_dir, VEL_RPM);
        wait(20, vex::msec);
    }
    if (do_decel) {
        drive_r.stop(vex::brakeType::brake);
        drive_l.stop(vex::brakeType::brake);
    } else {
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
    target_heading += degrees; // update target heading

    PID pid_drive_l = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID pid_drive_r = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);

    float pid_adjustment_l;
    float pid_adjustment_r;

    float ips = 0;
    float outer_vel_rpm, inner_vel_rpm;
    float outer_pos = 0, inner_pos;                             // expected distance that outer side has travelled
    float pos_start_l = POS_DRIVE_L, pos_start_r = POS_DRIVE_R; // start positions
    float pos_l, pos_r;                                         // current positions for each drive side

    float degrees_remaining;

    // Does what it says. Also, implicity sets inner side negative if turning in place
    float inner_radius = outer_radius - WHEEL_TO_WHEEL_DIST;
    float radius_ratio = inner_radius / outer_radius;

    // adjusts for different outer wheel sides
    int dir_mod = (degrees > 0) ? 1 : -1;


    while (ips >= 0) {
        // Update values
        pos_l = POS_DRIVE_L - pos_start_l;
        pos_r = POS_DRIVE_R - pos_start_r;

        degrees_remaining = target_heading - ROTATION * GYRO_CORRECTION;

        // Handle acceleration
        if (std::abs(degrees_remaining / RAD__DEG * outer_radius) - stop_dist(ips, ips_per_sec) <= 0) {
            ips -= ips_per_sec / 50.0;
        } else if (ips < target_ips)
            ips += ips_per_sec / 50.0; // 50 cycles per second
        else
            ips = target_ips;

        // Translate ips to rpm
        outer_vel_rpm = ips / DRIVE_REV__IN * 60 * ((reversed) ? -1 : 1);     // fixes the stupid thing;
        inner_vel_rpm = outer_vel_rpm * radius_ratio * ((reversed) ? -1 : 1); // try not to touch

        // Track position
        outer_pos += ips / 50; // 50 cycles per second
        inner_pos = outer_pos * radius_ratio;


        // Get PID adjustments
        if ((reversed && degrees > 0) || (!reversed && !(degrees > 0))) { // left is inner side
            pid_adjustment_l = -1 * pid_drive_l.adjust(inner_pos, pos_l);
            pid_adjustment_r = pid_drive_r.adjust(outer_pos, pos_r);

            drive_l.spin(DIR_FWD, inner_vel_rpm + pid_adjustment_l, VEL_RPM);
            drive_r.spin(DIR_FWD, outer_vel_rpm + pid_adjustment_r, VEL_RPM);
        } else { // right is inner side
            pid_adjustment_l = pid_drive_l.adjust(outer_pos, pos_l);
            pid_adjustment_r = -1 * pid_drive_r.adjust(inner_pos, pos_r);

            drive_l.spin(DIR_FWD, outer_vel_rpm + pid_adjustment_l, VEL_RPM);
            drive_r.spin(DIR_FWD, inner_vel_rpm + pid_adjustment_r, VEL_RPM);
        }

        // Exit if we're past the desired angle
        if (degrees_remaining * dir_mod < 0)
            break;

        wait(20, vex::msec);
    }
    drive_l.stop(vex::brakeType::brake);
    drive_r.stop(vex::brakeType::brake);
}

// In testing
void drive_linear(float inches, float max_ips, float ips_per_sec, bool do_decel) {
    const int TPS = 50; // ticks per second

    // Initialize PID objects
    PID pid_r = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID pid_l = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD); // needs a seperate controller because they'll rack up error at different rates
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

    while (std::abs(avg_pos) < std::abs(inches)) { // cuts if we've reached target position
        // Update positions
        current_pos_r = POS_DRIVE_R - start_pos_r;
        current_pos_l = POS_DRIVE_L - start_pos_l;
        avg_pos = (current_pos_r + current_pos_l) / 2.0;

        // Handle accelerations
        handle_acceleration(current_pos_r, inches, &target_vel_r, max_ips, ips_per_sec, TPS, do_decel);
        handle_acceleration(current_pos_l, inches, &target_vel_l, max_ips, ips_per_sec, TPS, do_decel);

        // Get PID values
        pid_r_adj = pid_r.adjust(target_vel_r, VEL_DRIVE_R);
        pid_l_adj = pid_l.adjust(target_vel_l, VEL_DRIVE_L);
        pid_dir_adj = pid_dir.adjust(target_heading, ROTATION * GYRO_CORRECTION);

        r_vel_rpm = target_vel_r / DRIVE_REV__IN * 60;
        l_vel_rpm = target_vel_l / DRIVE_REV__IN * 60;

        // Move drive
        drive_r.spin(DIR_FWD, dir_mod * r_vel_rpm + pid_r_adj + pid_dir_adj, VEL_RPM);
        drive_l.spin(DIR_FWD, dir_mod * l_vel_rpm + pid_l_adj - pid_dir_adj, VEL_RPM);

        // Wait for next cycle
        wait(20, vex::msec);
    }
    if (do_decel) {
        drive_l.stop(vex::brakeType::brake);
        drive_r.stop(vex::brakeType::brake);
    } else {
        drive_l.stop(vex::brakeType::coast);
        drive_r.stop(vex::brakeType::coast);
    }
}

void turn_pid(float degrees, float ratio, int direction) {
    target_heading += degrees;
    PID drive_pid = PID(turn_kp_l, turn_ki_l, turn_kd_l);

    float speed_l;
    float speed_r;

    int time_still = 0;
    while (time_still < 80) {
        if (within_range(ROTATION * GYRO_CORRECTION, target_heading, 3))
            time_still += 20;
        else
            time_still = 0;

        speed_l = drive_pid.adjust(target_heading, ROTATION * GYRO_CORRECTION) * direction;
        speed_r = speed_l * ratio;

        // Limit to max speed
        if (speed_l > 12 * std::abs(ratio))
            speed_l = 12 * std::abs(ratio);
        else if (speed_l < -12 * std::abs(ratio))
            speed_l = -12 * std::abs(ratio);
        if (speed_r > 12 * std::abs(ratio))
            speed_r = 12 * std::abs(ratio);
        else if (speed_r < -12 * std::abs(ratio))
            speed_r = -12 * std::abs(ratio);

        drive_l.spin(DIR_FWD, speed_l, VLT_VLT);
        drive_r.spin(DIR_FWD, speed_r, VLT_VLT);

        wait(20, vex::msec);
    }
}

void straight_pid(float dist) {
    PID drive_pid = PID(move_kp, move_ki, move_kd);
    PID dir_pid = PID(DIR_KP, DIR_KI, DIR_KD);
    int time_still = 0;
    float speed_l, speed_r;
    float dir_adjustment;
    float start_pos_l = POS_DRIVE_L, start_pos_r = POS_DRIVE_R;

    while (time_still < 80) {
        speed_l = drive_pid.adjust(dist, POS_DRIVE_L - start_pos_l);
        speed_r = drive_pid.adjust(dist, POS_DRIVE_R - start_pos_r);
        dir_adjustment = dir_pid.adjust(target_heading, ROTATION * GYRO_CORRECTION);

        if (within_range(POS_DRIVE_R - start_pos_r, dist, 0.5)) {
            time_still += 20;
            dir_adjustment *= 0.2;
        }
        else
            time_still = 0;

        drive_r.spin(DIR_FWD, speed_r - dir_adjustment, VLT_VLT);
        drive_l.spin(DIR_FWD, speed_l + dir_adjustment, VLT_VLT);
        wait(20, vex::msec);
    }
}
