#include "../include/main.h"
#include "stddefs.h"
#include "vex_global.h"
#include "vex_units.h"

void release_antenna(void);

void autonomous(void) {
    switch (auton_mode) {
        case AWP:
            /* tune pid */
            drive_straight(2 * 24, 64, 52);
            master.rumble(".");
            drive_turn(90, WHEEL_TO_WHEEL_DIST * 2, 64, 52);
            break;
        case HALF_AWP_NEAR:
            /*
            // Get to triball
            drive_straight(10, 24, 48);
            // Remove triball
            smith.set(1);
            drive_turn(35, WHEEL_TO_WHEEL_DIST / 2, 36, 48, false);
            // Reset
            smith.set(0);
            // Try AWP
            wait(200, vex::msec);
            drive_turn(-45, WHEEL_TO_WHEEL_DIST / 2, 36, 36, true);
            drive_straight(26, 48, 48);
            drive_turn(-42, WHEEL_TO_WHEEL_DIST / 2, 36, 36, true);
            drive_straight(24, 24, 24);
            */
            break;
        case HALF_AWP_FAR:
            release_intake();
            // Get triball
            intake.spin(DIR_FWD, 50, PCT_PCT);
            drive_straight(3, 24, 24);
            wait(300, vex::msec);
            intake.stop(vex::brakeType::hold);
            // Position for next
            drive_straight(-31, 72, 54);
            drive_turn(-45, WHEEL_TO_WHEEL_DIST, 48, 36, true);
            drive_straight(-12, 48, 36);
            // Slap it out
            smith.set(1);
            drive_turn(-45, WHEEL_TO_WHEEL_DIST, 36, 24, true);
            drive_straight(-8, 54, 48);
            // Line up
            drive_l.spin(DIR_FWD, -50, PCT_PCT);
            wait(650, vex::msec);
            target_heading -= 15;       // effectively turn 10 degrees left
            drive_straight(13, 60, 48);
            smith.set(0);
            drive_turn(-165, WHEEL_TO_WHEEL_DIST / 2, 54, 36);
            drive_straight(1, 48, 24);      // tries to correct angle
            // Slam stuff in
            intake.spin(DIR_FWD, -100, PCT_PCT);
            drive_r.spin(DIR_FWD, 100, PCT_PCT);
            drive_l.spin(DIR_FWD, 100, PCT_PCT);
            wait(650, vex::msec);
            drive_straight(-14, 60, 48);
            drive_r.spin(DIR_FWD, 100, PCT_PCT);
            drive_l.spin(DIR_FWD, 100, PCT_PCT);
            wait(650, vex::msec);
            intake.stop(vex::brakeType::coast);
            drive_straight(-10, 60, 48);
            // Pzth to one of the middle triballs
            drive_turn(-90, WHEEL_TO_WHEEL_DIST / 2, 48, 48);
            drive_straight(46, 84, 56);
            break;
        case NEAR_ELIMS:
            drive_straight(-28, 48, 48);
            drive_turn(15, WHEEL_TO_WHEEL_DIST - 9, 36, 36, false);
            drive_straight(3, 24, 24);
            wait(200, vex::msec);
            drive_l.spin(DIR_FWD, -100, VEL_PCT);
            drive_r.spin(DIR_FWD, -100, VEL_PCT);
            wait(1000, vex::msec);
            drive_straight(15, 48, 48);
            drive_turn(90, WHEEL_TO_WHEEL_DIST / 2, 36, 36, false);
            drive_straight(-4, 24, 24);
            drive_turn(-4, WHEEL_TO_WHEEL_DIST - 10, 36, 36, true);
            drive_straight(2, 24, 24);
            break;
        case FAR_ELIMS:
            break;
        case SKILLS:
            puncher.spin(DIR_FWD, 50, VEL_PCT);
            break;
    }
}
