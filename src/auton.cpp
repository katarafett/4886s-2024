#include "../include/main.h"

void autonomous(void) {
    switch (auton_mode) {
        case AWP:
            drive_turn(-90, 24, 24, 24, false);
            break;
        case HALF_AWP_NEAR:
            break;
        case HALF_AWP_FAR:
              break;
        case SKILLS:
              break;
    }
}
