#include "../include/main.h"

void pre_auton(void) {
    // Calibrate inertial
    imu.calibrate();

    int *sides;
    const char *autons[6] = {"TEST_AUTO", "RedRight", "RedLeft", "BlueRight", "BlueLeft", "SKILLS"};

    // Create GUI - none of this is important, just for looks
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

    // Print currently selected mode
    B_SCRN.print("%s", autons[auton_mode]);

    while (!(BTN_A.pressing())) {
        sides = side_pressed();

        // Update auton type
        if (auto_selector.value() == 0 || sides[X] == LEFT) {
            auton_mode++;
            if (auton_mode > SKILLS)
                auton_mode = TEST_AUTO;
            B_SCRN.setCursor(B_SCRN_Y * 3 / 2, 1);
            B_SCRN.clearLine();
            B_SCRN.print("%s", autons[auton_mode]);

            // Wait for sensor to depress
            while (auto_selector.value() == 0) {
                int count = 0;
                wait(1, vex::msec);
                if (++count > 200)
                    break;
            }
        }

        // Lock auton
        if (sides[X] == RIGHT && sides[Y] == UP) {
            B_SCRN.print(" - LOCKED");
            break;
        }

        if (!imu.isCalibrating())
            B_SCRN.printAt(0, B_SCRN_Y - 20, "imu: %.3f", imu_rotation());

        wait(20, vex::msec);
    }
    printf("locked");

    B_SCRN.setFillColor("#0000aa");
    B_SCRN.clearScreen();
    B_SCRN.drawRectangle(0, B_SCRN_Y_MID, B_SCRN_X_MID, B_SCRN_Y_MID);
    B_SCRN.printAt(B_SCRN_X_MID - 200, (B_SCRN_Y * 3 / 4) - (CHAR_HI / 2), "debug()");
}
