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
    intake_lift.set(0);

    while (lift.current(PCT_PCT)<80){
        lift.spin(DIR_REV);
    }
    wait(100, TIME_MSEC);
    lift.resetPosition();

    colorSort.setLightPower(100, PCT_PCT); 
    colorSort.setLight(vex::ledState::on); 

    lift.setStopping(vex::brakeType::hold);
    intakeHigh.setPosition(6, ROT_REV);

    while (1) {
        // master.rumble(".");
        // Drive control
        opdrive(TSA, spd_mod, SENSITIVITY * sens_mod);

        Brain.Screen.drawImageFromFile("Graduation.png", 0, 0);

        // Shift button
        shifted = btn_left();

        if( colorSort.color() == vex::color::blue){
            intakeHigh.resetPosition();
        }
        if (intakeHigh.position(ROT_REV) >= 1.5 && intakeHigh.position(ROT_REV) <= 1.7){
            intakeHigh.spinFor(-0.5, ROT_REV, 100, VEL_PCT, false);      
            wait(100, TIME_MSEC);
            intakeHigh.setPosition(6, ROT_REV);
        }
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
                while (lift.current(PCT_PCT)<80){
                    lift.spin(DIR_REV);
                    }
                    wait(100, TIME_MSEC);
                lift.resetPosition();
            }
            
            if (liftHeight == 1){
                lift.spinToPosition(15 * 5, ROT_DEG, 100, VEL_PCT, false);
                lift.setStopping(vex::brakeType::coast);
            }
            else if (liftHeight == 2){
                lift.spinToPosition(42 * 5, ROT_DEG, 100, VEL_PCT, false);
                lift.setStopping(vex::brakeType::hold);
                liftOT = 0;

            }
            else if (liftHeight == 3){
                lift.setStopping(vex::brakeType::hold);
                if (liftOT == 0){
                    intake.spinFor(250, TIME_MSEC, 100, VEL_PCT);
                    intake.spinFor(-180, ROT_DEG, 100, VEL_PCT, false);
                    wait(200, TIME_MSEC);
                    liftOT = 1;
                }

                lift.spinToPosition(140 * 5, ROT_DEG, 100, VEL_PCT, false);
                }
                 // MOGO Mech
            if (BTN_Y.PRESSED){
                mogo_clamp.set(!mogo_clamp.value());
            }

            // Smith Mech
            if (BTN_B.PRESSED)
                Smith_Mech.set(!Smith_Mech.value());


            // Intake lift
            if (BTN_X.PRESSED)
                intake_lift.set(!intake_lift.value());


            // PTO
            if (BTN_RIGHT.PRESSED){
                lift.spinToPosition(125*5, ROT_DEG, 200, VEL_RPM);
                wait(150, TIME_MSEC);
                lift.spinToPosition(2*5, ROT_DEG, 200, VEL_RPM, false);
                drive_straight(-21,45,100);
                mogo_clamp.set(1);
                turn_pid(-125, -1, 1); 
                intake.spin(DIR_FWD, 12, VLT_VLT);
            }

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