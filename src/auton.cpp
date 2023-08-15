#include "../include/main.h"

void autonomous(void) {
    sands_of_time.reset();
    inrtl.calibrate();
    while (inrtl.isCalibrating()) {
        vex::wait(20, vex::msec);
    }
    inrtl.resetRotation();

    while (inrtl.rotation() < abs(36000)) {
        drive_r.spin(DIR_FWD, -100, VEL_PCT);
        drive_l.spin(DIR_FWD, 100, VEL_PCT);
        vex::wait(20, vex::msec);
    }

    B_SCRN.print("time: %d", sands_of_time.time(vex::msec));
}
