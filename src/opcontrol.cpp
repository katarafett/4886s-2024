#include "../include/main.h"
#include "stddefs.h"

// Driver macros
void opcontrol(void) {
    drive_l.stop(vex::brakeType::coast);
    drive_r.stop(vex::brakeType::coast);
    bool shifted = false;

    while (1) {
        // Drive control
        opdrive(TSA, 1.0, SENSITIVITY);

        // Shift button
        shifted = btn_l2();

        // Unshifted
        if (!shifted) {
            // Intake
            intake.spin(DIR_FWD, (btn_r1() - btn_r2()) * BTN_TO_PCT, VEL_PCT);
            if (BTN_L1.PRESSED)
                intake_toggle.set(!intake_toggle.value());
        }
        // Shifted
        else {
            // Toggle wings
            if (BTN_L1.PRESSED)
                wing_fl.set(!wing_fl.value());
            if (BTN_R1.PRESSED)
                wing_fr.set(!wing_fr.value());
        }
        // Both

        // Activate PTO
        if (BTN_RIGHT.PRESSED)
            hang.set(!hang.value());

        wait(20, vex::msec);
    }
}

void opdrive(int control_mode, float drive_mod, float turn_mod) {
    switch (control_mode) {
        case TNK:
            drive_r.spin(DIR_FWD, RIGHT_STICK_Y, VEL_PCT);
            drive_l.spin(DIR_FWD, LEFT_STICK_Y, VEL_PCT);
            break;
        case OSA:
            drive_r.spin(DIR_FWD, (LEFT_STICK_Y - LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            drive_l.spin(DIR_FWD, (LEFT_STICK_Y + LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            break;
        case TSA:
            float lspeed = LEFT_STICK_Y;
            float rspeed = RIGHT_STICK_X * turn_mod;
            drive_r.spin(DIR_FWD, (lspeed - rspeed) * drive_mod, VEL_PCT);
            drive_l.spin(DIR_FWD, (lspeed + rspeed) * drive_mod, VEL_PCT);
            break;
    }
}
