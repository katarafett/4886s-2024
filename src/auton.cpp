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
            // Score on the AWS
            intake_lift.set(0);
            intake.spinFor(3.75, ROT_REV, 600, VEL_RPM, false);
            wait(500, TIME_MSEC);
            turn_pid(180, -1, 1);
            drive_turn(-100, 10.3, 50, 50, false);
            drive_full.spinFor(DIR_REV, 300, TIME_MSEC, 100, VEL_PCT);
            wait(300, TIME_MSEC);
            drive_straight(1, 50, 50);
            intake.spinFor(2.2, ROT_REV, 600, VEL_RPM);
            intake.spinFor(-.5, ROT_REV, 600, VEL_RPM, false);

            // Go for the MOGO
            drive_straight(10, 50, 50);
            turn_pid(-150, -1, 1);
            drive_straight(-25, 50, 50);
            mogo_clamp.set(1);
            wait(300, TIME_MSEC);
            drive_straight(-6, 50, 50);
            wait(100, TIME_MSEC);
            intake.spin(DIR_FWD, 80, PCT_PCT);
            // Third Ring
            turn_pid(-123, -1, 1);
            drive_straight(23, 75, 200);
            wait(500, TIME_MSEC);
            // Fourth Ring
            turn_pid(-100, -1, 1);
            drive_straight(14, 50, 50);
            wait(500, TIME_MSEC);
            drive_straight(-10, 50, 50);
            wait(500, TIME_MSEC);
            // Fifth ring
            turn_pid(-50, -1, 1);
            drive_straight(35, 40, 50);
            break;
        }


        case BLUE_LEFT: {
            intake_lift.set(0);
            //MOGO Rush
            drive_straight(-46, 75, 50);
            mogo_clamp.set(1);
            drive_straight(-1.5, 50, 50);
            // Second Ring
            turn_pid(40, -1, 1);
            intake.spin(DIR_FWD, 600, VEL_RPM);
            wait(1000, TIME_MSEC);
            drive_straight(17, 50, 50);
            wait(1000, TIME_MSEC);
            mogo_clamp.set(0);
            intake.stop();
            turn_pid(-288, -1, 1);
            // Second Goal
            drive_straight(-23, 30, 50, false);
            mogo_clamp.set(1);
            drive_straight(-3, 75, 100);
            wait(300, TIME_MSEC);
            turn_pid(-130, -1, 1);
            drive_straight(-3, 75, 100);
            intake_lift.set(0);
            // Thrid Ring
            drive_straight(24, 30, 100);
            intake_lift.set(1);
            intake.spin(DIR_FWD, 600, VEL_RPM);
            wait(2000, TIME_MSEC);
            drive_straight(-15, 75, 100);
            turn_pid(-90, -1, 1);
            drive_straight(20, 75, 100);




            break;
        }


        case RED_RIGHT:{
            intake_lift.set(0);
            //MOGO Rush
            drive_straight(-46, 75, 50);
            mogo_clamp.set(1);
            drive_straight(-1.5, 50, 50);
            // Second Ring
            turn_pid(-40, -1, 1);
            intake.spin(DIR_FWD, 600, VEL_RPM);
            wait(1000, TIME_MSEC);
            drive_straight(17, 50, 50);
            wait(1000, TIME_MSEC);
            mogo_clamp.set(0);
            intake.stop();
            turn_pid(288, -1, 1);
            // Second Goal
            drive_straight(-23, 30, 50, false);
            mogo_clamp.set(1);
            drive_straight(-3, 75, 100);
            wait(300, TIME_MSEC);
            turn_pid(130, -1, 1);
            drive_straight(-3, 75, 100);
            intake_lift.set(0);
            // Thrid Ring
            drive_straight(24, 30, 100);
            intake_lift.set(1);
            intake.spin(DIR_FWD, 600, VEL_RPM);
            wait(2000, TIME_MSEC);
            drive_straight(-15, 75, 100);
            turn_pid(90, -1, 1);
            drive_straight(20, 75, 100);
            break;
        }


        case RED_LEFT:{
            // Score on the AWS
            intake_lift.set(0);
            intake.spinFor(3.75, ROT_REV, 600, VEL_RPM, false);
            wait(500, TIME_MSEC);
            turn_pid(-180, -1, 1);
            drive_turn(100, -10.3, 50, 50, false);
            drive_full.spinFor(DIR_REV, 300, TIME_MSEC, 100, VEL_PCT);
            wait(300, TIME_MSEC);
            drive_straight(1, 50, 50);
            intake.spinFor(2.2, ROT_REV, 600, VEL_RPM);
            intake.spinFor(-.5, ROT_REV, 600, VEL_RPM, false);

            // Go for the MOGO
            drive_straight(10, 50, 50);
            turn_pid(150, -1, 1);
            drive_straight(-25, 50, 50);
            mogo_clamp.set(1);
            wait(300, TIME_MSEC);
            drive_straight(-6, 50, 50);
            wait(100, TIME_MSEC);
            intake.spin(DIR_FWD, 80, PCT_PCT);
            // Third Ring
            turn_pid(123, -1, 1);
            drive_straight(23, 75, 200);
            wait(500, TIME_MSEC);
            // Fourth Ring
            turn_pid(130, -1, 1);
            drive_straight(30, 50, 50);
            wait(500, TIME_MSEC);
            // Fifth Ring
            //drive_straight(-15, 50, 50);
            //turn_pid(25, -1, 1);
            //drive_straight(18, 50, 50);
            //wait(500, TIME_MSEC);

            // Touch Bar
            turn_pid(75, -1, 1);
            drive_straight(35, 50, 50);
            break;
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
            
            
        // Unravel and score on AS
        intake.spinFor(8, ROT_REV, 100, VEL_PCT, false);
        wait(300, TIME_MSEC);
        // go for MOGO
        drive_straight(13, 30, 50);
        turn_pid(90, -1, 1);
        drive_straight(-22, 60, 50);
        //mogo_clamp.set(1);
        // first ring
        intake.spin(DIR_FWD, 12, VLT_VLT);
        turn_pid(-90, -1, 1);
        drive_straight(20, 50, 50);
        // second
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
        turn_pid(-155, -1, 1);
        drive_straight(-50, 40, 50);
        mogo_clamp.set(1);
        // first ring
        turn_pid(90, -1, 1);
        drive_straight(20, 40, 50);
        // second
        turn_pid(90, -1, 1);
        drive_straight(21, 40, 50);
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
            drive_straight(8, 40, 50);
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
            drive_straight(35, 40, 50);
            turn_pid(-80, -1, 1);
            drive_straight(180, 40, 50);

           break;
            }
        }
    }