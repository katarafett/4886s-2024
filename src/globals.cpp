#include "main.h"

const double PI = 3.1415926535897932384626433832795;

const int TICKS_PER_SEC = 50;
const int MSEC_PER_TICK = 1000 / TICKS_PER_SEC;

// Which auton will run
int auton_mode = RED_QUAD;
// Heading robot should follow
float target_heading = 0;

// PID constants
float turn_kp_l = 1.05;
float turn_ki_l = 0;
float turn_kd_l = 4.575;

float turn_kp_r = 1.05;
float turn_ki_r = 0;
float turn_kd_r = 4.575;

float move_kp = 0, move_ki = 0, move_kd = 0;
float drive_accel_kp = DRIVE_STRAIGHT_DIR_KP, drive_accel_ki = DRIVE_STRAIGHT_DIR_KI, drive_accel_kd = DRIVE_STRAIGHT_DIR_KD;
float drive_dir_kp = 0, drive_dir_ki = 0, drive_dir_kd = 0;
