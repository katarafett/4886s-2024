#include "../include/main.h"

void opcontrol(void) {

    bool wings_out = false;

    while (1) {
        opdrive(TNK_STD, 1, SENSITIVITY);

        if (BTN_L2.PRESSED) {
            wings_out = !wings_out;
            wing_r.set(wings_out);
            wing_l.set(wings_out);
        }

        wait(20, vex::msec);
    }
}

void opdrive(int control_mode, float drive_mod, float turn_mod) {
    drive_mod *= STICK__PCT;     // Adjust for percentage units
    switch (control_mode) {
        case TNK_STD:
            drive_r.spin(DIR_FWD, RIGHT_STICK_Y * drive_mod, VEL_PCT);
            drive_l.spin(DIR_FWD, LEFT_STICK_Y * drive_mod, VEL_PCT);
            break;
        case OSA_STD:
            drive_r.spin(DIR_FWD, (LEFT_STICK_Y - LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            drive_l.spin(DIR_FWD, (LEFT_STICK_Y + LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            break;
        case TSA_STD:
            drive_r.spin(DIR_FWD, (LEFT_STICK_Y - RIGHT_STICK_X * turn_mod) * drive_mod * .7, VEL_PCT);
            drive_l.spin(DIR_FWD, (LEFT_STICK_Y + RIGHT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            break;
        case TNK_REV:
            drive_l.spin(DIR_REV, RIGHT_STICK_Y * drive_mod, VEL_PCT);
            drive_r.spin(DIR_REV, LEFT_STICK_Y * drive_mod, VEL_PCT);
            break;
        case OSA_REV:
            drive_l.spin(DIR_REV, (LEFT_STICK_Y - LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            drive_r.spin(DIR_REV, (LEFT_STICK_Y + LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            break;
        case TSA_REV:
            drive_r.spin(DIR_REV, (LEFT_STICK_Y + RIGHT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            drive_l.spin(DIR_REV, (LEFT_STICK_Y - RIGHT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            break;
        case XDRIVE:
            drive_rf.spin(DIR_FWD, LEFT_STICK_Y + LEFT_STICK_X - RIGHT_STICK_X, VEL_PCT);
            drive_rm.spin(DIR_FWD, LEFT_STICK_Y - LEFT_STICK_X - RIGHT_STICK_X, VEL_PCT);
            drive_lf.spin(DIR_FWD, LEFT_STICK_Y - LEFT_STICK_X + RIGHT_STICK_X, VEL_PCT);
            drive_lm.spin(DIR_FWD, LEFT_STICK_Y + LEFT_STICK_X + RIGHT_STICK_X, VEL_PCT);
            break;
    }
}
