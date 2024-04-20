#include "../include/main.h"
#include "stddefs.h"
#include "vex_global.h"
#include "vex_units.h"

void release_antenna(void);

void autonomous(void) {
    auton_mode = NEAR_LO;

    // Ensure inerital is calibrated
    while (imu.isCalibrating())
        wait(20, vex::msec);
    imu.resetRotation();

    switch (auton_mode) {
    case TESTING:
        break;

    case NEAR_HI: {
        // Release intake
        intake.spinFor(DIR_FWD, 1, ROT_REV, 100, VEL_PCT, false);
        // Prep for alliance triball shove
        wing_fl.set(1);

        // Rush triball
        vex::thread t1([] {
            drive_straight(46.5, 84, 200);
        });
        while (pos_drive_l() < 4) // wait until we've moved ten inches
            vex::wait(10, vex::msec);
        intake.spin(DIR_FWD, 100, VEL_PCT);
        wing_fl.set(0);
        t1.join();

        // Flip
        wait(100, vex::msec);
        drive_straight(-4, 84, 200);
        turn_pid(80, -1, 1);
        intake.spin(DIR_FWD, -100, VEL_PCT);
        drive_straight(18, 84, 200);
        wait(150, vex::msec);

        // Reset IMU
        drive_straight(-6, 84, 200);
        turn_pid(-55, -1, 1);
        drive_straight(-26, 84, 200);
        turn_pid(55, -1, 1);
        drive_straight(-8, 35, 200, false);
        drive_full.spin(DIR_FWD, -35, VEL_PCT);
        wait(800, vex::msec);
        imu.resetRotation();
        target_heading = 0;
        drive_full.stop();

        // AWP
        intake.spin(DIR_FWD, -100, VEL_PCT);
        drive_straight(5, 84, 200);
        turn_pid(-90, -1, 1);
        wing_fl.set(1);
        drive_straight(-5, 32, 48);
        drive_turn(-90, WHEEL_TO_WHEEL_DIST, 60, 60, true);
        turn_pid(-150, -1, 1);
        drive_straight(7, 84, 200);
        turn_pid(-30, -1, 1);
        drive_straight(28.5, 66, 84);
        drive_straight(-1.25, 66, 84);
        wing_fl.set(0);
        break;
    }

    case NEAR_LO:
        intake.spinFor(DIR_FWD, 1, ROT_REV, 100, VEL_PCT, true);
        intake.spinFor(DIR_FWD, -2, ROT_REV, 100, VEL_PCT, true);
        break;

    case FAR_LO:
        // Release intake
        intake.spinFor(DIR_FWD, 1, ROT_REV, false);
        drive_straight(-38, 48, 48);
        drive_straight(12, 48, 48);
        break;

    case FAR_HI:
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
        // Shoot
        // cata.spin(DIR_FWD, 100, VEL_PCT);
        // wait(3, vex::sec);
        // cata.stop();
        intake.stop();
        // cata.spinFor(46, ROT_REV, 100, VEL_PCT, true);
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
        drive_l.spin(DIR_FWD, -12, VLT_VLT);
        drive_r.spin(DIR_FWD, -12, VLT_VLT);
        // ram1_dir = imu_rotation() + 35;
        target_heading += 35;
        drive_straight(6, 72, 200);
        // Wings 2
        turn_pid(-30, -1, 1);
        drive_straight(30, 72, 200);
        turn_pid(120, -1, 1);
        drive_straight(52, 72, 200);
        turn_pid(-55, -1, 1);
        drive_l.spin(DIR_FWD, -12, VLT_VLT);
        drive_r.spin(DIR_FWD, -12, VLT_VLT);
        // ram1_dir = imu_rotation() - 35;
        target_heading -= 35;
        drive_straight(6, 72, 200);
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
        target_heading = -60; // Ensure turn is proper
        drive_straight(-6, 72, 72);
        turn_pid(0, -1, 1);
        drive_l.stop();
        drive_r.stop();
        opcontrol();
        break;
    }
}
