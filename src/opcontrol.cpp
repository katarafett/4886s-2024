#include "../include/main.h"
#include "stddefs.h"
#include "vex_thread.h"

// Driver macros
void opcontrol(void) {
    drive_l.stop(vex::brakeType::coast);
    drive_r.stop(vex::brakeType::coast);
    intake.stop(vex::brakeType::brake);
    bool shifted = false;

    float spd_mod = 1.0;
    float sens_mod = 1.0;
    bool do_neutral_line_up = false;

    const int LIFT_BUFFER = 110;

    int liftHeight = 1;
    bool liftOT = 0;
    intake_lift.set(0);
    bool sort = 1;

    while (lift.current(PCT_PCT) < 95) {
        lift.spin(DIR_REV, 85, PCT_PCT);
    }
    wait(100, TIME_MSEC);
    lift.resetPosition();

    colorSort.setLightPower(100, PCT_PCT);
    colorSort.setLight(vex::ledState::on);

    lift.setStopping(vex::brakeType::hold);

    while (1) {
        // master.rumble(".");
        // Drive control
        opdrive(TSA, spd_mod, SENSITIVITY * sens_mod);

        Brain.Screen.drawImageFromFile("Graduation.png", 0, 0);

        if (BTN_L2.pressing()) {
            lift.spinToPosition(280 * 4, ROT_DEG, 100, VEL_PCT, false);
            liftOT = 1;
        }
        if (BTN_L1.PRESSED)
            liftHeight = liftHeight + 1;
        if (BTN_L2.PRESSED)
            liftHeight = 1;
        if (BTN_LEFT.PRESSED)
            sort = !sort;



        // To reset the lift
        if (BTN_DOWN.PRESSED) {
            while (lift.current(PCT_PCT) < 95) {
                lift.spin(DIR_REV, 85, PCT_PCT);
                wait(100, TIME_MSEC);
            }
            lift.resetPosition();
        }
        if (liftOT == 0) {
            if (liftHeight == 1) {
                lift.spinToPosition(2 * 4, ROT_DEG, 100, VEL_PCT, false);
                lift.setStopping(vex::brakeType::coast);
            } else if (liftHeight == 2) {
                lift.spinToPosition(54 * 4, ROT_DEG, 100, VEL_PCT, false);
                lift.setStopping(vex::brakeType::hold);
            } else if (liftHeight == 3) {
                lift.setStopping(vex::brakeType::hold);
                lift.spinToPosition(183 * 4, ROT_DEG, 100, VEL_PCT, false);
            } else if (liftHeight == 4) {
                lift.spinToPosition(280 * 4, ROT_DEG, 100, VEL_PCT, false);
                lift.setStopping(vex::brakeType::hold);
            }
        }

        // MOGO Mech
        if (BTN_Y.PRESSED){
            mogo_clamp.set(!mogo_clamp.value());
            intakeHigh.spinFor(-60, ROT_DEG, 100, VEL_PCT);
        }
        // Smith Mech
        if (BTN_B.PRESSED)
            Smith_Mech.set(!Smith_Mech.value());
        // Intake lift
        if (BTN_X.PRESSED)
            intake_lift.set(!intake_lift.value());


        // AWS in skills
        if (BTN_RIGHT.PRESSED) {
            lift.spinToPosition(165 * 4, ROT_DEG, 200, VEL_RPM);
            wait(150, TIME_MSEC);
            drive_full.spinFor(DIR_REV, 400, TIME_MSEC, 50, VEL_PCT);

            while (lift.current(PCT_PCT) < 95) {
                lift.spin(DIR_REV, 85, PCT_PCT);
            }
        lift.resetPosition();
        mogo_clamp.set(1);
        }

        // Toggles chase neutral post
        //if (BTN_RIGHT.PRESSED)
        //do_neutral_line_up = !do_neutral_line_up;

        if (do_neutral_line_up) {
            // neutral_line_up();
        }
        liftOT = 0;
        wait(20, vex::msec);

    // Intake
    intake.spin(DIR_FWD, (btn_r1() - btn_r2()) * BTN_TO_PCT, VEL_PCT);

    }


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