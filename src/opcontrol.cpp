#include "main.h"
#include "stddefs.h"
#include "vex_thread.h"

void opcontrol(void) {
	intake.stop(vex::brakeType::brake);
	bool shifted = false;

	bool do_neutral_line_up = false;

	const int LIFT_BUFFER = 110;

	int liftHeight = 1;
	bool liftOT = 1;
	intake_lift.set(0);

	while (lift.current(PCT_PCT) < 80) {
		lift.spin(DIR_REV);
	}
	wait(100, TIME_MSEC);
	lift.resetPosition();

	colorSort.setLightPower(100, PCT_PCT);
	colorSort.setLight(vex::ledState::on);

	lift.setStopping(vex::brakeType::hold);
	intakeHigh.setPosition(6, ROT_REV);

	Brain.Screen.drawImageFromFile("Graduation.png", 0, 0);
	while (1) {
		// Drive control
		drive.opdrive();


		// Shift button
		shifted = btn_left();

		if (colorSort.color() == vex::color::blue) {
			intakeHigh.resetPosition();
		}
		if (intakeHigh.position(ROT_REV) >= 1.5 && intakeHigh.position(ROT_REV) <= 1.7) {
			intakeHigh.spinFor(-0.5, ROT_REV, 100, VEL_PCT, false);
			wait(100, TIME_MSEC);
			intakeHigh.setPosition(6, ROT_REV);
		}
		// Unshifted
		if (!shifted) {
			//Lift


			if (BTN_L1.PRESSED) {
				liftHeight = liftHeight + 1;
			}
			if (BTN_L2.PRESSED) {
				liftHeight = 1;
			}
			// To reset the lift
			if (BTN_DOWN.PRESSED) {
				while (lift.current(PCT_PCT) < 80) {
					lift.spin(DIR_REV);
				}
				wait(100, TIME_MSEC);
				lift.resetPosition();
			}

			if (liftHeight == 1) {
				lift.spinToPosition(2 * 4, ROT_DEG, 100, VEL_PCT, false);
				lift.setStopping(vex::brakeType::coast);
			}

			else if (liftHeight == 2) {
				lift.spinToPosition(54 * 4, ROT_DEG, 100, VEL_PCT, false);
				lift.setStopping(vex::brakeType::hold);
			}

			else if (liftHeight == 3) {
				lift.setStopping(vex::brakeType::hold);
				lift.spinToPosition(182 * 4, ROT_DEG, 100, VEL_PCT, false);
			}

			else if (liftHeight == 4) {
				lift.spinToPosition(280 * 4, ROT_DEG, 100, VEL_PCT, false);
				lift.setStopping(vex::brakeType::hold);
			}
			// MOGO Mech
			if (BTN_Y.PRESSED) {
				mogo_clamp.set(!mogo_clamp.value());
			}

			// Smith Mech
			if (BTN_B.PRESSED)
				Smith_Mech.set(!Smith_Mech.value());


			// Intake lift
			if (BTN_X.PRESSED)
				intake_lift.set(!intake_lift.value());


			// PTO
			if (BTN_RIGHT.PRESSED) {
				lift.spinToPosition(125 * 5, ROT_DEG, 200, VEL_RPM);
				wait(150, TIME_MSEC);
				lift.spinToPosition(2 * 5, ROT_DEG, 200, VEL_RPM, false);
			}

			if (do_neutral_line_up) {
				// neutral_line_up();
			}
			wait(20, vex::msec);
		}

		// Intake
		intake.spin(DIR_FWD, (btn_r1() - btn_r2()) * BTN_TO_PCT, VEL_PCT);
	}
}
