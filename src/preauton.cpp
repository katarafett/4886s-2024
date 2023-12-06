#include "../include/main.h"

void pre_auton(void) {
    // Calibrate inertial
    inrtl.calibrate();
    while (inrtl.isCalibrating()) wait(20, vex::msec);
    master.rumble(".");

    // Create GUI
    int *sides;
    const char *autons[4] = {"AWP", "HALF_AWP_NEAR", "HALF_AWP_FAR", "SKILLS"};

    B_SCRN.clearScreen();
    B_SCRN.drawRectangle(B_SCRN_X_MID / 8, 0, B_SCRN_X / 4, B_SCRN_Y_MID, vex::green);
    B_SCRN.drawRectangle(B_SCRN_X_MID / 8 + B_SCRN_X / 2, 0, B_SCRN_X / 4, B_SCRN_Y_MID, vex::red);

    B_SCRN.setFillColor(vex::red);
    B_SCRN.setPenColor(vex::black);
    B_SCRN.printAt(B_SCRN_X / 12 + B_SCRN_X / 2, B_SCRN_Y / 4, "LOCK");

    B_SCRN.setFillColor(vex::green);
    B_SCRN.printAt(B_SCRN_X / 12, B_SCRN_Y / 4, "CYCLE");

    B_SCRN.setFillColor(vex::black);
    B_SCRN.setPenColor(vex::white);
    B_SCRN.setCursor(B_SCRN_Y * 3 / 2, 1);
    B_SCRN.print("%s", autons[auton_mode]);


    while (!(BTN_A.pressing())) {
        sides = side_pressed();

        // Update auton type
        if (sides[X] == LEFT && sides[Y] == UP) {
            auton_mode++;
            // Not good; if auton count changes, memory errors
            if (auton_mode > 3) auton_mode = 0;
            B_SCRN.clearLine();
            B_SCRN.print("%s", autons[auton_mode]);
        }

        // Lock auton
        if (sides[X] == RIGHT && sides[Y] == UP) {
            B_SCRN.print(" - LOCKED");
            break;
        }

        wait(20, vex::msec);
    }

    B_SCRN.setFillColor("#0000aa");
    B_SCRN.clearScreen();
    B_SCRN.drawRectangle(0, B_SCRN_Y_MID, B_SCRN_X_MID, B_SCRN_Y_MID);
    B_SCRN.printAt(B_SCRN_X_MID - 200, (B_SCRN_Y * 3 / 4) - (CHAR_HI / 2), "debug()");
}
