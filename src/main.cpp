/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Aden                                             */
/*    Created:      Mon May 16 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "main.h"

vex::competition Competition;

int main() {
    Competition.autonomous(autonomous);
    Competition.drivercontrol(opcontrol);
    pre_auton();

    while (true) {
        wait(20, vex::msec);
    }
}
