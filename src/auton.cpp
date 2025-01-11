#include "../include/main.h"
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
            // score on AWS
            lift.spinToPosition(130*5, ROT_DEG, 200, VEL_RPM, false);
            wait(150, TIME_MSEC);
            drive_straight(5, 50, 50);
            // pickup ring 2 with smith mech
            drive_straight(-11, 50, 50);
            lift.spinToPosition(3*5, ROT_DEG, 200, VEL_RPM, false);
            turn_pid(-25, -1, 1);
            // push teammate
            drive_straight(16, 50, 50);
            // go for MOGO
            drive_straight(-12, 50, 50);
            drive_turn(90, -6, 40, 75, false);
            drive_full.spinFor(DIR_FWD, 700, TIME_MSEC, 50, VEL_PCT);
            drive_straight(-33, 40, 100);
            wait(200, TIME_MSEC);
            mogo_clamp.set(1);
            wait(200, TIME_MSEC);
            drive_straight(-1, 20, 50);
            // quad stack
            turn_pid(180, -1, 1);
            drive_straight(-5, 20, 50);
            intake.spin(DIR_FWD, 100, PCT_PCT);
            drive_turn(-85, -24, 40, 75, false);
            drive_straight(5, 20, 50);
            drive_straight(-14, 20, 50);
            // double stack
            drive_turn(-190, -14, 75, 75, false);
            drive_straight(30, 65, 100);

            break;
        }
        case BLUE_QUAD: {
            // score on AWS
            lift.spinToPosition(130*5, ROT_DEG, 200, VEL_RPM, false);
            wait(150, TIME_MSEC);
            drive_straight(5, 50, 50);
            // pickup ring 2 with smith mech
            drive_straight(-11, 50, 50);
            lift.spinToPosition(3*5, ROT_DEG, 200, VEL_RPM, false);
            turn_pid(25, -1, 1);
            // push teammate
            drive_straight(16, 50, 50);
            // go for MOGO
            drive_straight(-14, 50, 50);
            drive_turn(-90, 6, 40, 75, false);
            drive_full.spinFor(DIR_FWD, 400, TIME_MSEC, 30, VEL_PCT);
            drive_straight(-34.5, 40, 100);
            intake.spin(DIR_FWD, 100, PCT_PCT);
            wait(250, TIME_MSEC);
            mogo_clamp.set(1);
            // quad stack
            turn_pid(-180, -1, 1);
            drive_straight(-2, 20, 50);
            drive_turn(85, 23, 40, 75, false);
            drive_straight(5, 20, 50);
            drive_straight(-14, 20, 50);
            // double stack
            drive_turn(185, 14, 75, 75, false);
            drive_straight(32, 65, 100);
            break;
        }


        case BLUE_RUSH: {
            // score on AWS
            lift.spinToPosition(130*5, ROT_DEG, 200, VEL_RPM, false);
            wait(150, TIME_MSEC);
            drive_straight(5, 50, 50);
            // pickup ring 2 with smith mech
            drive_straight(-4, 50, 50);
            lift.spinToPosition(3*5, ROT_DEG, 200, VEL_RPM, false);
            turn_pid(52, -1, 1);
            drive_straight(-36, 50, 50);
            intake.spin(DIR_FWD, 100, PCT_PCT);
            mogo_clamp.set(1);
            turn_pid(110, -1, 1);
            drive_straight(25, 75, 100);
            drive_straight(-11, 50, 50);
            wait(1000, TIME_MSEC);
            mogo_clamp.set(0);
            drive_straight(5, 50, 50);
            turn_pid(-90, -1, 1);
            drive_straight(-17, 50, 50);
            mogo_clamp.set(1);
            turn_pid(-10, -1, 1);
            Smith_Mech.set(1);
            drive_straight(-56, 50, 50);
            turn_pid(-90, -1, 1);
            turn_pid(20, -1, 1);
            drive_straight(10, 50, 50);
            drive_straight(-6, 50, 50);

            break;
        }


        case RED_RUSH:{
            // score on AWS
            lift.spinToPosition(130*5, ROT_DEG, 200, VEL_RPM, false);
            wait(150, TIME_MSEC);
            drive_straight(5, 50, 50);
            // MOGO
            drive_straight(-4, 50, 50);
            lift.spinToPosition(3*5, ROT_DEG, 200, VEL_RPM, false);
            turn_pid(-52, -1, 1);
            drive_straight(-36, 50, 50);
            mogo_clamp.set(1);
            intake.spin(DIR_FWD, 100, PCT_PCT);
            // second ring
            turn_pid(-105, -1, 1);
            drive_straight(25, 75, 100);
            drive_straight(-9, 50, 50);
            wait(1000, TIME_MSEC);
            mogo_clamp.set(0);
            // MOGO 2
            drive_straight(5, 50, 50);
            turn_pid(90, -1, 1);
            drive_straight(-20, 50, 50);
            mogo_clamp.set(1);
            // corner
            drive_straight(20, 50, 50);
            turn_pid(-19, -1, 1);
            Smith_Mech.set(1);
            drive_straight(50, 30, 50);
            turn_pid(100, -1, 1);
            Smith_Mech.set(0);
            turn_pid(-20, -1, 1);
            drive_straight(15, 50, 50);
            turn_pid(-45, -1, 1);
            drive_straight(-40, 50, 50);
            break;
        }


        case RED_QUAD:{
            // score on AWS
            lift.spinToPosition(130*5, ROT_DEG, 200, VEL_RPM, false);
            wait(150, TIME_MSEC);
            drive_straight(5, 50, 50);
            // pickup ring 2 with smith mech
            drive_straight(-11, 50, 50);
            lift.spinToPosition(3*5, ROT_DEG, 200, VEL_RPM, false);
            turn_pid(-25, -1, 1);
            // push teammate
            drive_straight(16, 50, 50);
            // go for MOGO
            drive_straight(-14, 50, 50);
            drive_turn(90, -6, 40, 75, false);
            drive_full.spinFor(DIR_FWD, 500, TIME_MSEC, 60, VEL_PCT);
            drive_straight(-32, 75, 100);
            intake.spin(DIR_FWD, 100, PCT_PCT);
            wait(250, TIME_MSEC);
            mogo_clamp.set(1);
            drive_straight(-2, 20, 50);
            // quad stack
            turn_pid(180, -1, 1);
            drive_straight(-5, 20, 50);
            drive_turn(-85, -23, 40, 75, false);
            drive_straight(5, 20, 50);
            drive_straight(-14, 20, 50);
            // double stack
            drive_turn(-185, -14, 75, 75, false);
            drive_straight(32, 65, 100);
        }


        case ELIMS_RED:{

            // score on AWS
            lift.spinToPosition(130*5, ROT_DEG, 200, VEL_RPM, false);
            wait(150, TIME_MSEC);
            drive_straight(5, 50, 50);
            // pickup ring 2 with smith mech
            drive_straight(-11, 50, 50);
            lift.spinToPosition(3*5, ROT_DEG, 200, VEL_RPM, false);
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


case SKILLS:{

// first ring
lift.spinToPosition(125*5, ROT_DEG, 200, VEL_RPM);
wait(150, TIME_MSEC);
lift.spinToPosition(2*5, ROT_DEG, 200, VEL_RPM, false);
drive_straight(-21,50,50);
mogo_clamp.set(1);
turn_pid(-125, -1, 1); 
intake.spin(DIR_FWD, 12, VLT_VLT);
drive_straight(20,75,75);
turn_pid(-90, -1, 1);
drive_straight(21,75,75);
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



// second MOGO
drive_straight(33,  75, 75);
turn_pid(-159, -1, 1);
drive_straight(-48,  50, 75);
mogo_clamp.set(1);
// first ring
turn_pid(88, -1, 1);
drive_straight(21,  75, 75);
// second
turn_pid(92, -1, 1);
drive_straight(20,  75, 75);
// third
turn_pid(60, -1, 1);
drive_straight(23,  75, 75);
// fourth
wait(300, TIME_MSEC);
drive_straight(-22,  75, 75);
turn_pid(30, -1, 1);
drive_straight(21,  75, 75);
// fifth
drive_straight(12, 15, 75);
// put MOGO in corner
turn_pid(110, -1, 1);
drive_straight(-10, 20, 75);
mogo_clamp.set(0);
wait(250, TIME_MSEC);
//imu.setRotation(0, ROT_DEG);
intakeHigh.stop();

// reset imu
drive_straight(5, 40, 75);
turn_pid(70, -1, 1);
mogo_clamp.set(1);
drive_full.spinFor(DIR_REV, 1000, TIME_MSEC, 30, VEL_PCT);
wait(200,TIME_MSEC);
reset_imu_rotation();

// wall stake 
lift.spinToPosition(36 * 5, ROT_DEG, 100, VEL_PCT, false);
drive_straight(55, 40, 50);
intake.spin(DIR_FWD, 12, VLT_VLT);
drive_turn(90, 13, 50, 75);
wait(1000, TIME_MSEC);
drive_straight(2, 40, 50);
drive_full.spinFor(DIR_FWD, 500, TIME_MSEC, 20, VEL_PCT);
intakeHigh.spinFor(-90, ROT_DEG, 100, VEL_PCT);
lift.spinToPosition(140 * 5, ROT_DEG, 100, VEL_PCT);
lift.spinToPosition(5 * 5, ROT_DEG, 100, VEL_PCT, false);
drive_straight(-13, 40, 50);
turn_pid(-90, -1, 1);
drive_straight(11, 40, 50);


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
drive_straight(122, 50, 1000);
           break;
            }
        }
}