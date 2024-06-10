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
    bool do_red_chase = false;
    bool do_blue_run = false;

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
            
        }
        // Shifted
        else {
            
        }
        // Both
        printf("%i \n", do_red_chase);

        // Release hang
        if (BTN_Y.PRESSED)
            hang_release.set(!hang_release.value());

        // Toggles chase red 
        if (BTN_RIGHT.PRESSED)
            do_red_chase = !do_red_chase;
        if (do_red_chase) {
            red_chase();
        }
        // Toggles run from blue
        if (BTN_DOWN.PRESSED)
            do_blue_run = !do_blue_run;
        if (do_blue_run) {
                    printf("hi");

            blue_run();
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
            drive_r.spin(DIR_FWD, (lspeed - rspeed) * drive_mod, VEL_PCT);
            drive_l.spin(DIR_FWD, (lspeed + rspeed) * drive_mod, VEL_PCT);
            break;
    }
}
