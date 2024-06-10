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
vex::motor intake = vex::motor(PORT8, INTAKE_INSERT, true);
vex::motor lift = vex::motor(PORT7, vex::gearSetting::ratio18_1, false);
#endif

// Wings
vex::digital_out hang_release = vex::digital_out(PORTA);
// Sensors
vex::inertial imu = vex::inertial(PORT20);

vex::vision::signature red_ring = vex::vision::signature (3, 7579, 10923, 9251, -891, -433, -662, 4, 0);
vex::vision::signature blue_ring = vex::vision::signature (2, -3329, -2595, -2962, 5431, 6685, 6058, 5.8, 0);
vex::vision vision1 = vex::vision(PORT10, 17, red_ring);

vex::motor_group drive_r = vex::motor_group(drive_r1, drive_r2, drive_r3);
vex::motor_group drive_l = vex::motor_group(drive_l1, drive_l2, drive_l3);
vex::motor_group drive_full = vex::motor_group(drive_r1, drive_r2, drive_r3, drive_l1, drive_l2, drive_l3);

// vex::motor_group intake = vex::motor_group(intake_9, intake_10);

// Auton switcher
vex::digital_in auto_selector = vex::digital_in(PORTH);
