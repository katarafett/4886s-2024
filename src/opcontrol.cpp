#include "../include/main.h"

void opcontrol(void) {

    bool wings_out = false;
    bool smith_out = false;
    bool balance_out = false;

    while (1) {
        opdrive(TSA_STD, 1, SENSITIVITY);

        intake.spin(DIR_FWD, (BTN_R1.pressing() - BTN_R2.pressing()) * BTN__PCT, VEL_PCT);

        cata.spin(DIR_FWD, BTN_L1.pressing() * BTN__PCT, VEL_PCT);

        if (BTN_L2.PRESSED) {
            wings_out = !wings_out;
            wings.set(wings_out);
        }

        if (BTN_RIGHT.PRESSED) {
            smith_out = !smith_out;
            smith.set(smith_out);
        }

        if (BTN_Y.PRESSED) {
            balance_out = !balance_out;
            balance.set(balance_out);
        }

        wait(20, vex::msec);
    }
}

void opdrive(int control_mode, float drive_mod, float turn_mod) {
    drive_mod *= STICK__PCT;     // Adjust for percentage units
    double ry = RIGHT_STICK_Y, ly = LEFT_STICK_Y, rx = RIGHT_STICK_X, lx = LEFT_STICK_X;
    float rspeed, lspeed;
    switch (control_mode) {
        case TNK_STD:
            rspeed = ry * ry / 100 * ((ry > 0) - (ry < 0));
            lspeed = ly * ly / 100 * ((ly > 0) - (ly < 0));
            // drive_r.spin(DIR_FWD, rspeed, VEL_PCT);
            // drive_l.spin(DIR_FWD, lspeed, VEL_PCT);
            drive_r.spin(DIR_FWD, RIGHT_STICK_Y, VEL_PCT);
            drive_l.spin(DIR_FWD, LEFT_STICK_Y, VEL_PCT);
            printf("lspeed: %.2f\n", lspeed);
            break;
        case OSA_STD:
            drive_r.spin(DIR_FWD, (LEFT_STICK_Y - LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            drive_l.spin(DIR_FWD, (LEFT_STICK_Y + LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            break;

        case TSA_STD:
            // lspeed = (ly - rx) * (ly - rx) / 100 * (((ly - rx) > 0) - ((ly - rx) < 0));
            // rspeed = (ly + rx) * (ly + rx) / 100 * (((ly + rx) > 0) - ((ly + rx) < 0));
            drive_r.spin(DIR_FWD, (LEFT_STICK_Y - RIGHT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
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
    // Making the compiler shut up — completely useless
    ly = ry;
    lx = rx;
}
