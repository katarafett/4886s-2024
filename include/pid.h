#include "globals.h"

/**
 * @brief pid object for general pid cojtroo
 */
class PID {
    private:
        bool do_p;
        bool do_i;
        bool do_d;

        double kP;
        double kI;
        double kD;

        double error;
        double sum;
        double prev_error;
        double deriv;

        bool do_print_val;
    public:
        PID();
        PID(double init_kP, double init_kI, double init_kD);
        double pid_adjust(double setpoint, double current_value);
        void tune_kP(float stick_mod);
        void tune_kI(float stick_mod);
        void tune_kD(float stick_mod);

        float get_const(char constant);
};

/**
 * @param inches distance to travel - postive or negative
 * @param target_ips goal for velocity - positive
 * @param ips_per_sec acceleration - positive
 */
void drive_straight(float inches, float target_ips, float ips_per_sec, bool do_decel = true);

/**
 * @param degrees changes target heading
 * @param turn_radius outer radius of the turn
 * @param target_ips goal for velocity - positive
 * @param ips_per_sec acceleration
 * @param reversed are we moving backwards?
 */
void drive_turn(float degrees, float turn_radius, float target_ips, float ips_per_sec, bool reversed = false);

/**
 * @param inches distance to travel linearly
 * @param target_ips velocity
 * @param ips_per_sec acceleration
 * @param do_decel whether to decelerate
 */
void drive_linear(float inches, float target_ips, float ips_per_sec, float do_decel = true);

/**
 * @param degrees changes target heading
 * @param target_ips goal for velocity - positive
 * @param ips_per_sec acceleration
 * @param turn_radius outer radius of the arc
 * @param reversed are we moving backwards?
 */
void drive_arc(float degrees, float max_ips, float ips_per_sec, float turn_radius, bool do_decel, bool reversed);
