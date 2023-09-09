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

int main() {
    //pre_auton();
    Competition.autonomous(autonomous);
    Competition.drivercontrol(opcontrol);

    while (true) {
        vex::task::sleep(20);
    }
}
