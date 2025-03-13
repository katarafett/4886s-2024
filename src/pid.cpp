#include "main.h"
#include "stddefs.h"

Pid::Pid() {}

Pid::Pid(double kp, double ki, double kd) {
	Pid(pid_consts_t {kp, ki, kd});
}

Pid::Pid(pid_consts_t consts) {
	this->consts = consts;

	error = 0;
	sum = 0;
	prev_error = 0;
	deriv = 0;
}

void Pid::tune_kP(float value, float mod) {
	consts.kp += value * mod;
	printf("consts.kp: %lf\n", consts.kp);
	B_SCRN.setCursor(3, 4);
	B_SCRN.print("consts.kp: %lf", consts.kp);
}

void Pid::tune_kI(float value, float mod) {
	consts.ki += value * mod;
	printf("consts.ki: %lf\n", consts.ki);
	B_SCRN.setCursor(5, 4);
	B_SCRN.print("consts.ki: %lf", consts.ki);
}

void Pid::tune_kD(float value, float mod) {
	consts.kd += value * mod;
	printf("consts.kd: %lf\n", consts.kd);
	B_SCRN.setCursor(7, 4);
	B_SCRN.print("consts.kd: %lf", consts.kd);
}

float Pid::get_const(char constant) {
	if (constant == 'p')
		return this->consts.kp;
	if (constant == 'i')
		return this->consts.ki;
	if (constant == 'd')
		return this->consts.kd;
	return 0;
}

double Pid::calc(double setpoint, double sensor_value) {
	error = setpoint - sensor_value;
	// Only increment sum if I loop is used
	if (consts.ki != 0)
		sum += error;
	deriv = error - prev_error;
	prev_error = error;

	return (error * consts.kp) + (sum * consts.ki) + (deriv * consts.kd);
}
