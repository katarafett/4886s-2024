#include "../include/main.h"
#include "stddefs.h"

// Driver macros
#define L1_SHIFTED (BTN_L1.PRESSED && shifted)
#define R1_SHIFTED (BTN_R1.PRESSED && shifted)
#define R2_SHIFTED (BTN_R2.PRESSED && shifted)

#define L1_UNSHIFTED (BTN_L1.pressing() && !shifted)
#define R1_UNSHIFTED (BTN_R1.pressing() && !shifted)
#define R2_UNSHIFTED (BTN_R2.pressing() && !shifted)

void opcontrol(void) {
    drive_l.stop(vex::brakeType::coast);
    drive_r.stop(vex::brakeType::coast);
    if (auton_mode != SKILLS_DRIVER) {
        wing_fr.set(0);
        wing_fl.set(0);
    }
    bool shifted = false;

    while (1) {
        shifted = BTN_L2.pressing();

        // Drive control
        opdrive(TNK_STD, 1.0, SENSITIVITY);

        // Intake
        intake.spin(DIR_FWD, (R1_UNSHIFTED - R2_UNSHIFTED) * BTN__PCT, VEL_PCT);

       // Puncher

        // Toggle wings
        if (L1_SHIFTED)
            wing_fl.set(!wing_fl.value());
        if (R1_SHIFTED)
            wing_fr.set(!wing_fr.value());

        // Activate pto
        if (BTN_Y.PRESSED)
            hang.set(!hang.value());

        wait(20, vex::msec);
    }
}

void opdrive(int control_mode, float drive_mod, float turn_mod) {
    drive_mod *= STICK__PCT;     // Adjust for percentage units
    double ry = RIGHT_STICK_Y, ly = LEFT_STICK_Y, rx = RIGHT_STICK_X, lx = LEFT_STICK_X;
    float rspeed, lspeed;
    switch (control_mode) {
        case TNK_STD:
            drive_r.spin(DIR_FWD, RIGHT_STICK_Y, VEL_PCT);
            drive_l.spin(DIR_FWD, LEFT_STICK_Y, VEL_PCT);
            break;
        case OSA_STD:
            drive_r.spin(DIR_FWD, (LEFT_STICK_Y - LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            drive_l.spin(DIR_FWD, (LEFT_STICK_Y + LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            break;
        case TSA_STD:
            lspeed = LEFT_STICK_Y;
            rspeed = RIGHT_STICK_X * turn_mod;
            drive_r.spin(DIR_FWD, (lspeed - rspeed) * drive_mod, VEL_PCT);
            drive_l.spin(DIR_FWD, (lspeed + rspeed) * drive_mod, VEL_PCT);
            break;
    }
}
