#include "../include/main.h"
#include "stddefs.h"
#include "vex_global.h"
#include "vex_units.h"

void release_antenna(void);

void autonomous(void) {
    switch (auton_mode) {
        case AWP:
            /* tune pid */
            break;

        case HALF_AWP_NEAR:
            // release_intake();
            hang.set(1);
            // Knock out
            drive_straight(12, 24, 36);
            smith.set(1);
            drive_turn(45, WHEEL_TO_WHEEL_DIST / 2, 6, 12);
            smith.set(0);
            // Intake it
            drive_turn(-45, WHEEL_TO_WHEEL_DIST / 2, 24, 24);
            intake.spin(DIR_FWD, 50, VEL_PCT);
            drive_straight(8, 24, 24);
            // Line up for push
            drive_turn(180, WHEEL_TO_WHEEL_DIST / 2, 24, 24);
            intake.stop(vex::hold);
            drive_straight(26, 36, 36);
            drive_turn(-45, WHEEL_TO_WHEEL_DIST / 2, 24, 24);
            drive_straight(33, 24, 24);
            // Stop
            intake.spin(DIR_FWD, -100, VEL_PCT);
            break;

        case HALF_AWP_FAR:
            // release_intake();
            hang.set(1);
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
            target_heading -= 15;       // effectively turn 15 degrees left
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
            intake.spin(DIR_FWD, -50, VEL_PCT);
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
            drive_straight(36, 60, 60, false);
            drive_arc(90, WHEEL_TO_WHEEL_DIST , 60, 60, false, false);


            break;
            release_intake();
            intake.spin(DIR_FWD, 50, PCT_PCT);
            drive_straight(3, 48, 48);
            wait(250, vex::msec);
            intake.stop(vex::brakeType::hold);
            // Position for next
            drive_turn(180, WHEEL_TO_WHEEL_DIST / 2, 48, 48);
            drive_straight(12, 48, 48);
            drive_turn(-50, WHEEL_TO_WHEEL_DIST + 2, 48, 48);
            break;


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
            target_heading -= 15;       // effectively turn 15 degrees left
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

        case SKILLS:
            hang.set(1);
            wait(500, vex::msec);
            hang.set(0);
            puncher.spin(DIR_FWD, 100, VEL_PCT);
            wait(40, vex::sec);
            puncher.stop();
            drive_turn(15, WHEEL_TO_WHEEL_DIST / 2, 48, 48);
            drive_straight(36, 48, 48);
            drive_straight(-12, 48, 48);
            hang.set(1);
            drive_straight(36, 48, 48);
            break;
    }
}
