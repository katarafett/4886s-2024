#include "../include/main.h"


void red_chase() {
    vision1.takeSnapshot(red_ring);

    // Determines if there is a red ring to chase
    if (vision1.objectCount > 0) {
        // If the closeset ring is not in the center:
        if (vision1.largestObject.centerX < 145 || vision1.largestObject.centerX > 169) {
            // Drive turn perportionaly based on the distince to the ring
            drive_l.spin(DIR_FWD, -15 - (157 - vision1.largestObject.centerX) / 10.0, VEL_PCT);
            drive_r.spin(DIR_FWD, -15 + (157 - vision1.largestObject.centerX) / 10.0, VEL_PCT);
        }
        // If the ring is streight back from the robot:
        else {
            drive_full.spin(DIR_REV, 35, VEL_PCT);
        }
    }
    // If no ring is detected, do nothing
    else {
        drive_full.stop();
    }
}

void blue_run() {
    vision1.takeSnapshot(red_ring);

    // Determines if there is a red ring to chase
    if (vision1.objectCount > 0) {
        // If the closeset ring is on the left:
        if (vision1.largestObject.centerX < 145) {
            // Drive turn left perportionaly to the distince to the ring
            drive_l.spin(DIR_FWD, -(157 - vision1.largestObject.centerX) / 10.0, VEL_PCT);
            drive_r.spin(DIR_FWD, (157 - vision1.largestObject.centerX) / 10.0, VEL_PCT);
        }
        // If the closeset ring is on the right:
        else if (vision1.largestObject.centerX > 169) {
            drive_l.spin(DIR_FWD, -(157 - vision1.largestObject.centerX) / 10.0, VEL_PCT);
            drive_r.spin(DIR_FWD, (157 - vision1.largestObject.centerX) / 10.0, VEL_PCT);
        }
        // If the ring is streight back from the robot:
        else {
            drive_full.stop();
        }
    }
    // If no ring is detected, do nothing
    else {
        drive_full.stop();
    }
}