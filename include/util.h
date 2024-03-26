/**
 * @brief detects when a value is within range of a base value
 *
 * @param value value to check against
 * @param base_value center of valid range
 * @param range distance from base that returns true
 * @return whether it is within range of base
 */
bool within_range(double value, double base_value, double range);

/**
 * @brief finds distance to reach a target velocity given a certain acceleraion
 *
 * @param current_vel the current velocity
 * @param accel the expected acceleration
 * @param target_vel the target velocity to reach
 * @return the distance to reach target velocity
 */
float stop_dist(float current_vel, float accel, float target_vel = 0);

/**
 * @brief detects which side of the brain is pressed
 *
 * @return an array [x, y]
 */
int *side_pressed(void);

/**
 * @brief find gyro discrepencies
 */
void tune_gyro(void);

/**
 * @brief changes velocity at the acceleration rate
 *
 * @param dist disance travelled so far
 * @param target_dist desired distance to travel
 * @param vel current velocity
 * @param max_vel maximum velocity allowed
 * @param accel rate of acceleration
 * @param tps number of times this function is called per time unit of accel
 * @param do_decel whether to decelerate
 */
void handle_acceleration(float dist, float target_dist, float *vel, float max_vel,
        float accel, int tps, bool do_decel);
