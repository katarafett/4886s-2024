#include "../include/main.h"
#include "stddefs.h"
#include "vex_global.h"
#include "vex_units.h"

void release_antenna(void);

void autonomous(void) {
switch (auton_mode) {

    case BLUE_RIGHT: {
        //Full AWP quad side
        //unravel
        intake.spinFor(10, ROT_REV, 100, VEL_PCT, false);
        lift.spinFor(450, ROT_DEG, 100, VEL_PCT, true);
        //go for the AS
        turn_pid(-90, -1, 1);
        intake.spinFor(-1, ROT_REV, 100, VEL_PCT, false);
        drive_straight(4.6, 30, 50);
        lift.spinFor(-200, ROT_DEG, 100, VEL_PCT);
        //go for MOGO
        lift.spinFor(-130, ROT_DEG, 20, VEL_PCT, false);
        drive_straight(-10, 50, 50);
        turn_pid(-4, -1, 1);
        drive_straight(-23, 65, 50, false);
        mogo_clamp.set(1);
        drive_straight(-2, 30, 50);
        wait(250, TIME_MSEC);
        // score the ring in intake
        intake.spinFor(10, ROT_REV, 600, VEL_RPM, false);
        // go for the stack of two
        turn_pid(-95, -1, 1);
        drive_straight(20, 50, 50, false);
        intake.spinFor(150, ROT_REV, 600, VEL_RPM, false);
        drive_straight(3, 25, 50);
        wait(250, TIME_MSEC);
        drive_straight(-2, 30, 50);
        //go for quad stack
        turn_pid(-88, -1, 1);
        drive_straight(13, 18, 50);
        // turn to pickup the second
        drive_straight(-6, 18, 50);
        wait(1000, TIME_MSEC);
        turn_pid(-38, -1, 1);
        drive_straight(9, 15, 50);
        drive_straight(-9, 18, 50);
        wait(200, TIME_MSEC);
        // prep to touch the bar
        lift.spinToPosition(400, ROT_DEG, 60, VEL_PCT, false);
        // go to touch the bar
        turn_pid(-70, -1, 1);
        turn_pid(20, -1, 1);
        drive_straight(20, 30, 50, false);
        break;
    }


    case BLUE_LEFT: {

        // goal rush scoring 6 pts
        lift.spinFor(375, ROT_DEG, 100, VEL_PCT, false);
        drive_straight(39, 75, 50);
        lift.spinFor(-325, ROT_DEG, 100, VEL_PCT, true);
        turn_pid(-35, -1, 1);
        drive_straight(-22, 75, 60);
        mogo_clamp.set(1);
        turn_pid(-32, -1, 1);
        drive_straight(20, 75, 60);
        intake.spin(DIR_FWD, 100, VEL_PCT);
        drive_straight(5, 15, 60);
        lift.spinFor(500, ROT_DEG, 100, VEL_PCT, false);
        wait(2000, TIME_MSEC);
        turn_pid(155, -1, 1);
        drive_straight(25, 15, 60);
        break;
}

    case RED_RIGHT:{

        // goal rush scoring 6 pts
        lift.spinFor(375, ROT_DEG, 100, VEL_PCT, false);
        drive_straight(39, 75, 50);
        lift.spinFor(-325, ROT_DEG, 100, VEL_PCT, true);
        turn_pid(38, -1, 1);
        drive_straight(-25, 75, 60);
        mogo_clamp.set(1);
        turn_pid(25, -1, 1);
        drive_straight(20, 75, 60);
        intake.spin(DIR_FWD, 100, VEL_PCT);
        drive_straight(5, 15, 60);
        lift.spinToPosition(500, ROT_DEG, 100, VEL_PCT, false);
        drive_straight(10, 15, 60);
        wait(500000, TIME_MSEC);
        break;
    }


    case RED_LEFT:{
//unravel
        intake.spinFor(10, ROT_REV, 100, VEL_PCT, false);
        lift.spinFor(450, ROT_DEG, 100, VEL_PCT, true);
        //go for the AS
        turn_pid(90, -1, 1);
        intake.spinFor(-1, ROT_REV, 100, VEL_PCT, false);
        drive_straight(4.6, 30, 50);
        lift.spinFor(-200, ROT_DEG, 100, VEL_PCT);
        //go for MOGO
        lift.spinFor(-130, ROT_DEG, 20, VEL_PCT, false);
        drive_straight(-10, 50, 50);
        turn_pid(4, -1, 1);
        drive_straight(-23, 65, 50, false);
        mogo_clamp.set(1);
        drive_straight(-2, 30, 50);
        wait(250, TIME_MSEC);
        // score the ring in intake
        intake.spinFor(10, ROT_REV, 600, VEL_RPM, false);
        // go for the stack of two
        turn_pid(95, -1, 1);
        drive_straight(20, 50, 50, false);
        intake.spinFor(150, ROT_REV, 600, VEL_RPM, false);
        drive_straight(3, 25, 50);
        wait(250, TIME_MSEC);
        drive_straight(-2, 30, 50);
        //go for quad stack
        turn_pid(88, -1, 1);
        drive_straight(13, 18, 50);
        // turn to pickup the second
        drive_straight(-6, 18, 50);
        wait(1000, TIME_MSEC);
        turn_pid(38, -1, 1);
        drive_straight(9, 15, 50);
        drive_straight(-9, 18, 50);
        wait(200, TIME_MSEC);
        // prep to touch the bar
        lift.spinToPosition(400, ROT_DEG, 60, VEL_PCT, false);
        // go to touch the bar
        turn_pid(70, -1, 1);
        turn_pid(-20, -1, 1);
        drive_straight(20, 30, 50, false);
        wait(500000, TIME_MSEC);
        break;
    }


    case SKILLS:{

        // Unravel and score on AS
        intake.spinFor(8, ROT_REV, 100, VEL_PCT, false);
        lift.spinFor(300, ROT_DEG, 100, VEL_PCT, true);
        // go for MOGO
        drive_straight(12, 30, 50);
        turn_pid(90, -1, 1);
        drive_straight(-24, 60, 50);
        mogo_clamp.set(1);
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
        mogo_clamp.set(0);
        drive_straight(-10, 20, 50);
        turn_pid(-30, -1, 1);
        turn_pid(30, -1, 1);


        // second MOGO
        drive_straight(27, 40, 50);
        turn_pid(-155, -1, 1);
        drive_straight(-56, 40, 50);
        mogo_clamp.set(1);
        // first ring
        turn_pid(90, -1, 1);
        drive_straight(18, 40, 50);
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
        mogo_clamp.set(0);
        drive_straight(-10, 20, 50);
        wait(500, TIME_MSEC);
        intake.stop();

        // reset imu
        drive_straight(8, 40, 50);
        turn_pid(66, -1, 1);
        mogo_clamp.set(1);
        drive_full.spinFor(DIR_REV, 500, TIME_MSEC, 100, VEL_PCT);
        wait(200, TIME_MSEC);
        imu.setHeading(0, ROT_DEG);


        // thrid MOGO
        lift.spinToPosition(300, ROT_DEG, 100, VEL_PCT, false);
        drive_straight(73, 40, 50, false);
        mogo_clamp.set(0);
        // first ring
        intake.spinFor(DIR_FWD, 10, ROT_REV, 100, VEL_PCT, false);
        drive_straight(15, 20, 50);
        wait(1000, TIME_MSEC);
        // MOGO
        turn_pid(115, -1, 1);
        drive_straight(-56, 40, 50);
        mogo_clamp.set(1);
        lift.spinToPosition(180, ROT_DEG, 100, VEL_PCT, false);
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
        lift.spinToPosition(350, ROT_DEG, 100, VEL_PCT, false);
        turn_pid(-45, -1, 1);
        drive_straight(35, 40, 50);
        // put MOGO in corner
        turn_pid(-105, -1, 1);
        mogo_clamp.set(0);
        drive_straight(-35, 40, 50);
        turn_pid(-80, -1, 1);
        drive_straight(120, 40, 50);
        break;
   }



   
/*
    drive_straight(-10, 30, 50);
    turn_pid(-90, -1, 1);
    drive_straight(-4, 30, 50);
    intake.spinFor(3.5, ROT_REV, 66, VEL_PCT);
    drive_straight(5, 30, 50);
    turn_pid(-142, -1, 1);
    drive_straight(-37, 30, 50);
    mogo_clamp.set(1);
    turn_pid(-175, -1, 1);
    drive_straight(18, 30, 50);
    intake.spin(DIR_FWD, 12, VLT_VLT);
    wait(700, TIME_MSEC);
    turn_pid(-45, -1, 1);
    */


    /*
    drive_straight(14, 30, 50);
    turn_pid(-90, -1, 1);
    intake.spinFor(10, ROT_REV, 100, VEL_PCT, false);
    drive_straight(8, 30, 50);
    drive_straight(-20, 30, 50);
    */

}
}