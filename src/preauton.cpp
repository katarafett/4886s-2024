#include "main.h"

void pre_auton(void) {
    // Calibrate inertial
    imu.calibrate(2);

    intake_lift.set(1);
    int *sides;
    const char *autons[8] = {"FullAWP", "RedRush", "RedQuad", "BlueQuad", "BlueRush", "SKILLS", "ElimsBlue", "ElimsRed"};

    // Create GUI - none of this is important, just for looks
    Brain.Screen.clearScreen();
    Brain.Screen.drawRectangle(B_SCRN_X_MID / 8, 0, B_SCRN_X / 4, B_SCRN_Y_MID, vex::green);
    Brain.Screen.drawRectangle(B_SCRN_X_MID / 8 + B_SCRN_X / 2, 0, B_SCRN_X / 4, B_SCRN_Y_MID, vex::red);

    Brain.Screen.setFillColor(vex::red);
    Brain.Screen.setPenColor(vex::black);
    Brain.Screen.printAt(B_SCRN_X / 12 + B_SCRN_X / 2, B_SCRN_Y / 4, "LOCK");

    Brain.Screen.setFillColor(vex::green);
    Brain.Screen.printAt(B_SCRN_X / 12, B_SCRN_Y / 4, "CYCLE");

    Brain.Screen.setFillColor(vex::black);
    Brain.Screen.setPenColor(vex::white);
    Brain.Screen.setCursor(B_SCRN_Y * 3 / 2, 1);

    // Print currently selected mode
    Brain.Screen.print("%s", autons[auton_mode]);

    while (!(BTN_A.pressing())) {
        sides = side_pressed();

        // Update auton type
        if (sides[X] == LEFT) {
            auton_mode++;
            if (auton_mode > ELIMS_RED)
                auton_mode = FULL_AWP;
            Brain.Screen.setCursor(B_SCRN_Y * 3 / 2, 1);
            Brain.Screen.clearLine();
            Brain.Screen.print("%s", autons[auton_mode]);
        }

        // Lock auton
        if (sides[X] == RIGHT && sides[Y] == UP) {
            Brain.Screen.print(" - LOCKED");
            break;
        }

        if (!imu.isCalibrating())
            Brain.Screen.printAt(0, B_SCRN_Y - 20, "imu: %.3f", imu_rotation());

        wait(20, vex::msec);
    }
    printf("locked");
    Brain.Screen.clearScreen();
    Brain.Screen.drawImageFromFile("GradNew.jpeg", 57.5, 0);

    /*
    Brain.Screen.setFillColor("#0000aa");
    Brain.Screen.clearScreen();
    Brain.Screen.drawRectangle(0, B_SCRN_Y_MID, B_SCRN_X_MID, B_SCRN_Y_MID);
    Brain.Screen.printAt(B_SCRN_X_MID - 200, (B_SCRN_Y * 3 / 4) - (CHAR_HI / 2), "debug()");
	*/
}
