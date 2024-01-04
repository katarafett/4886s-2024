#include "../include/main.h"

vex::brain Brain;
vex::controller master;

// Drive
// #define RPM_450
#ifdef RPM_450
vex::motor drive_rf = vex::motor(PORT1, DRIVE_INSERT, false);
vex::motor drive_rm = vex::motor(PORT2, DRIVE_INSERT, false);
vex::motor drive_rb = vex::motor(PORT3, DRIVE_INSERT, false);
vex::motor drive_lf = vex::motor(PORT4, DRIVE_INSERT, true);
vex::motor drive_lm = vex::motor(PORT5, DRIVE_INSERT, true);
vex::motor drive_lb = vex::motor(PORT6, DRIVE_INSERT, true);
#else
vex::motor drive_rf = vex::motor(PORT1, DRIVE_INSERT, true);
vex::motor drive_rm = vex::motor(PORT2, DRIVE_INSERT, true);
vex::motor drive_rb = vex::motor(PORT3, DRIVE_INSERT, true);
vex::motor drive_lf = vex::motor(PORT4, DRIVE_INSERT, false);
vex::motor drive_lm = vex::motor(PORT5, DRIVE_INSERT, false);
vex::motor drive_lb = vex::motor(PORT6, DRIVE_INSERT, false);
#endif      // STACKED

// Cata
vex::motor puncher = vex::motor(PORT7, TRQ_INSERT, false);

// Intake
vex::motor intake = vex::motor(PORT10, INTAKE_INSERT, false);

// Wings
vex::digital_out wings_r = vex::digital_out(PORTA);
vex::digital_out wings_l = vex::digital_out(PORTB);

// Slapper
vex::digital_out smith = vex::digital_out(PORTC);

// Sensors
vex::inertial inrtl = vex::inertial(PORT20);
vex::timer sands_of_time;

vex::motor_group drive_r = vex::motor_group(drive_rf, drive_rm, drive_rb);
vex::motor_group drive_l = vex::motor_group(drive_lf, drive_lm, drive_lb);
vex::motor_group drive_full = vex::motor_group(drive_rf, drive_rm, drive_rb, drive_lf, drive_lb, drive_lm, drive_lb);
