/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Aden                                             */
/*    Created:      Mon May 16 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/main.h"

vex::competition Competition;

void rotprog(void);

int main() {
    // pre_auton();
    Competition.autonomous(autonomous);
    Competition.drivercontrol(opcontrol);

    while (true) {
        vex::task::sleep(20);
    }
}

void rotprog() {
    inrtl.calibrate();
    while (inrtl.isCalibrating())
        wait(20, vex::msec);
    sands_of_time.reset();
    while (inrtl.rotation() * GYRO_CORRECTION < 360) {
        drive_r.spin(DIR_FWD, -100, VEL_PCT);
        drive_l.spin(DIR_FWD, 100, VEL_PCT);
    }
    float time = sands_of_time.time();
    drive_r.stop();
    drive_l.stop();
    B_SCRN.clearScreen();
    B_SCRN.setCursor(3, 3);
    B_SCRN.print("time: %f", time);
    printf("%f\n", time);
}
