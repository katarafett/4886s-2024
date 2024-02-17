#include "../include/main.h"
#include "stddefs.h"
#include "vex_global.h"
#include "vex_units.h"

void release_antenna(void);

void autonomous(void) {
    float ram1_dir;
    float ram2_dir;
    // Ensure inerital is calibrated
    while (inrtl.isCalibrating())
        wait(20, vex::msec);
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
            intake.spin(DIR_FWD, 100, VEL_PCT);
            //  Slap into goal
            wing_fl.set(1);
            wait(250, vex::msec);
            wing_fl.set(0);
            // Knock out
            wing_bl.set(1);
            wait(100, vex::msec);
            turn_pid(-45, -1, 1);
            wing_bl.set(0);
            // Path to center triball
            intake.spin(DIR_FWD, 100, VEL_PCT);
            drive_turn(95, WHEEL_TO_WHEEL_DIST / 1.5, 72, 72, false);
            drive_turn(-50, WHEEL_TO_WHEEL_DIST * 2.8, 76, 72, false);
            drive_straight(17.5, 72, 200);
            // Grab triball
            wait(400, vex::msec);
            intake.stop(vex::brakeType::hold);
            // Path to flip
            drive_straight(-1.75, 72, 72);
            turn_pid(90, -1, 1);
            drive_l.stop();
            drive_r.stop();
            // Flip
            wing_fl.set(1);
            wait(200, vex::msec);
            drive_l.spin(DIR_FWD, 9, VLT_VLT);
            drive_r.spin(DIR_FWD, 9, VLT_VLT);
            wait(400, vex::msec);
            wing_fl.set(0);
            // Intake-flip
            intake.spin(DIR_FWD, -100, VEL_PCT);
            drive_straight(-7, 72, 72);
            drive_l.spin(DIR_FWD, 5, VLT_VLT);
            drive_r.spin(DIR_FWD, 5, VLT_VLT);
            wait(450, vex::msec);
            drive_straight(-4, 72, 72);
            // Path to goal
            drive_turn(-45, WHEEL_TO_WHEEL_DIST * 1.5, 72, 72, true);
            drive_straight(-38, 72, 72);
            // Slap in
            intake.stop(vex::brakeType::coast);
            // Push under bar
            drive_turn(-135, WHEEL_TO_WHEEL_DIST * 0.74, 72, 72, true);
            drive_straight(-36, 72, 72);
            drive_straight(6, 72, 72);
            wing_br.set(1);
            drive_turn(20, WHEEL_TO_WHEEL_DIST, 48, 48, true);
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
            target_heading = 45;
            intake.spin(DIR_FWD, 100, VEL_PCT);
            // Shove under
            drive_turn(45, WHEEL_TO_WHEEL_DIST * 0.77, 72, 72, true);
            drive_l.spin(DIR_FWD, -12, VLT_VLT);
            drive_r.spin(DIR_FWD, -12, VLT_VLT);
            wait(650, vex::msec);
            // Line up
            drive_straight(12, 72, 80);
            turn_pid(-107, -1, 1);
            drive_straight(-6, 72, 80);
            turn_pid(0, -1, 1);
            drive_l.stop(vex::brakeType::hold);
            drive_r.stop(vex::brakeType::hold);
            wing_br.set(1);
            // Shoot
            // cata.spin(DIR_FWD, 100, VEL_PCT);
            // wait(3, vex::sec);
            // cata.stop();
            cata.spinFor(46, ROT_REV, 100, VEL_PCT, true);
            wing_br.set(0);
            // Run through alley
            drive_turn(107, WHEEL_TO_WHEEL_DIST * 1.65, 72, 84, false);
            drive_straight(7, 72, 200);
            turn_pid(90, -1, 1);
            drive_straight(-76, 84, 200);
            turn_pid(-45, -1, 1);
            drive_straight(-24, 84, 200);
            turn_pid(-45, -1, 1);
            // Ram under goal
            drive_l.spin(DIR_FWD, -12, VLT_VLT);
            drive_r.spin(DIR_FWD, -12, VLT_VLT);
            wait(700, vex::msec);
            drive_straight(6, 72, 80);
            // Wings 1
            turn_pid(100, -1, 1);
            drive_straight(48, 72, 200);
            turn_pid(-45, -1, 1);
            wing_br.set(1);
            wing_bl.set(1);
            drive_l.spin(DIR_FWD, -12, VLT_VLT);
            drive_r.spin(DIR_FWD, -12, VLT_VLT);
            ram1_dir = ROTATION * GYRO_CORRECTION + 35;
            do {
                wait(10, vex::msec);
            } while (ROTATION * GYRO_CORRECTION < ram1_dir);
            target_heading += 35;
            drive_straight(6, 72, 200);
            wing_br.set(0);
            wing_bl.set(0);
            // Wings 2
            turn_pid(-30, -1, 1);
            drive_straight(30, 72, 200);
            turn_pid(120, -1, 1);
            drive_straight(54, 72, 200);
            turn_pid(-55, -1, 1);
            wing_br.set(1);
            wing_bl.set(1);
            drive_l.spin(DIR_FWD, -12, VLT_VLT);
            drive_r.spin(DIR_FWD, -12, VLT_VLT);
            ram1_dir = ROTATION * GYRO_CORRECTION - 35;
            do {
                wait(10, vex::msec);
            } while (ROTATION * GYRO_CORRECTION > ram1_dir);
            target_heading -= 35;
            drive_straight(6, 72, 200);
            wing_br.set(0);
            wing_bl.set(0);
            drive_straight(12, 72, 200);
            turn_pid(360, -1, 1);
            break;

        case SKILLS_DRIVER:
            intake.spin(DIR_FWD, 100, VEL_PCT);
            // Shove under
            drive_turn(45, WHEEL_TO_WHEEL_DIST * 0.75, 72, 72, true);
            drive_l.spin(DIR_FWD, -12, VLT_VLT);
            drive_r.spin(DIR_FWD, -12, VLT_VLT);
            wait(600, vex::msec);
            // Line up
            drive_straight(12, 72, 72);
            turn_pid(-120, -1, 1);
            target_heading = -60;    // Ensure turn is proper
            drive_straight(-6, 72, 72);
            turn_pid(0, -1, 1);
            drive_l.stop();
            drive_r.stop();
            wing_br.set(1);
            wing_bl.set(1);
            opcontrol();
            break;
    }
}
