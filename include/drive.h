#pragma once

#include "main.h"

/**
 * Set of control schemes for the driver
 */
enum ControlType {
	TWO_STICK_ARCADE,
	TWO_STICK_ARCADE_SOUTHPAW,
	ONE_STICK_ARCADE,
	ONE_STICK_ARCADE_SOUTHPAW,
	TANK,
};

/**
 * The physical configuration of the drivebase
 */
typedef struct _drive_config_t {
	double wheelbase;
	double wheeldiam;
	double gear_ratio;
} drive_config_t;

/**
 * The configuration for the operator
 */
typedef struct _op_congig_t {
	ControlType control_type;
	double rot_mod;
	double speed_mod;
} op_config_t;

/**
 * The PID configurations for drive functions
 */
typedef struct _dr_pid_configs_t {
	pid_consts_t linear_accel;
	pid_consts_t linear_dir;
	pid_consts_t fast_linear;
	pid_consts_t rotate;
	pid_consts_t arc;
} dr_pid_configs_t;


/**
 * @brief A class to control the drivetrain of a robot
 */
class Drive {
private:
	/* A motor group for the left half of the drive */
	vex::motor_group left;
	/* A motor group for the right half of the drive */
	vex::motor_group right;
	/* The physical configuration of the drivebase */
	drive_config_t drive_conf;
	/* The configuration for operator control */
	op_config_t op_conf;
	/* The PID configurations for drive functions */
	dr_pid_configs_t pid_confs;

public:
	Drive();

	Drive(vex::motor_group left, vex::motor_group right, drive_config_t drive_conf);

	Drive(vex::motor_group left, vex::motor_group right, drive_config_t drive_conf,
		  op_config_t op_conf);

	Drive(vex::motor_group left, vex::motor_group right, drive_config_t drive_conf,
		  op_config_t op_conf, dr_pid_configs_t pid_confs);

	/**
	 * @brief Allows a controller to control the robot. Intended to be called
	 * from within a loop.
	 */
	void opdrive();

	void linear(double dist, double vel, double accel);
	void fast_linear(const double dist, const int short_time, const int long_time, const double range);
	void turn(double deg);
	void arc(double deg, double r, double vel, double accel, bool reversed);

	double get_lpos();
	double get_rpos();

	vex::motor_group get_left();
	vex::motor_group get_right();
	drive_config_t get_drive_conf();
	op_config_t get_op_conf();
	dr_pid_configs_t get_pid_confs();
	void set_drive_conf(drive_config_t drive_conf);
	void set_op_conf(op_config_t op_conf);
	void set_pid_confs(dr_pid_configs_t pid_confs);
};
