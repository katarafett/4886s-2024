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

#define TESTING
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
    }
    else {
        master.ButtonY.pressed(tune_fast_pid);
        master.ButtonRight.pressed(autonomous);
    }

    while (true) {
        vex::task::sleep(20);
    }
}
