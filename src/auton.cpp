#include "../include/main.h"

void autonomous(void) {
    // Initialization and calibration
    // inrtl.calibrate();
    // while (inrtl.isCalibrating()) {
    //     wait(20, vex::msec);
    // }
    // inrtl.resetRotation();
    sands_of_time.reset();

    // Spin 100 circles
    // while (inrtl.rotation() < 36000 && inrtl.rotation() > -36000) {
    //     drive_r.spin(DIR_FWD, -100, VEL_PCT);
    //     drive_l.spin(DIR_FWD, 100, VEL_PCT);
    //     wait(20, vex::msec);
    // }
    
    drive_r.spin(DIR_FWD, 12, VLT_VLT);
    drive_l.spin(DIR_FWD, 12, VLT_VLT);

    wait(20000, vex::msec);

    // Stop spinning
    drive_r.stop();
    drive_l.stop();

    B_SCRN.print("time: %d", sands_of_time.time(vex::msec));
}
