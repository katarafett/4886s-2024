#include "main.h"
#include "stddefs.h"
#include "vex_global.h"
#include "vex_units.h"

void release_antenna(void);

void autonomous(void) {
    while (imu.isCalibrating()) {
        wait(20, vex::msec);
    }
    switch (auton_mode) {
    case FULL_AWP: {
        intakeLow.spin(DIR_FWD, 100, PCT_PCT);
        wait(250, TIME_MSEC);
        drive_straight(-6, 30, 70);
        turn_pid(65, -1, 1);
        drive_straight(5, 30, 70);
        lift.spinToPosition(170 * 4, ROT_DEG, 200, VEL_RPM);
        drive_straight(-15, 30, 70);
        lift.spinToPosition(-40 * 4, ROT_DEG, 200, VEL_RPM, false);
        turn_pid(47, -1, 1);
        drive_straight(-24, 30, 70);
        mogo_clamp.set(1);
        wait(250, TIME_MSEC);
        intake.spin(DIR_FWD, 100, PCT_PCT);
        turn_pid(95, -1, 1);
        drive_straight(20, 30, 70);
        drive_straight(-20, 30, 70);
        // push teamnate
        turn_pid(70, -1, 1);
        drive_straight(-36, 30, 70);
        turn_pid(-85, -1, 1);
        drive_straight(-23, 75, 70);
        drive_straight(5, 30, 70);
        turn_pid(110, -1, 1);
        lift.spinToPosition(180 * 4, ROT_DEG, 200, VEL_RPM, false);
        drive_straight(23, 30, 70);


        break;
    }
    case BLUE_QUAD: {
        // score on AWS
        drive_straight(3, 50, 50);
        lift.spinToPosition(164 * 4, ROT_DEG, 150, VEL_RPM);
        // pickup ring 2 with smith mech
        drive_straight(-12, 50, 50);
        lift.spinToPosition(-40 * 4, ROT_DEG, 200, VEL_RPM, false);
        turn_pid(65, -1, 1);
        // push teammate
        drive_straight(16, 50, 50);
        drive_straight(-5, 50, 50);
        // go for MOGO
        turn_pid(-80, -1, 1);
        drive_straight(-36, 50, 100);
        wait(250, TIME_MSEC);
        mogo_clamp.set(1);
        drive_straight(-1, 20, 50);
        intake.spin(DIR_FWD, 100, PCT_PCT);
        // quad stack
        turn_pid(140, -1, 1);
        drive_straight(-8, 20, 50);
        drive_turn(90, 18, 40, 75, false);
        drive_straight(10, 20, 50);
        drive_straight(-14, 20, 50);
        // double stack
        drive_turn(185, 14, 75, 75, false);
        drive_straight(31, 65, 100);

        break;
    }


    case BLUE_RUSH: {
        break;
    }


    case RED_RUSH: {
        lift.spinToPosition(145 * 4, ROT_DEG, 200, VEL_RPM, false);
        drive_straight(38.5, 75, 100);
        lift.spinToPosition(190 * 4, ROT_DEG, 200, VEL_RPM, true);
        drive_straight(-5, 30, 70);
        turn_pid(55, -1, 1);
        // goal 2
        drive_straight(-18, 30, 70);
        lift.spinToPosition(-45 * 4, ROT_DEG, 200, VEL_RPM, false);
        mogo_clamp.set(1);
        wait(250, TIME_MSEC);
        intake.spin(DIR_FWD, 100, PCT_PCT);
        turn_pid(10, -1, 1);
        drive_straight(28, 75, 70);
        // ring 3
        turn_pid(143, -1, 1);
        drive_straight(41, 75, 70);
        Smith_Mech.set(1);
        drive_straight(-10, 75, 70);
        Smith_Mech.set(0);
        wait(200, TIME_MSEC);
        turn_pid(25, -1, 1);
        lift.spinToPosition(0 * 4, ROT_DEG, 200, VEL_RPM, false);
        drive_straight(15, 75, 70);
        drive_straight(-10, 75, 70);
        turn_pid(-56, -1, 1);
        drive_straight(17, 75, 70);
        intake.stop();
        lift.spinToPosition(170 * 4, ROT_DEG, 200, VEL_RPM);
        drive_straight(-18, 75, 70);
        lift.spinToPosition(160 * 4, ROT_DEG, 200, VEL_RPM);
        turn_pid(90, -1, 1);
        drive_straight(18, 30, 70);

        break;
    }


    case RED_QUAD: {
        // score on AWS
        drive_straight(3, 50, 50);
        lift.spinToPosition(164 * 4, ROT_DEG, 150, VEL_RPM);
        // pickup ring 2 with smith mech
        drive_straight(-15, 50, 50);
        lift.spinToPosition(-40 * 4, ROT_DEG, 200, VEL_RPM, false);
        turn_pid(50, -1, 1);
        drive_straight(-27, 30, 100);
        mogo_clamp.set(1);
        drive_straight(-1, 20, 50);
        wait(250, TIME_MSEC);
        intake.spin(DIR_FWD, 100, PCT_PCT);
        // quad stack
        turn_pid(130, -1, 1);
        drive_straight(14, 20, 50);
        turn_pid(-45, -1, 1);
        drive_straight(15, 20, 50);
        turn_pid(-90, -1, 1);
        drive_straight(25, 40, 50);


        break;
    }


    case ELIMS_RED: {
        // score on AWS
        lift.spinToPosition(130 * 4, ROT_DEG, 200, VEL_RPM, false);
        wait(150, TIME_MSEC);
        drive_straight(5, 50, 50);
        // pickup ring 2 with smith mech
        drive_straight(-11, 50, 50);
        lift.spinToPosition(3 * 4, ROT_DEG, 200, VEL_RPM, false);
        turn_pid(-25, -1, 1);
        drive_straight(4, 50, 50);
        Smith_Mech.set(1);
        // go for MOGO
        drive_straight(-6, 50, 50);
        drive_turn(95, -7, 75, 75, false);
        intake.spin(DIR_FWD, 100, PCT_PCT);
        drive_straight(-26, 75, 75);
        mogo_clamp.set(1);
        Smith_Mech.set(0);
        drive_straight(-1, 20, 50);

        turn_pid(180, -1, 1);
        drive_straight(-4, 20, 50);
        drive_turn(-90, -23, 40, 75, false);
        drive_straight(3, 20, 50);
        drive_straight(-12, 20, 50);

        drive_turn(-70, -14, 40, 75, false);
        drive_straight(10, 75, 100);
        drive_straight(-12, 20, 50);
        drive_turn(-75, -14, 40, 75, false);
        drive_straight(33, 75, 100);


        break;
    }


    case SKILLS: {
        // first ring
        lift.spinToPosition(162 * 4, ROT_DEG, 150, VEL_RPM);
        drive_straight(-20, 50, 50);
        mogo_clamp.set(1);
        wait(350, TIME_MSEC);
        lift.spinToPosition(-40 * 4, ROT_DEG, 200, VEL_RPM, false);
        turn_pid(-135, -1, 1);
        intake.spin(DIR_FWD, 12, VLT_VLT);
        drive_straight(20, 75, 75);
        turn_pid(-90, -1, 1);
        drive_straight(21, 75, 75);
        // third
        turn_pid(-60, -1, 1);
        drive_straight(23, 75, 75);
        // fourth
        wait(300, TIME_MSEC);
        drive_straight(-23, 75, 75);
        turn_pid(-30, -1, 1);
        drive_straight(21, 75, 75);
        // fifth
        drive_straight(12, 15, 75);
        // put mogo in corner
        turn_pid(-110, -1, 1);
        drive_straight(-10, 20, 75);
        mogo_clamp.set(0);
        intake.spin(DIR_REV, 12, VLT_VLT);


        // second MOGO
        intake.stop();
        drive_straight(33, 75, 75);
        turn_pid(-159, -1, 1);
        drive_straight(-48, 50, 75);
        mogo_clamp.set(1);
        wait(350, TIME_MSEC);
        // first ring
        turn_pid(88, -1, 1);
        intake.spin(DIR_FWD, 12, VLT_VLT);
        drive_straight(21, 75, 75);
        // second
        turn_pid(92, -1, 1);
        drive_straight(20, 75, 75);
        // third
        turn_pid(60, -1, 1);
        drive_straight(23, 75, 75);
        // fourth
        wait(300, TIME_MSEC);
        drive_straight(-22, 75, 75);
        turn_pid(30, -1, 1);
        drive_straight(21, 75, 75);
        // fifth
        drive_straight(12, 15, 75);
        // put MOGO in corner
        turn_pid(110, -1, 1);
        drive_straight(-10, 20, 75);
        mogo_clamp.set(0);
        wait(250, TIME_MSEC);
        //imu.setRotation(0, ROT_DEG);
        intake.spin(DIR_REV, 12, VLT_VLT);


        // reset imu
        drive_straight(5, 40, 75);
        turn_pid(70, -1, 1);
        mogo_clamp.set(1);
        /*drive_full.spinFor(DIR_REV, 1000, TIME_MSEC, 30, VEL_PCT);*/
        wait(200, TIME_MSEC);
        reset_imu_rotation();

        // wall stake
        lift.spinToPosition(4 * 4, ROT_DEG, 100, VEL_PCT, false);
        drive_straight(55, 40, 50);
        intake.spin(DIR_FWD, 12, VLT_VLT);
        drive_turn(90, 13, 50, 75);
        wait(1000, TIME_MSEC);
        drive_straight(2, 40, 50);
        /*drive_full.spinFor(DIR_FWD, 500, TIME_MSEC, 20, VEL_PCT);*/
        intakeHigh.spinFor(-90, ROT_DEG, 100, VEL_PCT);
        lift.spinToPosition(150 * 4, ROT_DEG, 100, VEL_PCT, false);
        wait(500, TIME_MSEC);
        drive_straight(-2, 40, 50);
        drive_straight(2, 40, 50);
        drive_straight(-13, 40, 50);
        lift.spinToPosition(-40 * 4, ROT_DEG, 100, VEL_PCT, false);
        turn_pid(-90, -1, 1);
        drive_straight(11, 40, 50);
        intake.stop();

        // thrid MOGO
        intakeLow.spin(DIR_FWD, 12, VLT_VLT);
        mogo_clamp.set(0);
        // first ring
        drive_straight(15, 20, 50);
        wait(500, TIME_MSEC);
        // MOGO
        turn_pid(115, -1, 1);
        drive_straight(-56, 40, 50);
        mogo_clamp.set(1);
        wait(350, TIME_MSEC);
        // second
        intake.spin(DIR_FWD, 12, VLT_VLT);

        turn_pid(20, -1, 1);
        drive_straight(31, 40, 50);
        // third
        turn_pid(90, -1, 1);
        wait(500, TIME_MSEC);
        drive_straight(35, 40, 50);
        // fourth
        turn_pid(100, -1, 1);
        drive_straight(33, 40, 50);
        // fifth
        turn_pid(-55, -1, 1);
        drive_straight(35, 40, 50);
        // put MOGO in corner
        turn_pid(-105, -1, 1);
        intake.spin(DIR_REV, 12, VLT_VLT);
        mogo_clamp.set(0);
        drive_straight(-34, 40, 50);
        intake.spin(DIR_REV, 12, VLT_VLT);
        drive_straight(23, 40, 50);
        turn_pid(-90, -1, 1);
        drive_straight(120, 50, 1000);
        drive_straight(-10, 75, 1000);

        break;
    }
    }
}
