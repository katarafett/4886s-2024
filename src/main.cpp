/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Aden                                             */
/*    Created:      Mon May 16 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/main.h"
#include "stddefs.h"
#include "vex_global.h"
#include "vex_units.h"

vex::competition Competition;

void testing(void) {
    drive_straight(48, 60, 48);
}

void rot_test(void) {
    inrtl.resetRotation();
    drive_turn(360, WHEEL_TO_WHEEL_DIST / 2.0, 48, 48);
    master.rumble(".");
    drive_r.spin(DIR_FWD, -12, VLT_VLT);
    drive_l.spin(DIR_FWD, 12, VLT_VLT);

    printf("\n\nstart\n");
    sands_of_time.reset();
    while (ROTATION * GYRO_CORRECTION < 360) {
        wait(1, vex::msec);
        printf("time: %.3f", sands_of_time.time(vex::msec));
    }

    C_SCREEN.clearScreen();
    C_SCREEN.print(" ");
    C_SCREEN.print(sands_of_time.time());

    drive_l.stop(vex::brakeType::brake);
    drive_r.stop(vex::brakeType::brake);
    wait(2, vex::sec);
    drive_turn(360, WHEEL_TO_WHEEL_DIST / 2.0, 48, 48);
}

// #define TESTING
#ifdef TESTING
const bool do_testing = true;
#else
const bool do_testing = false;
#endif

int main() {
    pre_auton();
    if (!do_testing) {
        Competition.autonomous(autonomous);
        Competition.drivercontrol(opcontrol);
    } else {
        // master.ButtonA.pressed(testing);
        // master.ButtonB.pressed(rot_test);
        // master.ButtonX.pressed(tune_gyro);
        master.ButtonY.pressed(tune_simple_pid);
    }

    while (true) {
        vex::task::sleep(20);
    }
}
