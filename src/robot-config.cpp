#include "../include/main.h"
#include "stddefs.h"
#include "v5_apitypes.h"
#include "vex_global.h"
#include "vex_triport.h"

#define DRIVE_INSERT vex::gearSetting::ratio6_1
#define INTAKE_INSERT vex::gearSetting::ratio6_1

vex::brain Brain;
vex::controller master;

// #define WEE_LITTLE_THING

#ifdef WEE_LITTLE_THING
// Drive
vex::motor drive_r1 = vex::motor(PORT18, DRIVE_INSERT, true);
vex::motor drive_r2 = vex::motor(PORT17, DRIVE_INSERT, true);
vex::motor drive_r3 = vex::motor(PORT16, DRIVE_INSERT, true);
// vex::motor drive_r4 = vex::motor(PORT4, DRIVE_INSERT, true);

vex::motor drive_l1 = vex::motor(PORT3, DRIVE_INSERT, false);
vex::motor drive_l2 = vex::motor(PORT6, DRIVE_INSERT, false);
vex::motor drive_l3 = vex::motor(PORT4, DRIVE_INSERT, false);
// vex::motor drive_l4 = vex::motor(PORT8, DRIVE_INSERT, false);

// Subsystem 3
vex::motor intake = vex::motor(PORT7, INTAKE_INSERT, false);
#else
vex::motor drive_r1 = vex::motor(PORT1, DRIVE_INSERT, false);
vex::motor drive_r2 = vex::motor(PORT2, DRIVE_INSERT, false);
vex::motor drive_r3 = vex::motor(PORT3, DRIVE_INSERT, false);
// vex::motor drive_r4 = vex::motor(PORT4, DRIVE_INSERT, true);

vex::motor drive_l1 = vex::motor(PORT4, DRIVE_INSERT, true);
vex::motor drive_l2 = vex::motor(PORT5, DRIVE_INSERT, true);
vex::motor drive_l3 = vex::motor(PORT6, DRIVE_INSERT, true);
// vex::motor drive_l4 = vex::motor(PORT8, DRIVE_INSERT, false);

// Subsystem 3
vex::motor intake = vex::motor(PORT8, INTAKE_INSERT, false);
#endif

// Wings
vex::digital_out wing_fl = vex::digital_out(PORTD);
vex::digital_out wing_fr = vex::digital_out(PORTC);

vex::digital_out hang_release = vex::digital_out(PORTA);
vex::digital_out intake_toggle = vex::digital_out(PORTE);
vex::digital_out pto = vex::digital_out(PORTB);

// Sensors
vex::inertial imu = vex::inertial(PORT20);

vex::motor_group drive_r = vex::motor_group(drive_r1, drive_r2, drive_r3);
vex::motor_group drive_l = vex::motor_group(drive_l1, drive_l2, drive_l3);
vex::motor_group drive_full = vex::motor_group(drive_r1, drive_r2, drive_r3, drive_l1, drive_l2, drive_l3);

// vex::motor_group intake = vex::motor_group(intake_9, intake_10);

// Auton switcher
vex::digital_in auto_selector = vex::digital_in(PORTH);
