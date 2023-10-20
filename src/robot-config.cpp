#include "../include/main.h"

vex::brain Brain;
vex::controller master;

// Drive
vex::motor drive_rf (PORT3, DRIVE_INSERT, true);
vex::motor drive_rm (PORT7, DRIVE_INSERT, true);
vex::motor drive_rb (PORT3, DRIVE_INSERT, true);
vex::motor drive_lf (PORT4, DRIVE_INSERT, false);
vex::motor drive_lm (PORT5, DRIVE_INSERT, false);
vex::motor drive_lb (PORT6, DRIVE_INSERT, false);

// Intake
vex::motor intake_l (PORT8, INTAKE_INSERT, true);
vex::motor intake_r (PORT9, INTAKE_INSERT, false);

// Cata
vex::motor cata (PORT7, TRQ_INSERT, false);

// Fly
vex::motor flywheel_t (PORT15, TRB_INSERT, false);
vex::motor flywheel_b (PORT16, TRB_INSERT, true);

// Wings
vex::digital_out wing_r (PORTA);
vex::digital_out wing_l (PORTB);

// Sensors
vex::inertial inrtl (PORT20);
vex::timer sands_of_time;
vex::rotation rtn (PORT10);

vex::motor_group drive_r (drive_rf, drive_rm, drive_rb);
vex::motor_group drive_l (drive_lf, drive_lm, drive_lb);
vex::motor_group intake (intake_l, intake_r);
vex::motor_group flywheel (flywheel_t, flywheel_b);
