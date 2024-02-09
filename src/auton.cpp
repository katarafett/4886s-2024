#include "../include/main.h"
#include "stddefs.h"
#include "vex_global.h"
#include "vex_units.h"

void release_antenna(void);

void autonomous(void) {
    switch (auton_mode) {
        case AWP:
            release_intake();
            drive_r.spin(DIR_FWD, -100, VEL_PCT);
            drive_l.spin(DIR_FWD, -100, VEL_PCT);
            wait(1500, vex::msec);
            drive_r.spin(DIR_FWD, 100, VEL_PCT);
            drive_l.spin(DIR_FWD, 100, VEL_PCT);
            wait(500, vex::msec);
            drive_l.stop();
            drive_r.stop();
            /* tune pid */
            break;

        case HALF_AWP_NEAR:
            release_intake();
            // Knock out
            // wing_l.set(1);
            drive_turn(-45, WHEEL_TO_WHEEL_DIST / 2.0, 36, 24, false);
            // wing_l.set(0);
            drive_straight(2, 48, 48);
            drive_straight(-6, 48, 48);
            drive_turn(-45, WHEEL_TO_WHEEL_DIST, 36, 24, true);
            drive_straight(-28, 48, 48);
            break;

        case HALF_AWP_FAR:
            // release_intake();
            // Get triball
            // // sys3.spin(DIR_FWD, 50, PCT_PCT);
            drive_straight(3, 24, 24);
            wait(300, vex::msec);
            // // sys3.stop(vex::brakeType::hold);
            // Position for next
            drive_straight(-31, 72, 54);
            drive_turn(-45, WHEEL_TO_WHEEL_DIST, 48, 36, true);
            drive_straight(-12, 48, 36);
            // Slap it out
            // smith.set(1);
            drive_turn(-45, WHEEL_TO_WHEEL_DIST, 36, 24, true);
            drive_straight(-8, 54, 48);
            // Line up
            drive_l.spin(DIR_FWD, -50, PCT_PCT);
            wait(650, vex::msec);
            target_heading -= 15;       // effectively turn 15 degrees left
            drive_straight(13, 60, 48);
            // smith.set(0);
            drive_turn(-165, WHEEL_TO_WHEEL_DIST / 2, 54, 36);
            drive_straight(1, 48, 24);      // tries to correct angle
            // Slam stuff in
            // sys3.spin(DIR_FWD, -100, PCT_PCT);
            drive_r.spin(DIR_FWD, 100, PCT_PCT);
            drive_l.spin(DIR_FWD, 100, PCT_PCT);
            wait(650, vex::msec);
            drive_straight(-14, 60, 48);
            drive_r.spin(DIR_FWD, 100, PCT_PCT);
            drive_l.spin(DIR_FWD, 100, PCT_PCT);
            wait(650, vex::msec);
            // sys3.stop(vex::brakeType::coast);
            drive_straight(-10, 60, 48);
            // Pzth to one of the middle triballs
            drive_turn(-90, WHEEL_TO_WHEEL_DIST / 2, 48, 48);
            drive_straight(46, 84, 56);
            break;

        case NEAR_ELIMS:
            release_intake();
            // intake.spin(DIR_FWD, -50, VEL_PCT);
            // Push to our OZ
            drive_straight(33, 54, 36);
            drive_straight(-26, 54, 36);
            // Line up
            drive_turn(45, WHEEL_TO_WHEEL_DIST, 36, 24, true);
            drive_straight(-20, 48, 36);
            drive_turn(-45, WHEEL_TO_WHEEL_DIST, 36, 24, true);
            // Back up
            drive_l.spin(DIR_FWD, -10, VEL_PCT);
            drive_r.spin(DIR_FWD, -10, VEL_PCT);
            wait(900, vex::msec);
            drive_l.stop();
            drive_r.stop();
            break;

        case FAR_ELIMS:
            release_intake();
            drive_straight(36, 60, 60, false);
            drive_arc(90, WHEEL_TO_WHEEL_DIST , 60, 60, false, false);


            break;
            // release_intake();
            // intake.spin(DIR_FWD, 50, PCT_PCT);
            drive_straight(3, 48, 48);
            wait(250, vex::msec);
            // intake.stop(vex::brakeType::hold);
            // Position for next
            drive_turn(180, WHEEL_TO_WHEEL_DIST / 2, 48, 48);
            drive_straight(12, 48, 48);
            drive_turn(-50, WHEEL_TO_WHEEL_DIST + 2, 48, 48);
            break;


            drive_straight(-31, 72, 54);
            drive_turn(-45, WHEEL_TO_WHEEL_DIST, 48, 36, true);
            drive_straight(-12, 48, 36);
            // Slap it out
            // smith.set(1);
            drive_turn(-45, WHEEL_TO_WHEEL_DIST, 36, 24, true);
            drive_straight(-8, 54, 48);
            // Line up
            drive_l.spin(DIR_FWD, -50, PCT_PCT);
            wait(650, vex::msec);
            target_heading -= 15;       // effectively turn 15 degrees left
            drive_straight(13, 60, 48);
            // smith.set(0);
            drive_turn(-165, WHEEL_TO_WHEEL_DIST / 2, 54, 36);
            drive_straight(1, 48, 24);      // tries to correct angle
            // Slam stuff in
            // intake.spin(DIR_FWD, -100, PCT_PCT);
            drive_r.spin(DIR_FWD, 100, PCT_PCT);
            drive_l.spin(DIR_FWD, 100, PCT_PCT);
            wait(650, vex::msec);
            drive_straight(-14, 60, 48);
            drive_r.spin(DIR_FWD, 100, PCT_PCT);
            drive_l.spin(DIR_FWD, 100, PCT_PCT);
            wait(650, vex::msec);
            // intake.stop(vex::brakeType::coast);
            drive_straight(-10, 60, 48);
            // Pzth to one of the middle triballs
            drive_turn(-90, WHEEL_TO_WHEEL_DIST / 2, 48, 48);
            drive_straight(46, 84, 56);
            break;

        case SKILLS:
            release_intake();
            // // sys3.spin(DIR_FWD, 68, VEL_PCT);
            wait(60, vex::sec);
            // puncher.stop();
            drive_straight(4, 48, 48);
            drive_turn(58, WHEEL_TO_WHEEL_DIST / 2, 48, 48);
            drive_straight(20, 48, 48);
            drive_turn(-35, WHEEL_TO_WHEEL_DIST / 2, 48, 48);
            drive_straight(48, 48, 48);
            drive_straight(-12, 48, 48);
            hang.set(1);
            drive_straight(36, 48, 48);
            drive_straight(-5, 48, 48);
            drive_straight(5, 48, 48);
            break;
    }
}
