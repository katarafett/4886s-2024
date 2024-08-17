#include "../include/main.h"
#include "stddefs.h"
#include "vex_global.h"
#include "vex_units.h"

void release_antenna(void);

void autonomous(void) {
    //unravel
    intake.spinFor(10, ROT_REV, 100, VEL_PCT, false);
    lift.spinFor(350, ROT_DEG, 100, VEL_PCT, true);
    //go for the AS
    turn_pid(-87, -1, 1);
    intake.spinFor(-1, ROT_REV, 100, VEL_PCT, false);
    drive_straight(4, 30, 50);
    lift.spinFor(-200, ROT_DEG, 100, VEL_PCT);
    //go for MOGO
    lift.spinFor(-150, ROT_DEG, 20, VEL_PCT, false);
    drive_straight(-10, 50, 50);
    turn_pid(-8, -1, 1);
    drive_straight(-23, 65, 50, false);
    mogo_clamp.set(1);
    drive_straight(-2, 30, 50);
    wait(250, TIME_MSEC);
    // score the ring in intake
    intake.spinFor(10, ROT_REV, 600, VEL_RPM, false);
    // go for the stack of two
    turn_pid(-90, -1, 1);
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
    lift.spinFor(350, ROT_DEG, 60, VEL_PCT, false);
    // go to touch the bar
    turn_pid(-70, -1, 1);
    turn_pid(20, -1, 1);
    drive_straight(15, 30, 50, false);
    mogo_clamp.set(0);
    drive_straight(5, 30, 50);





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