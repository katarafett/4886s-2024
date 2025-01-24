#include "main.h"
#include <thread>

Drive::Drive() {}

Drive::Drive(vex::motor_group left, vex::motor_group right, DriveType drive_type,
			 double rot_mod, double speed_mod) {
	Pid move_pid = Pid(0, 0, 0);
	Pid rotate_pid = Pid(0, 0, 0);
	Pid arc_pid = Pid(0, 0, 0);

	Drive(left, right, drive_type, rot_mod, speed_mod, move_pid, rotate_pid, arc_pid);
}

Drive::Drive(vex::motor_group left, vex::motor_group right, DriveType drive_type,
			 double rot_mod, double speed_mod, Pid &move_pid, Pid &rotate_pid,
			 Pid &arc_pid) {
	this->left = left;
	this->right = right;
	this->drive_type = drive_type;
	this->rot_mod = rot_mod;
	this->speed_mod = speed_mod;
	this->move_pid = move_pid;
	this->rotate_pid = rotate_pid;
	this->arc_pid = arc_pid;
}

void Drive::set_drive_type(DriveType drive_type) {
	this->drive_type = drive_type;
}

void Drive::set_rot_mod(double rot_mod) {
	this->rot_mod = rot_mod;
}

void Drive::set_speed_mod(double speed_mod) {
	this->speed_mod = speed_mod;
}

void Drive::opdrive() {
	switch (drive_type) {
	case TWO_STICK_ARCADE:
		left.spin(vex::fwd, (axis_ly() + axis_rx() * rot_mod) * speed_mod, vex::pct);
		right.spin(vex::fwd, (axis_ly() - axis_rx() * rot_mod) * speed_mod, vex::pct);
		break;
	case TWO_STICK_ARCADE_SOUTHPAW:
		left.spin(vex::fwd, (axis_ry() + axis_lx() * rot_mod) * speed_mod, vex::pct);
		right.spin(vex::fwd, (axis_ry() - axis_lx() * rot_mod) * speed_mod, vex::pct);
		break;
	case ONE_STICK_ARCADE:
		left.spin(vex::fwd, (axis_ly() + axis_lx() * rot_mod) * speed_mod, vex::pct);
		right.spin(vex::fwd, (axis_ly() - axis_lx() * rot_mod) * speed_mod, vex::pct);
		break;
	case ONE_STICK_ARCADE_SOUTHPAW:
		left.spin(vex::fwd, (axis_ry() + axis_rx() * rot_mod) * speed_mod, vex::pct);
		right.spin(vex::fwd, (axis_ry() - axis_rx() * rot_mod) * speed_mod, vex::pct);
		break;
	case TANK:
		left.spin(vex::fwd, axis_ly(), vex::pct);
		right.spin(vex::fwd, axis_ry(), vex::pct);
	}
}

void Drive::ram(vex::directionType dir, double msec, double pct) {
	left.spinFor(dir, msec, vex::msec, pct, vex::velocityUnits::pct);
	right.spinFor(dir, msec, vex::msec, pct, vex::velocityUnits::pct);
}
