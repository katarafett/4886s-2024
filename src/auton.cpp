#include "../include/main.h"
#include "stddefs.h"
#include "vex_global.h"
#include "vex_units.h"

void release_antenna(void);

void autonomous(void) {
    switch (auton_mode) {

        case FULL_AWP: {
            // score on AWS
            lift.spinToPosition(130*5, ROT_DEG, 200, VEL_RPM, false);
            wait(150, TIME_MSEC);
            drive_straight(5, 50, 50);
            // pickup ring 2 with smith mech
            drive_straight(-11, 50, 50);
            lift.spinToPosition(-40, ROT_DEG, 200, VEL_RPM, false);
            turn_pid(-25, -1, 1);
            drive_straight(4, 50, 50);
            Smith_Mech.set(1);
            // push teamate
            drive_straight(12, 50, 50);
            // go for MOGO
            drive_straight(-18, 50, 50);
            drive_turn(95, -7, 75, 75, false);
            intake.spin(DIR_FWD, 100, PCT_PCT);
            drive_straight(-26, 75, 75);
            mogo_clamp.set(1);
            drive_straight(-3, 50, 50);
            // go for ring 3
            turn_pid(92, -1, 1);
            drive_straight(25, 75, 75);
            wait(300, TIME_MSEC);
            drive_straight(-12, 75, 75);
            // go to score ring 2
            turn_pid(-158, -1, 1);
            Smith_Mech.set(0);
            wait(500, TIME_MSEC);
            turn_pid(-20, -1, 1);
            drive_straight(45, 25, 75);

            break;
        }
        case BLUE_RIGHT: {

            break;
        }


        case BLUE_LEFT: {

            break;
        }


        case RED_RIGHT:{

            break;
        }


        case RED_LEFT:{

        }


        case ELIMS_RED:{
            //MOGO
            drive_straight(-24, 30, 50, false);
            mogo_clamp.set(1);
            drive_straight(-2, 30, 50);
            wait(500, TIME_MSEC);
            // Ring 1
            turn_pid(90, -1, 1);
            intake.spin(DIR_FWD, 12, VLT_VLT);
            drive_straight(31, 75, 150);
            intake.stop();
            drive_straight(-1, 75, 150);
            // Ring 2
            turn_pid(100, -1, 1);
            intake.spin(DIR_FWD, 12, VLT_VLT);
            drive_straight(12, 30, 50);
            // ring 3
            turn_pid(-35, -1, 1);
            drive_straight(-20, 30, 50, true);
            wait(400, TIME_MSEC);
            turn_pid(30, -1, 1);
            drive_straight(22, 30, 50, true);
            drive_straight(-36, 30, 50, true);
            turn_pid(-135, -1, 1);

            break;
        }


        case SKILLS:{
            
            // first ring
            lift.spinToPosition(130*5, ROT_DEG, 200, VEL_RPM);
            wait(150, TIME_MSEC);
            lift.spinToPosition(2*5, ROT_DEG, 200, VEL_RPM, false);
            drive_straight(-20, 50, 50);
            mogo_clamp.set(1);
            turn_pid(-125, -1, 1); 
            intake.spin(DIR_FWD, 12, VLT_VLT);
            drive_straight(20, 50, 50);
            turn_pid(-90, -1, 1);
            drive_straight(21, 50, 50);
            // third
            turn_pid(-60, -1, 1);
            drive_straight(23, 50, 50);
            // fourth
            wait(300, TIME_MSEC);
            drive_straight(-23, 50, 50);
            turn_pid(-30, -1, 1);
            drive_straight(21, 50, 50);
            // fifth
            drive_straight(12, 15, 50);
            // put mogo in corner
            turn_pid(-110, -1, 1);
            drive_straight(-10, 20, 50);
            mogo_clamp.set(0);
            


            // second MOGO
            drive_straight(27, 40, 50);
            turn_pid(-159, -1, 1);
            drive_straight(-54, 40, 50);
            mogo_clamp.set(1);
            // first ring
            turn_pid(90, -1, 1);
            drive_straight(20, 40, 50);
            // second
            turn_pid(90, -1, 1);
            drive_straight(23, 40, 50);
            // third
            turn_pid(60, -1, 1);
            drive_straight(23, 40, 50);
            // fourth
            wait(300, TIME_MSEC);
            drive_straight(-23, 40, 50);
            turn_pid(30, -1, 1);
            drive_straight(21, 40, 50);
            // fifth
            drive_straight(12, 15, 50);
            // put MOGO in corner
            turn_pid(110, -1, 1);
            drive_straight(-10, 20, 50);
            mogo_clamp.set(0);
            intakeHigh.stop();

            // reset imu
            drive_straight(10, 40, 50);
            turn_pid(70, -1, 1);
            mogo_clamp.set(1);
            drive_full.spinFor(DIR_REV, 1000, TIME_MSEC, 30, VEL_PCT);

            // thrid MOGO
            intakeLow.spin(DIR_FWD, 12, VLT_VLT);
            drive_straight(73, 40, 50, false);
            mogo_clamp.set(0);
            // first ring
            drive_straight(15, 20, 50);
            wait(500, TIME_MSEC);
            // MOGO
            turn_pid(115, -1, 1);
            drive_straight(-56, 40, 50);
            mogo_clamp.set(1);
            // second
            intake.spin(DIR_FWD, 12, VLT_VLT);
            
            turn_pid(15, -1, 1);
            drive_straight(31, 40, 50);
            // third
            turn_pid(90, -1, 1);
            drive_straight(35, 40, 50);
            // fourth
            turn_pid(90, -1, 1);
            drive_straight(35, 40, 50);
            // fifth
            turn_pid(-45, -1, 1);
            drive_straight(35, 40, 50);
            // put MOGO in corner
            turn_pid(-105, -1, 1);
            mogo_clamp.set(0);
            drive_straight(-35, 40, 50);
            turn_pid(-80, -1, 1);
            drive_straight(180, 40, 50);

           break;
            }
        }
}