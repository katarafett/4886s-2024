#include "main.h"
#include "util.h"

Drive::Drive() {}

Drive::Drive(vex::motor_group left, vex::motor_group right, drive_config_t drive_conf) {
	// Sane default drive config
	op_config_t op_conf = {TANK, 1.0, 1.0};

	Drive(left, right, drive_conf, op_conf);
}

Drive::Drive(vex::motor_group left, vex::motor_group right, drive_config_t drive_conf,
			 op_config_t op_conf) {
	// Defaults to no PID config
	dr_pid_configs_t pid_confs = {pid_consts_t{0, 0, 0}, pid_consts_t{0, 0, 0},
								  pid_consts_t{0, 0, 0}, pid_consts_t{0, 0, 0},
								  pid_consts_t{0, 0, 0}};

	Drive(left, right, drive_conf, op_conf, pid_confs);
}

Drive::Drive(vex::motor_group left, vex::motor_group right, drive_config_t drive_conf,
			 op_config_t op_conf, dr_pid_configs_t pid_confs) {
	this->left = left;
	this->right = right;
	this->drive_conf = drive_conf;
	this->op_conf = op_conf;
	this->pid_confs = pid_confs;
}

void Drive::opdrive() {
	const ControlType control_type = op_conf.control_type;
	const double rot_mod = op_conf.rot_mod;
	const double speed_mod = op_conf.speed_mod;

	switch (control_type) {
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
		break;
	}
}

void Drive::linear(double dist, double vel, double accel) {
	double pos = (get_lpos() + get_rpos()) / 2;
	Pid pid_left = Pid(pid_confs.linear_accel);
	Pid pid_right = Pid(pid_confs.linear_accel);
	Pid pid_dir = Pid(pid_confs.linear_dir);

	const double start_l = get_lpos();
	const double start_r = get_rpos();
}

void Drive::fast_linear(const double dist, const int short_time = 60,
						const int long_time = 2000, const double range = 1) {
	Pid pid_l = Pid(pid_confs.fast_linear);
	Pid pid_r = Pid(pid_confs.fast_linear);

	const double travel_deg = dist / PI / drive_conf.wheeldiam * 360;
	const double final_lpos = get_lpos() + travel_deg;
	const double final_rpos = get_rpos() + travel_deg;

	int time_still = 0;
	const int end_time = timer.time() + long_time;

	while (time_still < short_time && timer.time() < end_time) {
		if (within_range(get_lpos(), final_lpos, range) &&
			within_range(get_rpos(), final_rpos, range)) {
			time_still += MSEC_PER_TICK;
		}

		left.spin(vex::fwd, pid_l.calc(final_lpos, get_lpos()), vex::pct);
		right.spin(vex::fwd, pid_r.calc(final_rpos, get_rpos()), vex::pct);

		vex::wait(MSEC_PER_TICK, vex::msec);
	}
}

void Drive::turn(double deg) {
}

void Drive::arc(double deg, double r, double vel, double accel, bool reversed) {
}

double Drive::get_lpos() {
	return left.position(vex::deg);
}

double Drive::get_rpos() {
	return right.position(vex::deg);
}
