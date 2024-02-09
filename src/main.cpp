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
    // inrtl.resetRotation();
    // drive_r.spin(DIR_FWD, -12, VLT_VLT);
    // drive_l.spin(DIR_FWD, 12, VLT_VLT);

    // printf("\n\nstart\n");
    // sands_of_time.reset();
    // while (ROTATION * GYRO_CORRECTION < 360) {
    //     wait(1, vex::msec);
    //     printf("time: %.3f", sands_of_time.time(vex::msec));
    // }

    // C_SCREEN.clearScreen();
    // C_SCREEN.print(" ");
    // C_SCREEN.print(sands_of_time.time());

    // drive_l.stop(vex::brakeType::brake);
    // drive_r.stop(vex::brakeType::brake);
    drive_turn(360, WHEEL_TO_WHEEL_DIST / 2.0, 48, 48);
}

int main() {
    pre_auton();
    Competition.autonomous(autonomous);
    Competition.drivercontrol(opcontrol);
    // master.ButtonA.pressed(testing);
    // master.ButtonB.pressed(rot_test);
    // master.ButtonX.pressed(tune_gyro);
    // master.ButtonY.pressed(tune_drive_pid);

    while (true) {
        vex::task::sleep(20);
    }
}
