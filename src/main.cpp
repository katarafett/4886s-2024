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

// #define TEST_FUNCS
#ifdef TEST_FUNCS
const bool run_main = false;
#else
const bool run_main = true;
#endif

void alt() {

    while (true) {
        vision1.takeSnapshot(red_ring);

        if (vision1.objectCount > 0) {
            if (vision1.largestObject.centerX < 145) {
                drive_l.spin(DIR_FWD, -15 - (157 - vision1.largestObject.centerX) / 10.0, VEL_PCT);
                drive_r.spin(DIR_FWD, -15 + (157 - vision1.largestObject.centerX) / 10.0, VEL_PCT);
            }
            else if (vision1.largestObject.centerX > 169) {
                drive_l.spin(DIR_FWD, -15 - (157 - vision1.largestObject.centerX) / 10.0, VEL_PCT);
                drive_r.spin(DIR_FWD, -15 + (157 - vision1.largestObject.centerX) / 10.0, VEL_PCT);
            }
            else {
                drive_full.spin(DIR_REV, 35, VEL_PCT);
            }
        }
        else {
            drive_full.stop();
        }
        wait(20, vex::msec);
    }
}

int main() {
    if (run_main) {
        Competition.autonomous(autonomous);
        Competition.drivercontrol(alt);
    }
    else {
        master.ButtonY.pressed(tune_fast_pid);
        master.ButtonRight.pressed(autonomous);
    }

    pre_auton();

    while (true) {
        vex::task::sleep(20);
    }
}
