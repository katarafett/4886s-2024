float pid_a(float setpoint, float current_value, float *sum, float *prev_error,
        double constants[3]);

/**
 * @brief moves with pid
 *
 * @param dist inches to travel
 * @param max_vel max inch/sec
 * @param accel inches/sec/sec to accelerate
 * @param do_decel whether or not to decel
 */
void pid_move(float dist, float max_vel, float accel = 24,
        bool do_decel = true);

/**
 * @brief drives straight using pid
 *
 * @param dist inches to travel
 * @param maxVel max in/sec
 * @param accel in/sec/sec to accelerate
 */
void drive_straight(float dist, float maxVel, float accel);

/**
 * @brief turns in an arc
 *
 * @param radians turns to this angle - does NOT increase by this angle
 * @param outerRadius outer radius of turn
 * @param maxVel max velocity in in/sec of turn
 * @param accel acceleration in in/sec/sec of turn
 * @param reversed turning backwards?
 */
void drive_turn(float deg, float outerRadius, float maxVel, float accel,
        bool reversed = true);

void press_back(bool toggle_pressing);

bool within_range(double value, double base, double range);

float stop_dist(float current_vel, float accel, float target_vel = 0);

/**
 * @brief detects which side of the brain is pressed
 *
 * @return an array [x, y]
 */
int *side_pressed(void);
