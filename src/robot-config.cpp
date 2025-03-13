#include "robot-config.h"

const vex::gearSetting DRIVE_INSERT = vex::gearSetting::ratio6_1;
const vex::gearSetting INTAKE_INSERT = vex::gearSetting::ratio6_1;
const vex::gearSetting LIFT_INSERT = vex::gearSetting::ratio18_1;

vex::brain Brain;
vex::controller master;


/* START OF DRIVE CONFIG */

// Drive motors
vex::motor drive_r1 = vex::motor(vex::PORT14, DRIVE_INSERT, false);
vex::motor drive_r2 = vex::motor(vex::PORT15, DRIVE_INSERT, false);
vex::motor drive_r3 = vex::motor(vex::PORT16, DRIVE_INSERT, true);
vex::motor drive_l1 = vex::motor(vex::PORT11, DRIVE_INSERT, false);
vex::motor drive_l2 = vex::motor(vex::PORT12, DRIVE_INSERT, true);
vex::motor drive_l3 = vex::motor(vex::PORT13, DRIVE_INSERT, true);

// Drive halves
vex::motor_group drive_r = vex::motor_group(drive_r1, drive_r2, drive_r3);
vex::motor_group drive_l = vex::motor_group(drive_l1, drive_l2, drive_l3);

// Physical drivebase config
drive_config_t drive_conf = {11.5, 3.25, 36 / 48.0};

// Config for the driver
op_config_t op_conf = {TWO_STICK_ARCADE, 0.6, 1.0};

// The drive object. Uses default (no) Pid
Drive drive = Drive(drive_r, drive_l, drive_conf, op_conf);

/* END OF DRIVE CONFIG */


// Subsystem 3
vex::motor intakeLow = vex::motor(vex::PORT1, INTAKE_INSERT, true);
vex::motor intakeHigh = vex::motor(vex::PORT19, INTAKE_INSERT, true);

vex::motor lift = vex::motor(vex::PORT3, LIFT_INSERT, false);

// 3 Wire Ports
vex::digital_out mogo_clamp = vex::digital_out(Brain.ThreeWirePort.A);
vex::digital_out Smith_Mech = vex::digital_out(Brain.ThreeWirePort.B);
vex::digital_out intake_lift = vex::digital_out(Brain.ThreeWirePort.D);
vex::digital_out PTO = vex::digital_out(Brain.ThreeWirePort.C);

// Sensors
vex::inertial imu = vex::inertial(vex::PORT20);


vex::timer timer = vex::timer();
