#include "../include/main.h"
#include "stddefs.h"
#include "vex_thread.h"

// Driver macros
void opcontrol(void) {
                    lift.setStopping(vex::brakeType::coast);

    drive_l.stop(vex::brakeType::coast);
    drive_r.stop(vex::brakeType::coast);
    intake.stop(vex::brakeType::brake);
    colorSort.setLightPower(100, PCT_PCT);
    colorSort.setLight(vex::ledState::on);


    bool shifted = false;
    void red_sort(void);
    void blue_sort(void);


    float spd_mod = 1.0;
    float sens_mod = 1.0;
    bool do_neutral_line_up = false;

    const int LIFT_BUFFER = 110;

    int liftHeight = 0;
    bool liftOT = 0;
    bool liftSA = 0;
    intake_lift.set(0);
    bool sort = 1;

    while (lift.current(PCT_PCT) < 95) {
        lift.spin(DIR_REV, 90, PCT_PCT);
    }
    wait(100, TIME_MSEC);
    lift.resetPosition();
    lift.stop();


    while (1) {
        // master.rumble(".");
        // Drive control
        opdrive(TSA, spd_mod, SENSITIVITY * sens_mod);

        Brain.Screen.drawImageFromFile("Graduation.png", 0, 0);

        if (BTN_L2.pressing()) {
            lift.spinToPosition(280 * 4, ROT_DEG, 100, VEL_PCT, false);
            liftSA = 1;
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
        if (liftSA == 0) {
            if (liftHeight == 1) {
                lift.spinToPosition(3 * 4, ROT_DEG, 100, VEL_PCT, false);
                lift.setStopping(vex::brakeType::coast);
                liftOT = 0;
            } 
            else if (liftHeight == 2) {
                lift.spinToPosition(40 * 4, ROT_DEG, 100, VEL_PCT, false);
            } 
            else if (liftHeight == 3) {
                lift.spinToPosition(164 * 4, ROT_DEG, 100, VEL_PCT, false);
                if (liftOT == 0){
                    intakeHigh.setStopping(vex::brakeType::coast);
                    liftOT = 1;
                }
            }
        }

        // MOGO Mech
        if (BTN_Y.PRESSED){
            mogo_clamp.set(!mogo_clamp.value());
            intakeHigh.spinFor(-60, ROT_DEG, 100, VEL_PCT);
        }
        // Smith Mech
        if (BTN_B.PRESSED)
            Smith_MechR.set(!Smith_MechR.value());
        // Intake lift

        // AWS in skills
        if (BTN_RIGHT.PRESSED) {
            lift.spinToPosition(168 * 4, ROT_DEG, 150, VEL_RPM);
            wait(150, TIME_MSEC);
            drive_full.spinFor(DIR_REV, 300, TIME_MSEC, 50, VEL_PCT);
            lift.spinToPosition(-23 * 4, ROT_DEG, 200, VEL_RPM);    
            lift.resetPosition();
            mogo_clamp.set(1);
        }

        // Toggles chase neutral post
        //if (BTN_RIGHT.PRESSED)
        //do_neutral_line_up = !do_neutral_line_up;

        if (do_neutral_line_up) {
            // neutral_line_up();
        }
        liftSA = 0;
        wait(20, vex::msec);

    // Intake
    intakeLow.spin(DIR_FWD, (btn_r1() - btn_r2()) * BTN_TO_PCT, VEL_PCT);
    if (!BTN_X.pressing()){    
        intakeHigh.spin(DIR_FWD, (btn_r1() - btn_r2()) * BTN_TO_PCT, VEL_PCT);
    }
    else {
                    intakeLow.spin(DIR_FWD, 12, VLT_VLT);

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
