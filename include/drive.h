#pragma once

#include "main.h"

/**
 * @brief Set of control schemes for the driver
 */
enum DriveType {
	TWO_STICK_ARCADE,
	TWO_STICK_ARCADE_SOUTHPAW,
	ONE_STICK_ARCADE,
	ONE_STICK_ARCADE_SOUTHPAW,
	TANK,
};

typedef struct _driver_config_t {
	DriveType drive_type;
	double rot_mod;
	double speed_mod;
} driver_config_t;

typedef struct _pid_consts_t {
	double kp;
	double ki;
	double kd;
} pid_consts_t;

typedef struct _pid_configs_t {
	pid_consts_t move_accel;
	pid_consts_t move_dir;
	pid_consts_t linear;
	pid_consts_t rotate;
	pid_consts_t arc;
} pid_configs_t;

/**
 * @brief A class to control the drivetrain of a robot
 */
class Drive {
private:
	/* A motor group for the left half of the drive */
	vex::motor_group left;

	/* A motor group for the right half of the drive */
	vex::motor_group right;

	driver_config_t drive_conf;

	pid_configs_t pid_confs;

public:
	Drive();

	Drive(vex::motor_group left, vex::motor_group right,
			driver_config_t driver_conf, pid_configs_t pid_confs);

	/**
	 * @brief Constructor
	 *
	 * @param left The motor group for the left half of the drive
	 * @param right The motor group for the right half of the drive
	 * @param drive_type The driver control scheme to use
	 * @param rot_mod The driver rotation speed modifier. 0 disables turning,
	 * 1 is full speed.
	 * @param speed_mod The driver linear speed modifier. 0 disables movement,
	 * 1 is full speed.
	 */
	Drive(vex::motor_group left, vex::motor_group right, DriveType drive_type,
		  double rot_mod, double speed_mod);

	/**
	 * @brief Constructor
	 * @param left The motor group for the left half of the drive
	 * @param right The motor group for the right half of the drive
	 * @param drive_type The driver control scheme to use
	 * @param rot_mod The driver rotation speed modifier. 0 disables turning,
	 * 1 is full speed.
	 * @param speed_mod The driver linear speed modifier. 0 disables movement,
	 * 1 is full speed.
	 * @param move_pid The PID object to control the move function
	 * @param rotate_pid The PID object to control the rotate function
	 * @param arc_pid The PID object to control the arc function
	 */
	Drive(vex::motor_group left, vex::motor_group right, DriveType drive_type,
		  double rot_mod, double speed_mod, Pid &move_accel_pid,
		  Pid &move_dir_pid, Pid &rotate_pid, Pid &arc_pid);

	/**
	 * @brief Sets the driver control scheme
	 *
	 * @param drive_type The control scheme to use
	 */
	void set_drive_type(DriveType drive_type);

	/**
	 * @brief Sets the driver rotation speed modifier
	 *
	 * @param rot_mod The rotation speed modifier to use. 0 disables rotation,
	 * 1 is full speed.
	 */
	void set_rot_mod(double rot_mod);

	/**
	 * @brief Sets the driver linear speed modifier
	 *
	 * @param speed_mod The linear speed modifier to use. 0 disables movement,
	 * 1 is full speed.
	 */
	void set_speed_mod(double speed_mod);

	/**
	 * @brief Allows a controller to control the robot. Intended to be called
	 * from within a loop.
	 */
	void opdrive();

	/**
	 * @brief Moves the robot in a given direction at a given speed for a given
	 * amount of time. Does not use feedback control.
	 *
	 * @param dir The direction to move
	 * @param msec The number of milliseconds to be moving for
	 * @param pct The percentage of max velocity at which to move
	 */
	void ram(vex::directionType dir, double msec, double pct);

	/**
	 * @brief PID aided forward/backward movement. PID is used to maintain 
	 * speed and direction.
	 *
	 * @param in The number of inches to move. Positive values go forward, 
	 * negative values go backward.
	 * @param ips The velocity (in inches per second) to travel. Always
	 * positive.
	 * @param ipss The acceleration (in inches per second squared) to travel.
	 * Always positive.
	 * @param do_decel Whether to decelerate at the end of the function
	 */
	void linear(double in, double ips, double ipss, bool do_decel);

	/**
	 * @brief PID aided forward/backward movement. PID is used to maintain 
	 * speed and direction.
	 *
	 * @param in The number of inches to move. Positive values go forward, 
	 * negative values go backward.
	 * @param ips The velocity (in inches per second) to travel. Always
	 * positive.
	 * @param ipss The acceleration (in inches per second squared) to travel.
	 * Always positive.
	 * @param do_decel Whether to decelerate at the end of the function
	 * @param lockout Whether to lock out the user from other actions until the
	 * function has finished running. Equivalent to vex`s `waitForCompletion`.
	 */
	void linear(double in, double ips, double ipss, bool do_decel, bool lockout);

	/**
	 * @brief PID aided rotation in place. PID maintain direction and 
	 * indirectly controls speed.
	 *
	 * @param deg The number of degrees to turn. Positive is clockwise.
	 * @param ratio The ratio of the outer turn radius to the inner turn
	 * radius. Should remain set to -1. Currently BROKEN.
	 * @param dir I forget what this was for, honestly. Should remain set to 1.
	 * Currently BROKEN.
	 */
	void rotate(double deg, double ratio, int dir);

	/**
	 * @brief PID aided arcing function. PID is used to maintain speed.
	 *
	 * @param deg The number of degrees to turn. Positive is clockwise.
	 * @param radius The outer radius of the turn in inches
	 * @param ips The velocity (in inches per second) of the turn. Always
	 * positive.
	 * @param ipss The acceleration (in inches per second squared) of the turn.
	 * Alawys positive.
	 * @param reversed Whether to arc backward
	 *
	 * This function is slow, and very BROKEN. Should be avoided when possible.
	 * There is no functioning PID assistance and the reversed modifier is
	 * broken. Certain parameters need to be set to negative when turning in
	 * reverse or counterclockwise. I forget which parameters these are. Good
	 * luck.
	 */
	void arc(double deg, double radius, double ips, double ipss, bool reversed);

	void tune_move();
	void tune_rotate();
	void tune_arc();
};
