#include "../include/main.h"

vex::brain Brain;
vex::controller master;

// Drive
vex::motor drive_rf (PORT1, DRIVE_INSERT, true);
vex::motor drive_rm (PORT2, DRIVE_INSERT, true);
vex::motor drive_rb (PORT3, DRIVE_INSERT, true);
vex::motor drive_lf (PORT4, DRIVE_INSERT, false);
vex::motor drive_lm (PORT5, DRIVE_INSERT, false);
vex::motor drive_lb (PORT6, DRIVE_INSERT, false);

// Intake
vex::motor intake_l (PORT9, INTAKE_INSERT, false);
vex::motor intake_r (PORT10, INTAKE_INSERT, true);

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
