#include "main.h"
#include "stddefs.h"
#include "v5_apitypes.h"
#include "vex_global.h"
#include "vex_triport.h"

#define DRIVE_INSERT vex::gearSetting::ratio6_1
#define INTAKE_INSERT vex::gearSetting::ratio6_1

vex::brain Brain;
vex::controller master;


/* START OF DRIVE CONFIG */

// Drive motors
vex::motor drive_r1 = vex::motor(PORT14, DRIVE_INSERT, false);
vex::motor drive_r2 = vex::motor(PORT15, DRIVE_INSERT, false);
vex::motor drive_r3 = vex::motor(PORT16, DRIVE_INSERT, true);
vex::motor drive_l1 = vex::motor(PORT11, DRIVE_INSERT, false);
vex::motor drive_l2 = vex::motor(PORT12, DRIVE_INSERT, true);
vex::motor drive_l3 = vex::motor(PORT13, DRIVE_INSERT, true);

// Drive halves
vex::motor_group drive_r = vex::motor_group(drive_r1, drive_r2, drive_r3);
vex::motor_group drive_l = vex::motor_group(drive_l1, drive_l2, drive_l3);

// Config for the driver
driver_config_t driver_conf = {TWO_STICK_ARCADE, 0.6, 1.0};

// Individual PID constants
pid_consts_t move_accel = {1.0, 0.0, 0.0};
pid_consts_t move_dir = {1.0, 0.0, 0.0};
pid_consts_t linear = {1.0, 0.0, 0.0};
pid_consts_t rotate = {1.0, 0.0, 0.0};
pid_consts_t arc = {1.0, 0.0, 0.0};

// All PID configs
pid_configs_t pid_confs = {move_accel, move_dir, linear, rotate, arc};

// The drive object
Drive drive = Drive(drive_r, drive_l, driver_conf, pid_confs);

/* END OF Drive drive CONFIG */


// Subsystem 3
vex::motor intakeLow = vex::motor(PORT1, INTAKE_INSERT, true);
vex::motor intakeHigh = vex::motor(PORT19, INTAKE_INSERT, true);

vex::motor lift = vex::motor(PORT3, vex::gearSetting::ratio18_1, false);

// 3 Wire Ports
vex::digital_out mogo_clamp = vex::digital_out(PORTA);
vex::digital_out Smith_Mech = vex::digital_out(PORTB);
vex::digital_out intake_lift = vex::digital_out(PORTD);
vex::digital_out PTO = vex::digital_out(PORTC);


// Sensors
vex::inertial imu = vex::inertial(PORT20);
vex::optical colorSort = vex::optical(PORT12);

vex::motor_group intake = vex::motor_group(intakeLow, intakeHigh);

vex::rotation liftDegree = vex::rotation(PORT10);
