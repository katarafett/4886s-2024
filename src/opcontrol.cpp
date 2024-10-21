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

    const int LIFT_BUFFER = 110;

    int liftHeight = 1;
    bool liftOT = 1;
    intake_lift.set(1);

    while (lift.current(PCT_PCT)<50){
        lift.spin(DIR_REV);
    }
    wait(100, TIME_MSEC);
    lift.resetPosition();

    lift.setStopping(vex::brakeType::hold);


    while (1) {
        // master.rumble(".");
        // Drive control
        opdrive(TSA, spd_mod, SENSITIVITY * sens_mod);

        Brain.Screen.drawImageFromFile("Graduation.png", 0, 0);

        // Shift button
        shifted = btn_left();

        // Unshifted
        if (!shifted) {

            //Lift


            if (BTN_L1.PRESSED){
                liftHeight = liftHeight+1;
            }
            if (BTN_L2.PRESSED){
                liftHeight = liftHeight-1;
            }
            // To reset the lift
            if (BTN_DOWN.PRESSED){
                while (lift.current(PCT_PCT)<50){
                    lift.spin(DIR_REV);
                    }
                    wait(100, TIME_MSEC);
                lift.resetPosition();
            }
            
            if (liftHeight == 1){
                lift.spinToPosition(15 * 5/3, ROT_DEG, 100, VEL_PCT, false);
            }
            else if (liftHeight == 2){
                lift.spinToPosition(51 * 5/3, ROT_DEG, 100, VEL_PCT, false);
                liftOT = 0;

            }
            else if (liftHeight == 3){
                if (liftOT == 0){
                    intake.spinFor(-180, ROT_DEG, 100, VEL_PCT, false);
                    wait(200, TIME_MSEC);
                    liftOT = 1;
                }

                lift.spinToPosition(137 * 5/3, ROT_DEG, 100, VEL_PCT, false);
                }
                 // MOGO Mech
            if (BTN_Y.PRESSED){
                mogo_clamp.set(!mogo_clamp.value());
            }

            // Smith Mech
            if (BTN_B.PRESSED)
                Smith_Mech.set(!Smith_Mech.value());


            // Toggles chase neutral post
            //if (BTN_RIGHT.PRESSED)
                //do_neutral_line_up = !do_neutral_line_up;
            
            if (do_neutral_line_up) {
            // neutral_line_up();
            }
            wait(20, vex::msec);
            }

            // Intake
            intake.spin(DIR_FWD, (btn_r1() - btn_r2()) * BTN_TO_PCT, VEL_PCT);

                /*
                if (BTN_L1.PRESSED) {
                    lift.setTimeout(1250, vex::msec);
                    lift.spinToPosition(700, ROT_DEG, 100, VEL_PCT, false);
                }

                if (BTN_L2.PRESSED) {
                    lift.setTimeout(1250, vex::msec);
                    lift.spinToPosition(0, ROT_DEG, 100, VEL_PCT, false);
                }
                */
    }
        // Shifted
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
        float rspeed = (RIGHT_STICK_X * turn_mod);
        drive_r.spin(DIR_FWD, (lspeed - rspeed) * drive_mod, VEL_PCT);
        drive_l.spin(DIR_FWD, (lspeed + rspeed) * drive_mod, VEL_PCT);
        break;

    }
}

    // loat rspeed = (RIGHT_STICK_X * ((LEFT_STICK_Y) + 50) / 200);

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