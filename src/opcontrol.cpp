#include "../include/main.h"
#include "stddefs.h"

// Driver macros
#define L1_SHIFTED (BTN_L1.PRESSED && shifted)
#define R1_SHIFTED (BTN_R1.PRESSED && shifted)
#define R2_SHIFTED (BTN_R2.PRESSED && shifted)

#define L1_UNSHIFTED (BTN_L1.pressing() && !shifted)
#define R1_UNSHIFTED (BTN_R1.pressing() && !shifted)
#define R2_UNSHIFTED (BTN_R2.pressing() && !shifted)

void opcontrol(void) {
    bool wings_out_l = false;
    bool wings_out_r = false;
    bool smith_out = false;
    bool balance_out = false;
    bool shifted = false;

    while (1) {
        shifted = BTN_L2.pressing();

        opdrive(TSA_STD, 1, SENSITIVITY);

        intake.spin(DIR_FWD, (R1_UNSHIFTED - R2_UNSHIFTED) * BTN__PCT, VEL_PCT);
        puncher.spin(DIR_FWD, (L1_UNSHIFTED) * BTN__VLT, VLT_VLT);

        // Flip wings
        if (L1_SHIFTED) {
            wings_out_l = !wings_out_l;
            wings_l.set(wings_out_l);
        }
        if (R1_SHIFTED) {
            wings_out_r = !wings_out_r;
            wings_r.set(wings_out_r);
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
    printf("rsy: %ld", RIGHT_STICK_X);
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
            lspeed = (ly * ly * ly / 16129.0);
            rspeed = (rx * rx * rx / 16129.0);
            drive_r.spin(DIR_FWD, lspeed - rspeed, VEL_PCT);
            drive_l.spin(DIR_FWD, lspeed + rspeed, VEL_PCT);
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
