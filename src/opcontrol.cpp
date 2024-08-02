#include "../include/main.h"
#include "stddefs.h"
#include "vex_thread.h"

// Driver macros
void opcontrol(void) {
    drive_l.stop(vex::brakeType::coast);
    drive_r.stop(vex::brakeType::coast);
    bool shifted = false;

    float spd_mod = 1.0;
    float sens_mod = 1.0;
    bool do_neutral_line_up = false;

    while (1) {
        // master.rumble(".");
        // Drive control
        opdrive(TSA, spd_mod, SENSITIVITY * sens_mod);

        // Shift button
        shifted = btn_left();

        //lift.spin(DIR_FWD, (btn_up() - btn_down()) * BTN_TO_PCT, VEL_PCT);

        // Unshifted
        if (!shifted) {
            // Intake
            intake.spin(DIR_FWD, (btn_r1() - btn_r2()) * BTN_TO_PCT, VEL_PCT);


            if (BTN_L1.PRESSED) {
                lift.setTimeout(1250, vex::msec);
                lift.spinToPosition(700, ROT_DEG, 100, VEL_PCT, false);
            }

            if (BTN_L2.PRESSED) {
                lift.setTimeout(1250, vex::msec);
                lift.spinToPosition(0, ROT_DEG, 100, VEL_PCT, false);
            }
/*
            if (BTN_X.pressing()) {
                imuTurn(180);
                printf("-\n");
            }
*/
        }
        // Shifted
        else {
        }
        // Both
        printf("%i \n", do_neutral_line_up);

        // Release hang
        if (BTN_Y.PRESSED)
            hang_release.set(!hang_release.value());

        // Toggles chase neutral post
        if (BTN_RIGHT.PRESSED)
            do_neutral_line_up = !do_neutral_line_up;
        
        if (do_neutral_line_up) {
           // neutral_line_up();
        }

        wait(20, vex::msec);
    }
}

void opdrive(int control_mode, float drive_mod, float turn_mod) {
    switch (control_mode) {
    case TNK:
        drive_r.spin(DIR_FWD, RIGHT_STICK_Y, VEL_PCT);
        drive_l.spin(DIR_FWD, LEFT_STICK_Y, VEL_PCT);
        break;
    case OSA:
        drive_r.spin(DIR_FWD, (LEFT_STICK_Y - LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
        drive_l.spin(DIR_FWD, (LEFT_STICK_Y + LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
        break;
    case TSA:
        float lspeed = LEFT_STICK_Y;
        float rspeed = RIGHT_STICK_X * turn_mod;
        drive_r.spin(DIR_FWD, (lspeed + rspeed) * drive_mod, VEL_PCT);
        drive_l.spin(DIR_FWD, (lspeed - rspeed) * drive_mod, VEL_PCT);
        break;

    }
}

/**
 * turnGoal is the desired rotation in degrees
 */
/*
void imuTurn(int turnGoal){
    printf(".\n");
    while (imu.rotation() <= turnGoal) {
        drive_l.spin(DIR_FWD, -20, VEL_PCT);
        drive_r.spin(DIR_FWD, 20, VEL_PCT);
    }
    drive_full.stop();
}
*/