#include "../include/main.h"

// Which auton will run
int auton_mode = HALF_AWP_NEAR;
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

