#include "../include/main.h"
#include "stddefs.h"
#include "vex_global.h"
#include "vex_units.h"

void release_antenna(void);

void autonomous(void) {
    /*
    drive_straight(-10, 30, 50);
    turn_pid(-90, -1, 1);
    drive_straight(-4, 30, 50);
    intake.spinFor(3.5, ROT_REV, 66, VEL_PCT);
    */
    drive_straight(5, 30, 50);
    turn_pid(-142, -1, 1);
    drive_straight(-37, 30, 50);
    mogo_clamp.set(1);
    turn_pid(-175, -1, 1);
    drive_straight(18, 30, 50);
    intake.spin(DIR_FWD, 12, VLT_VLT);
    wait(700, TIME_MSEC);
    turn_pid(-45, -1, 1);







    /*
    drive_straight(14, 30, 50);
    turn_pid(-90, -1, 1);
    intake.spinFor(10, ROT_REV, 100, VEL_PCT, false);
    drive_straight(8, 30, 50);
    drive_straight(-20, 30, 50);
    */
}