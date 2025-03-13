#pragma once

#include "main.h"

typedef struct _pid_consts_t {
	double kp;
	double ki;
	double kd;
} pid_consts_t;

/**
 * @brief pid object for general pid
 */
class Pid {
private:
	pid_consts_t consts;

    double error;
    double sum;
    double prev_error;
    double deriv;

    bool do_print_val;

public:
    Pid();
    Pid(double kp, double ki, double kd);
    explicit Pid(pid_consts_t consts);
    double calc(double setpoint, double sensor_value);
    void tune_kP(float value, float mod);
    void tune_kI(float value, float mod);
    void tune_kD(float value, float mod);

    float get_const(char constant);
};
