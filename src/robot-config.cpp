#include "../include/main.h"
#include "stddefs.h"
#include "vex_global.h"
#include "vex_triport.h"

vex::brain Brain;
vex::controller master;

// Drive
vex::motor drive_rf = vex::motor(PORT1, DRIVE_INSERT, false);
vex::motor drive_rb = vex::motor(PORT2, DRIVE_INSERT, false);
vex::motor drive_rt = vex::motor(PORT3, DRIVE_INSERT, true);
vex::motor drive_lf = vex::motor(PORT4, DRIVE_INSERT, true);
vex::motor drive_lm = vex::motor(PORT5, DRIVE_INSERT, true);
vex::motor drive_lb = vex::motor(PORT6, DRIVE_INSERT, false);

// Subsystem 3
vex::motor cata = vex::motor(PORT8, TRQ_INSERT, false);
vex::motor intake = vex::motor(PORT7, TRB_INSERT, false);

// Wings
vex::digital_out wing_fr = vex::digital_out(PORTC);
vex::digital_out wing_fl = vex::digital_out(PORTD);
vex::digital_out wing_br = vex::digital_out(PORTA);
vex::digital_out wing_bl = vex::digital_out(PORTB);

vex::digital_out hang = vex::digital_out(PORTE);

// Sensors
vex::inertial inrtl = vex::inertial(PORT20);
vex::timer sands_of_time;

vex::motor_group drive_r = vex::motor_group(drive_rf, drive_rb, drive_rt);
vex::motor_group drive_l = vex::motor_group(drive_lf, drive_lb, drive_lt);
vex::motor_group drive_full = vex::motor_group(drive_rf, drive_rb, drive_rt, drive_lf, drive_lb, drive_lt);

// Auton switcher
vex::digital_in selector = vex::digital_in(PORTH);
