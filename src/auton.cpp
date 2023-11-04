#include "../include/main.h"

void autonomous(void) {
    switch (auton_mode) {
        case AWP:
            break;
        case HALF_AWP_NEAR:
            // Get to triball
            drive_straight(-15, 24, 48);
            // Remove triball
            balance.set(1);
            drive_turn(35, WHEEL_TO_WHEEL_DIST / 2, 36, 48, false);
            // Reset
            balance.set(0);
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
            drive_l.spin(DIR_FWD, -100, VEL_PCT);
            drive_r.spin(DIR_FWD, -100, VEL_PCT);
            wait(1000, vex::msec);
            drive_straight(12, 48, 48);
            break;
        case SKILLS:
            break;
    }
}
