#include "../include/main.h"
#include "stddefs.h"
#include "vex_global.h"
#include "vex_units.h"

void red_sort(void);
void blue_sort(void);

void autonomous(void) {
    while (imu.isCalibrating()) {
        wait(20, vex::msec);
    }

drive_full.setStopping(vex::hold);
lift.resetPosition();
    switch (auton_mode) {
    case FULL_AWP: {

intakeLow.spin(DIR_FWD, 100, PCT_PCT);
drive_straight(3, 30, 70);
drive_straight(-10, 30, 70);
turn_pid(67, -1, 1);
drive_straight(6, 30, 70);
lift.spinToPosition(170 * 4, ROT_DEG, 200, VEL_RPM);
drive_straight(-16, 30, 70);
lift.spinToPosition(-40 * 4, ROT_DEG, 200, VEL_RPM, false);
turn_pid(45, -1, 1);
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
drive_straight(-20, 75, 70);
drive_straight(5, 30, 70);
turn_pid(100, -1, 1);
lift.spinToPosition(138 * 4, ROT_DEG, 200, VEL_RPM, false);
drive_straight(25, 30, 70);
lift.spinToPosition(180 * 4, ROT_DEG, 200, VEL_RPM, false);


        break;
    }
    case BLUE_QUAD: {

// score on AWS
lift.spinToPosition(164 * 4, ROT_DEG, 150, VEL_RPM, false);
drive_straight(2, 50, 50);
wait(250, TIME_MSEC);
// pickup ring 2 with smith mech
drive_straight(-14, 50, 50);
lift.spinToPosition(70 * 4, ROT_DEG, 150, VEL_RPM, false);
turn_pid(-51, -1, 1);
drive_straight(-33, 40, 100);
mogo_clamp.set(1);
wait(400, TIME_MSEC);
vex::thread t1 (red_sort);
// quad stack
turn_pid(-180, -1, 1);
wait(200, TIME_MSEC);
drive_straight(-6, 30, 100);
drive_turn(90, 18, 40, 75, false);
drive_straight(14, 20, 100);
wait(250, TIME_MSEC);
drive_straight(-10, 40, 100);
wait(250, TIME_MSEC);
drive_turn(-85, 18, 50, 75, true);
turn_pid(85, -1, 1);
drive_straight(16, 30, 50);
drive_straight(-9, 30, 50);
turn_pid(-150, -1, 1);
drive_straight(20, 40, 50);
t1.interrupt();
lift.spinToPosition(160 * 4, ROT_DEG, 150, VEL_RPM, false);

        break;
    }


    case BLUE_RUSH: {

lift.spinToPosition(145 * 4, ROT_DEG, 200, VEL_RPM, false);
drive_straight(38.5, 75, 100);
lift.spinToPosition(190 * 4, ROT_DEG, 200, VEL_RPM, true);
drive_straight(-5, 30, 70);
turn_pid(-55, -1, 1);
// goal 2
drive_straight(-18, 30, 70);
lift.spinToPosition(-45 * 4, ROT_DEG, 200, VEL_RPM, false);
mogo_clamp.set(1);
wait(250, TIME_MSEC);
vex::thread t1 (blue_sort);
turn_pid(-10, -1, 1);
drive_straight(28, 75, 70);
// ring 3
turn_pid(165, -1, 1);
lift.spinToPosition(140 * 4, ROT_DEG, 200, VEL_RPM, false);
drive_straight(35, 75, 70);
lift.spinToPosition(180 * 4, ROT_DEG, 200, VEL_RPM, false);

t1.interrupt();

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
vex::thread t1 (red_sort);
turn_pid(10, -1, 1);
drive_straight(28, 75, 70);
// ring 3
turn_pid(152, -1, 1);
drive_straight(41, 75, 70);
Smith_Mech.set(1);
drive_straight(-10, 75, 70);
Smith_Mech.set(0);
wait(500, TIME_MSEC);
turn_pid(25, -1, 1);
lift.spinToPosition(0 * 4, ROT_DEG, 200, VEL_RPM, false);
drive_straight(15, 75, 70);
drive_straight(-10, 75, 70);
turn_pid(-56, -1, 1);
drive_straight(17, 75, 70);
lift.spinToPosition(170 * 4, ROT_DEG, 200, VEL_RPM, false);
t1.interrupt();
intake.spinFor(-90, ROT_DEG, 100, VEL_PCT);
wait(300, TIME_MSEC);
drive_straight(-18, 75, 70);
lift.spinToPosition(140 * 4, ROT_DEG, 200, VEL_RPM, false);
turn_pid(115, -1, 1);
drive_straight(12, 30, 70);
t1.interrupt();
        break;
    }


    case RED_QUAD: {

// score on AWS
lift.spinToPosition(164 * 4, ROT_DEG, 150, VEL_RPM, false);
drive_straight(2, 50, 50);
wait(250, TIME_MSEC);
// pickup ring 2 with smith mech
drive_straight(-14, 50, 50);
lift.spinToPosition(70 * 4, ROT_DEG, 150, VEL_RPM, false);
turn_pid(51, -1, 1);
drive_straight(-33, 40, 100);
mogo_clamp.set(1);
wait(400, TIME_MSEC);
vex::thread t1 (red_sort);
// quad stack
turn_pid(180, -1, 1);
wait(200, TIME_MSEC);
drive_straight(-6, 30, 100);
drive_turn(-90, -18, 40, 75, false);
drive_straight(14, 20, 100);
wait(250, TIME_MSEC);
drive_straight(-10, 40, 100);
wait(250, TIME_MSEC);
drive_turn(85, -18, 50, 75, true);
turn_pid(-85, -1, 1);
drive_straight(16, 30, 50);
drive_straight(-9, 30, 50);
turn_pid(150, -1, 1);
drive_straight(20, 40, 50);
t1.interrupt();
lift.spinToPosition(160 * 4, ROT_DEG, 150, VEL_RPM, false);


        break;
    }


    case ELIMS_RED: {

intakeLow.spin(DIR_FWD, 100, PCT_PCT);
drive_straight(43, 70, 100);
wait(300, TIME_MSEC);
drive_straight(-2, 30, 100);
turn_pid(-40, -1, 1);
drive_straight(-22, 50, 50);
mogo_clamp.set(1);
wait(300, TIME_MSEC);
vex::thread t1 (red_sort);
turn_pid(-30, -1, 1);
drive_straight(32, 75, 100);
drive_straight(-1, 75, 100);
turn_pid(80, -1, 1);
drive_straight(13, 75, 100);
wait(200, TIME_MSEC);
drive_straight(-13, 75, 100);
turn_pid(-151, -1, 1);
drive_straight(57, 50, 100);
wait(1200, TIME_MSEC);
drive_turn(15, -12, 30, 75, true);
drive_straight(-15, 30, 100);
turn_pid(-115, -1, 1);
t1.interrupt();
drive_straight(80, 75, 500);

        break;
    }

    case ELIMS_BLUE: {

intakeLow.spin(DIR_FWD, 100, PCT_PCT);
drive_straight(43, 70, 100);
wait(300, TIME_MSEC);
drive_straight(-2, 30, 100);
turn_pid(40, -1, 1);
drive_straight(-22, 50, 50);
mogo_clamp.set(1);
wait(300, TIME_MSEC);
vex::thread t1 (blue_sort);
turn_pid(30, -1, 1);
drive_straight(32, 75, 100);
drive_straight(-1, 75, 100);
turn_pid(-80, -1, 1);
drive_straight(13, 75, 100);
wait(200, TIME_MSEC);
drive_straight(-13, 75, 100);
turn_pid(151, -1, 1);
drive_straight(57, 50, 100);
wait(1200, TIME_MSEC);
drive_turn(-15, 12, 30, 75, true);
drive_straight(-15, 30, 100);
turn_pid(115, -1, 1);
t1.interrupt();
drive_straight(80, 75, 500);

        break;
    }


case SKILLS: {
// first ring
lift.spinToPosition(162 * 4, ROT_DEG, 150, VEL_RPM);
drive_straight(-18, 50, 50);
mogo_clamp.set(1);
wait(200, TIME_MSEC);
lift.spinToPosition(-40 * 4, ROT_DEG, 200, VEL_RPM, false);
turn_pid(-135, -1, 1);
intake.spin(DIR_FWD, 12, VLT_VLT);
drive_straight(20, 75, 75);
turn_pid(-90, -1, 1);
drive_straight(20, 75, 75);
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
drive_straight(-14, 20, 75);
mogo_clamp.set(0);


// second MOGO
intakeHigh.stop();
drive_straight(34, 75, 75);
turn_pid(-155, -1, 1);
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
drive_straight(-14, 20, 75);
mogo_clamp.set(0);
wait(250, TIME_MSEC);
//imu.setRotation(0, ROT_DEG);
intakeHigh.spinFor(-180, ROT_DEG, 100, VEL_PCT);


// reset imu
drive_straight(4, 40, 75);
turn_pid(70, -1, 1);
drive_full.spinFor(DIR_REV, 500, TIME_MSEC, 30, VEL_PCT);
wait(200, TIME_MSEC);
reset_imu_rotation();

// wall stake
lift.spinToPosition(4 * 4, ROT_DEG, 100, VEL_PCT, false);
drive_straight(50, 40, 50);
intake.spin(DIR_FWD, 12, VLT_VLT);
drive_turn(90, 17, 50, 75);
drive_straight(-2, 40, 50);
drive_straight(2, 40, 50);
wait(1000, TIME_MSEC);
drive_full.spinFor(DIR_FWD, 200, TIME_MSEC, 20, VEL_PCT);
intakeHigh.spinFor(-90, ROT_DEG, 100, VEL_PCT);
lift.spinToPosition(140 * 4, ROT_DEG, 100, VEL_PCT, false);
wait(700, TIME_MSEC);
drive_straight(-4, 40, 50);
drive_straight(2, 40, 50);
drive_straight(-11, 40, 50);
lift.spinToPosition(-40 * 4, ROT_DEG, 100, VEL_PCT, false);
turn_pid(-90, -1, 1);
drive_straight(11, 40, 50);
intake.stop();

// thrid MOGO
intakeLow.spin(DIR_FWD, 12, VLT_VLT);
// first ring
drive_straight(15, 20, 50);
wait(500, TIME_MSEC);
// MOGO
turn_pid(115, -1, 1);
drive_straight(-56, 40, 50);
wait(350, TIME_MSEC);
mogo_clamp.set(1);
// second
intake.spin(DIR_FWD, 12, VLT_VLT);
turn_pid(20, -1, 1);
drive_straight(31, 40, 50);
// third
turn_pid(90, -1, 1);
wait(500, TIME_MSEC);
drive_straight(33, 40, 50);
// fourth
turn_pid(90, -1, 1);
drive_straight(33, 40, 50);
// fifth
turn_pid(-45, -1, 1);
drive_straight(35, 40, 50);
// put MOGO in corner
turn_pid(-105, -1, 1);
intake.spin(DIR_REV, 12, VLT_VLT);
mogo_clamp.set(0);
drive_straight(-34, 70, 100);
intake.spin(DIR_REV, 12, VLT_VLT);
drive_straight(23, 40, 50);
turn_pid(-90, -1, 1);
drive_straight(129, 75, 10000);
drive_straight(3, 75, 1000);
drive_straight(-10, 75, 1000);

        break;
    }
    }
}

void blue_sort() {
    intakeLow.spin(DIR_FWD, 100, VEL_PCT);
    while (true){
        intakeHigh.spin(DIR_FWD, 100, VEL_PCT);
        if (colorSort.isNearObject() && colorSort.color() == vex::color::red) {
            intakeHigh.spinFor(-60, ROT_DEG, 100, VEL_PCT);
        }
    wait(20, TIME_MSEC);
    }
}

void red_sort() {
    intakeLow.spin(DIR_FWD, 100, VEL_PCT);
    while (true){
        intakeHigh.spin(DIR_FWD, 100, VEL_PCT);
        if (colorSort.isNearObject() && colorSort.color() == vex::color::blue)
            intakeHigh.spinFor(-60, ROT_DEG, 100, VEL_PCT);
    wait(20, TIME_MSEC);
    }
}