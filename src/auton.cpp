#include "../include/main.h"

void release_antenna(void);

void autonomous(void) {
    switch (auton_mode) {
        case AWP:
            /* tune pid */
            drive_straight(3 * 24, 64, 52);
            master.rumble(".");
            drive_turn(90, WHEEL_TO_WHEEL_DIST * 2, 64, 52);
            break;
        case HALF_AWP_NEAR:
            // Get to triball
            drive_straight(-15, 24, 48);
            // Remove triball
            balance.set(1);
            drive_turn(35, WHEEL_TO_WHEEL_DIST / 2, 36, 48, false);
            // Reset
            balance.set(0);
            // Try AWP
            wait(200, vex::msec);
            drive_turn(-45, WHEEL_TO_WHEEL_DIST / 2, 36, 36, true);
            drive_straight(26, 48, 48);
            drive_turn(-42, WHEEL_TO_WHEEL_DIST / 2, 36, 36, true);
            drive_straight(24, 24, 24);
            break;
        case HALF_AWP_FAR:
            drive_straight(-28, 48, 48);
            drive_turn(-15, WHEEL_TO_WHEEL_DIST - 9, 36, 36, true);
            drive_straight(3, 24, 24);
            wait(200, vex::msec);
            drive_l.spin(DIR_FWD, -100, VEL_PCT);
            drive_r.spin(DIR_FWD, -100, VEL_PCT);
            wait(1000, vex::msec);
            drive_straight(12, 48, 48);
            // Try AWP
            drive_turn(38, WHEEL_TO_WHEEL_DIST / 2, 36, 36, false);
            drive_straight(32, 48, 48);
            drive_turn(41, WHEEL_TO_WHEEL_DIST / 2, 36, 36, false);
            drive_straight(25, 24, 24);
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
