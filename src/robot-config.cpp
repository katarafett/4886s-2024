#include "../include/main.h"

vex::brain Brain;
vex::controller master;

// Drive
vex::motor drive_rf (PORT1, DRIVE_INSERT, false);
vex::motor drive_rm (PORT2, DRIVE_INSERT, false);
vex::motor drive_rb (PORT3, DRIVE_INSERT, false);
vex::motor drive_lf (PORT4, DRIVE_INSERT, true);
vex::motor drive_lm (PORT5, DRIVE_INSERT, true);
vex::motor drive_lb (PORT6, DRIVE_INSERT, true);

// Flywheel
vex::motor flywheel_hi (PORT7, FLYWHEEL_INSERT, false);
vex::motor flywheel_lo (PORT8, FLYWHEEL_INSERT, true);

// PTO
vex::digital_out pto_flywheel (PORTA);
vex::digital_out pto_intake (PORTB);

// Sensors
vex::inertial inrtl (PORT20);
vex::rotation rot_flywheel_hi (PORT19, false);
vex::rotation rot_flywheel_lo (PORT18, true);
vex::timer sands_of_time;

vex::motor_group drive_r (drive_rf, drive_rm, drive_rb);
vex::motor_group drive_l (drive_lf, drive_lm, drive_lb);
vex::motor_group flywheel (flywheel_hi, flywheel_lo);
