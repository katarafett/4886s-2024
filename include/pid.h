#pragma once

#include "globals.h"

/**
 * @brief pid object for general pid cojtroo
 */
class Pid {
private:
    double kP;
    double kI;
    double kD;

    double error;
    double sum;
    double prev_error;
    double deriv;

    bool do_print_val;

public:
    Pid();
    Pid(double init_kP, double init_kI, double init_kD);
    double adjust(double setpoint, double sensor_value);
    void tune_kP(float value, float mod);
    void tune_kI(float value, float mod);
    void tune_kD(float value, float mod);

    float get_const(char constant);
};
