#include "../include/main.h"
#include "stddefs.h"
#include "vex_triport.h"

vex::brain Brain;
vex::controller master;

// Drive
vex::motor drive_rf = vex::motor(PORT1, DRIVE_INSERT, false);
vex::motor drive_rm = vex::motor(PORT2, DRIVE_INSERT, false);
vex::motor drive_rb = vex::motor(PORT3, DRIVE_INSERT, true);
vex::motor drive_lf = vex::motor(PORT4, DRIVE_INSERT, true);
vex::motor drive_lm = vex::motor(PORT5, DRIVE_INSERT, true);
vex::motor drive_lb = vex::motor(PORT6, DRIVE_INSERT, false);

// LRS
vex::motor sys3_r = vex::motor(PORT7, SPD_INSERT, true);
vex::motor sys3_l = vex::motor(PORT8, SPD_INSERT, false);

// Intake
vex::motor intake = vex::motor(PORT10, INTAKE_INSERT, false);

// Wings
vex::digital_out wings = vex::digital_out(PORTA);

// Sensors
vex::inertial inrtl = vex::inertial(PORT20);
vex::timer sands_of_time;

vex::motor_group drive_r = vex::motor_group(drive_rf, drive_rm, drive_rb);
vex::motor_group drive_l = vex::motor_group(drive_lf, drive_lm, drive_lb);
vex::motor_group drive_full = vex::motor_group(drive_rf, drive_rm, drive_rb, drive_lf, drive_lb, drive_lm, drive_lb);

vex::motor_group sys3 = vex::motor_group(sys3_r, sys3_l);

// Auton switcher
vex::digital_in selector = vex::digital_in(PORTH);
