#include "../include/main.h"

void opcontrol(void) {
    PID fly_pid (0.3, 0, 0, true, false, false);

    while (1) {
        opdrive(TSA_STD, 1, SENSITIVITY);

        float fly_pid_ajdustment_hi = fly_pid.pid_adjust(3200, VEL_FLY_HI);
        float fly_pid_ajdustment_lo = fly_pid.pid_adjust(3000, VEL_FLY_LO);

        if (fly_pid_ajdustment_hi < 0) fly_pid_ajdustment_hi = 0;
        if (fly_pid_ajdustment_lo < 0) fly_pid_ajdustment_lo = 0;

        flywheel_hi.spin(DIR_FWD, 8 + fly_pid_ajdustment_hi, VLT_VLT);
        flywheel_lo.spin(DIR_FWD, 8 + fly_pid_ajdustment_lo, VLT_VLT);

        fly_pid.tune_kP(0.1);
        fly_pid.tune_kD(0.1);

        printf("fly_hi: %.3f\n", VEL_FLY_HI);
        printf("fly_lo: %.3f\n", VEL_FLY_LO);

        wait(20, vex::msec);
    }
}

void opdrive(int control_mode, float drive_mod, float turn_mod) {
    switch (control_mode) {
        case TNK_STD:
            drive_r.spin(DIR_FWD, RIGHT_STICK_Y * drive_mod * STICK__PCT, VEL_PCT);
            drive_l.spin(DIR_FWD, LEFT_STICK_Y * drive_mod * STICK__PCT, VEL_PCT);
            break;
        case OSA_STD:
            drive_r.spin(DIR_FWD, (LEFT_STICK_Y - LEFT_STICK_X * turn_mod) * drive_mod * STICK__PCT, VEL_PCT);
            drive_l.spin(DIR_FWD, (LEFT_STICK_Y + LEFT_STICK_X * turn_mod) * drive_mod * STICK__PCT, VEL_PCT);
            break;
        case TSA_STD:
            drive_r.spin(DIR_FWD, (LEFT_STICK_Y - RIGHT_STICK_X * turn_mod * drive_mod) * drive_mod * STICK__PCT, VEL_PCT);
            drive_l.spin(DIR_FWD, (LEFT_STICK_Y + RIGHT_STICK_X * turn_mod * drive_mod) * drive_mod * STICK__PCT, VEL_PCT);
            break;
        case TNK_REV:
            drive_l.spin(DIR_REV, RIGHT_STICK_Y * drive_mod * STICK__PCT, VEL_PCT);
            drive_r.spin(DIR_REV, LEFT_STICK_Y * drive_mod * STICK__PCT, VEL_PCT);
            break;
        case OSA_REV:
            drive_l.spin(DIR_REV, (LEFT_STICK_Y - LEFT_STICK_X * turn_mod) * drive_mod * STICK__PCT, VEL_PCT);
            drive_r.spin(DIR_REV, (LEFT_STICK_Y + LEFT_STICK_X * turn_mod) * drive_mod * STICK__PCT, VEL_PCT);
            break;
        case TSA_REV:
            drive_r.spin(DIR_REV, (LEFT_STICK_Y + RIGHT_STICK_X * turn_mod) * drive_mod * STICK__PCT, VEL_PCT);
            drive_l.spin(DIR_REV, (LEFT_STICK_Y - RIGHT_STICK_X * turn_mod) * drive_mod * STICK__PCT, VEL_PCT);
    }
}
