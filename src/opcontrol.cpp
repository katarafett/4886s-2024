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
    bool autofire_enabled = false;
    bool wings_out_l = false;
    bool wings_out_r = false;
    bool hang_out = false;
    bool shifted = false;
    float drive_mod = 1.0;

    while (1) {
        shifted = BTN_L2.pressing();
        // Slow down drive if hang is active
        if (hang.value())
            drive_mod = 0.5;
        else drive_mod = 1.0;

        // Drive control
        opdrive(TSA_STD, drive_mod, SENSITIVITY);

        // Intake
        intake.spin(DIR_FWD, (R1_UNSHIFTED - R2_UNSHIFTED) * BTN__PCT, VEL_PCT);

       // Puncher
        cata.spin(DIR_FWD, L1_UNSHIFTED * BTN__PCT, VEL_PCT);

        // Toggle wings
        if (L1_SHIFTED)
            wing_fl.set(!wing_fl.value());
        if (R1_SHIFTED)
            wing_fr.set(!wing_fr.value());
        if (R2_SHIFTED) {
            wing_bl.set(!wing_bl.value());
            wing_br.set(!wing_br.value());
        }

        // Toggle hang
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
            rspeed = ry * ry / 100 * ((ry > 0) - (ry < 0));
            lspeed = ly * ly / 100 * ((ly > 0) - (ly < 0));
            // drive_r.spin(DIR_FWD, rspeed, VEL_PCT);
            // drive_l.spin(DIR_FWD, lspeed, VEL_PCT);
            drive_r.spin(DIR_FWD, RIGHT_STICK_Y, VEL_PCT);
            drive_l.spin(DIR_FWD, LEFT_STICK_Y, VEL_PCT);
            break;
        case OSA_STD:
            drive_r.spin(DIR_FWD, (LEFT_STICK_Y - LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            drive_l.spin(DIR_FWD, (LEFT_STICK_Y + LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            break;
        case TSA_STD:
            // lspeed = (ly - rx) * (ly - rx) / 100 * (((ly - rx) > 0) - ((ly - rx) < 0));
            // rspeed = (ly + rx) * (ly + rx) / 100 * (((ly + rx) > 0) - ((ly + rx) < 0));
            lspeed = (ly * ly * ly / 16129.0);
            rspeed = (rx * rx * rx / 16129.0) * turn_mod;
            drive_r.spin(DIR_FWD, (lspeed - rspeed) * drive_mod, VEL_PCT);
            drive_l.spin(DIR_FWD, (lspeed + rspeed) * drive_mod, VEL_PCT);
            break;
        case TNK_REV:
            drive_l.spin(DIR_REV, RIGHT_STICK_Y * drive_mod, VEL_PCT);
            drive_r.spin(DIR_REV, LEFT_STICK_Y * drive_mod, VEL_PCT);
            break;
        case OSA_REV:
            drive_l.spin(DIR_REV, (LEFT_STICK_Y - LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            drive_r.spin(DIR_REV, (LEFT_STICK_Y + LEFT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            break;
        case TSA_REV:
            drive_r.spin(DIR_REV, (LEFT_STICK_Y + RIGHT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            drive_l.spin(DIR_REV, (LEFT_STICK_Y - RIGHT_STICK_X * turn_mod) * drive_mod, VEL_PCT);
            break;
    }
}
