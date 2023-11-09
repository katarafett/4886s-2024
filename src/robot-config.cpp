#include "../include/main.h"

vex::brain Brain;
vex::controller master;

// Drive
vex::motor drive_rf = vex::motor(PORT1, DRIVE_INSERT, true);
vex::motor drive_rm = vex::motor(PORT2, DRIVE_INSERT, true);
vex::motor drive_rb = vex::motor(PORT3, DRIVE_INSERT, true);
vex::motor drive_lf = vex::motor(PORT4, DRIVE_INSERT, false);
vex::motor drive_lm = vex::motor(PORT5, DRIVE_INSERT, false);
vex::motor drive_lb = vex::motor(PORT6, DRIVE_INSERT, false);

// Cata
vex::motor cata = vex::motor(PORT7, TRQ_INSERT, true);

// Intake
vex::motor intake_l = vex::motor(PORT15, INTAKE_INSERT, false);
vex::motor intake_r = vex::motor(PORT16, INTAKE_INSERT, true);

// Wings
vex::digital_out wings = vex::digital_out(PORTA);
// Slapper
vex::digital_out smith = vex::digital_out(PORTB);
// Elevation
vex::digital_out balance = vex::digital_out(PORTC);

// Sensors
vex::inertial inrtl = vex::inertial(PORT20);
vex::timer sands_of_time;
vex::rotation rotn = vex::rotation(PORT10);

vex::motor_group drive_r = vex::motor_group(drive_rf, drive_rm, drive_rb);
vex::motor_group drive_l = vex::motor_group(drive_lf, drive_lm, drive_lb);
vex::motor_group intake = vex::motor_group(intake_l, intake_r);
