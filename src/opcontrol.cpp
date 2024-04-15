#include "../include/main.h"
#include "stddefs.h"
#include "vex_thread.h"

// Driver macros
void opcontrol(void) {
    drive_l.stop(vex::brakeType::coast);
    drive_r.stop(vex::brakeType::coast);
    bool shifted = false;

    float spd_mod = 1.0;
    float sens_mod = 1.0;

    while (1) {
        // Drive control
        opdrive(TSA, spd_mod, SENSITIVITY * sens_mod);

        // Shift button
        shifted = btn_l2();

        // Unshifted
        if (!shifted) {
            // Intake
            intake.spin(DIR_FWD, (btn_r1() - btn_r2()) * BTN_TO_PCT, VEL_PCT);
            // Toggle intake
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
            if (BTN_R2.PRESSED) {
                wing_fl.set(0);
                wing_fr.set(0);
            }
        }
        // Both

        // Release hang
        if (BTN_Y.PRESSED)
            hang_release.set(!hang_release.value());
        // Activate PTO
        if (BTN_RIGHT.PRESSED) {
            if (!pto.value()) {
                hang_release.set(0);
                intake_toggle.set(1);
            }
            pto.set(!pto.value());
        }

        if (hang_release.value() && !pto.value()) {
            spd_mod = 0.5;
            sens_mod = 0.6;
        }
        else {
            spd_mod = 1.0;
            sens_mod = 1.0;
        }
        
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
