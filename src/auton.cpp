#include "../include/main.h"

void autonomous(void) {
    switch (auton_mode) {
        case AWP:
            // Tune pid
            while (!BTN_B.pressing()) {
                drive_pid.tune_kP(0.1);
                wait(20, vex::msec);
            }
            break;
        case HALF_AWP_NEAR:
            break;
        case HALF_AWP_FAR:
              break;
        case SKILLS:
              break;
    }
}
