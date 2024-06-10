#include "../include/main.h"

void alt() {
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
            printf("here\n ");
        }
    }
    else {
        drive_full.stop();
    }

}