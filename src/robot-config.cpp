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

// Cata
vex::motor cata (PORT7, TRQ_INSERT, true);

// Intake
vex::motor intake_l (PORT15, INTAKE_INSERT, false);
vex::motor intake_r (PORT16, INTAKE_INSERT, true);

// Wings
vex::digital_out wings (PORTA);
// Slapper
vex::digital_out smith (PORTB);
// Elevation
vex::digital_out balance (PORTC);

// Sensors
vex::inertial inrtl (PORT20);
vex::timer sands_of_time;
vex::rotation rotn (PORT10);

vex::motor_group drive_r (drive_rf, drive_rm, drive_rb);
vex::motor_group drive_l (drive_lf, drive_lm, drive_lb);
vex::motor_group intake (intake_l, intake_r);

PID drive_pid (0.1, 0, 0);
