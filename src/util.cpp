#include "../include/main.h"

// Utility functions

// Returns whether a value is within range of a base value
bool within_range(double value, double base_value, double range) {
    return ((value <= base_value + range) && (value >= base_value - range));
}

// Derived from standard acceleration formula
float stop_dist(float current_vel, float acceleration, float target_vel) {
    return -(target_vel * target_vel - current_vel * current_vel) / (2 * acceleration);
}

// Returns quadrant of brain
int *side_pressed(void) {
    static int sides[2];
    if (!B_SCRN.PRESSED) {
        sides[0] = 0;
        sides[1] = 0;
        return sides;
    }

    if (B_SCRN.xPosition() < B_SCRN_X_MID)
        sides[X] = LEFT;
    else
        sides[X] = RIGHT;

    if (B_SCRN.yPosition() < B_SCRN_Y_MID)
        sides[Y] = UP;
    else
        sides[Y] = DOWN;

    return sides;
}

void tune_gyro(void) {
    imu.calibrate();
    while (imu.isCalibrating())
        wait(20, vex::msec);

    while (1) {
        B_SCRN.clearScreen();
        B_SCRN.setCursor(1, 1);
        B_SCRN.print("%.1f", ROTATION);
        wait(20, vex::msec);
    }
}

void handle_acceleration(float position, float distance, float velocity,
        float max_velocity, float acceleration, int tick_rate, bool do_decel) {
    if (std::abs(position) + stop_dist(velocity, acceleration) >= std::abs(distance) && do_decel)
        velocity -= acceleration / tick_rate;
    else if (velocity < max_velocity)
        velocity += acceleration / tick_rate;
    else velocity = max_velocity;
}

// Shorthand functions

// Position in inches
double pos_drive_r() {
    return drive_r.position(vex::rotationUnits::rev) * DRIVE_REV__IN;
}
double pos_drive_l() {
    return drive_l.position(vex::rotationUnits::rev) * DRIVE_REV__IN;
}
// Velocity in inches per second
double vel_drive_r() {
    return drive_r.velocity(vex::rpm) * DRIVE_REV__IN * 60;
}
double vel_drive_l() {
    return drive_l.velocity(vex::rpm) * DRIVE_REV__IN * 60;
}

// Heading in degrees
double imu_rotation() {
    return imu.rotation() * IMU_CORRECTION;
}

// Controller joystick shorthand
double axis_rx() {
    return master.Axis1.position();
}
double axis_ry() {
    return master.Axis2.position();
}
double axis_lx() {
    return master.Axis3.position();
}
double axis_ly() {
    return master.Axis4.position();
}

// Controller button shorthand
double btn_r1() {
    return master.ButtonR1.pressing();
}
double btn_r2() {
    return master.ButtonR2.pressing();
}
double btn_l1() {
    return master.ButtonL1.pressing();
}
double btn_l2() {
    return master.ButtonL2.pressing();
}

double btn_a() {
    return master.ButtonA.pressing();
}
double btn_b() {
    return master.ButtonB.pressing();
}
double btn_x() {
    return master.ButtonX.pressing();
}
double btn_y() {
    return master.ButtonY.pressing();
}
