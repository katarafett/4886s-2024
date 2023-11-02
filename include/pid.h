/**
 * @brief pid object for general pid cojtroo
 */
class PID {
    private:

        bool do_p;
        bool do_i;
        bool do_d;

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

        double kP;
        double kI;
        double kD;
};

