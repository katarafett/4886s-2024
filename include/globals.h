#pragma once

extern const double PI;

extern const int TICKS_PER_MSEC;
extern const int MSEC_PER_TICK;

// Drive gear ratio
extern const double DRIVE_GEARING;
// Connversion factor from motor revolutions to inches travelled
extern const double DRIVE_REV_TO_IN;
extern const float WHEEL_TO_WHEEL_DIST;

// Brain sides and coordinates
#define X 0
#define Y 1
#define LEFT 1
#define UP 1
#define RIGHT 2
#define DOWN 2

// Correct inertial sensor error
#define IMU_CORRECTION (1.0035)
// Height in pixels of default characters on brain
#define CHAR_HI 20
#define CHAR_WI 12

enum autons {
	FULL_AWP,
	BLUE_QUAD,
	BLUE_RUSH,
	RED_QUAD,
	RED_RUSH,
	ELIMS_RED,
	SKILLS,
};

// Global variable declarations
extern int auton_mode;
extern float target_heading;

// Selection
extern const char *control_types[6];
extern const char *auton_types[4];

extern float turn_kp_l;
extern float turn_ki_l;
extern float turn_kd_l;

extern float turn_kp_r;
extern float turn_ki_r;
extern float turn_kd_r;

extern float move_kp, move_ki, move_kd;

extern float drive_accel_kp, drive_accel_ki, drive_accel_kd;
extern float drive_dir_kp, drive_dir_ki, drive_dir_kd;
