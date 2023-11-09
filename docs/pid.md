# PID class

```cpp
PID::PID(double init_kP, double init_kI, double init_kD);
```

Takes initial P, I, and D constants.  
Creates a PID object for using PID control loops.

---

```cpp
double PID::pid_adjust(double setpoint, double current_value);
```

Takes a target value and the current value.  
Returns the modifier for a PID control loop.

**P(roportional)**: distance to target (error). Basically, if setpoint is far away, change the current value faster.  
**I(ntegral)**: Error buildup. If error keeps getting bigger, change current value faster.  
**D(erivative)**: Rate of change of error. If error is oscillating around the setpoint, change current value slower.

---

```cpp
void PID::tune_X(float stick_mod);
```

Takes the scaling value for controller (so that a human can change the values slow enough to use).  
Tunes the X (either kP, kI, or kD) value.

---

```cpp
float PID::get_const(char constant);
```

Takes the character of the constant.  
Returns the current value of the constant.

# drive_straight()

```cpp
void drive_straight(float inches, float target_ips, float ips_per_sec);
```

Takes inches to travel, maximum inches/second, and acceleration in inches/sec/sec.  
Moves the drive along one heading according to those values.

### Explanation

```cpp
if (std::abs(pos) + stop_dist(ips, ips_per_sec) >= std::abs(inches))
    ips -= ips_per_sec / 50;    // 50 hz
else if (ips < target_ips)
    ips += target_ips / 50;
else ips = target_ips;
```

Handles acceleration

If the current distance travelled plus the distance needed to stop exceeds the target distance, slow down. Otherwise, if the current speed is less than target speed, speed up. Otherwise, set speed to the target speed (to prevent moving faster than the target).

# drive_turn()

```cpp
void drive_turn(float degrees, float outer_radius, float target_ips, float ips_per_sec, bool reversed);
```

Takes the degrees to turn, the outer radius of the turn (inches), the speed of the turn (in/sec), the acceleration of the turn (in/sec/sec), and whether or not to arc backwards.
Turns in an arc with radius `outer_radius`.

### Explanation

```cpp
target_heading += degrees;
```

To maintain the target heading between function calls, it is stored as a global variable. This adds to the heading the relative number of degrees needed to turn.

---

```cpp
int dir_mod = (degrees > 0) ? 1 : -1;
```

If turning right, dir_mod = 1. Otherwise, it's -1.  
Used to flip some values depending on the direction being turned.

---

```cpp
degrees_remaining = target_heading - ROTATION * GYRO_CORRECTION;
```

The number of degrees left in the turn. If I want to go 90°, and I've turned 30° so far, this is 60°.

---

```cpp
if (std::abs(degrees_remaining / RAD__DEG * outer_radius) - stop_dist(ips, ips_per_sec) <= 0)
    ips -= ips_per_sec / 50.0;
else if (ips < target_ips)
    ips += ips_per_sec / 50.0;   // 50 cycles per second
else ips = target_ips;
```

Handles acceleration.

First, `degrees_remaining` is converted to radians to get the number of radii left in the turn. Then it gets multiplied by the length of one radius to get the number of inches left in the turn. Other than that, it follows the logic of drive_straight().

---

```cpp
outer_pos += ips / 50;
inner_pos = outer_pos * radius_ratio;
```

Updates the distance each side should have traveled.

---

```cpp
if ((reversed && degrees > 0) || (!reversed && !(degrees > 0))) {      // left is inner side
    pid_adjustment_l = -1 * pid_drive_l.pid_adjust(inner_pos, pos_l);
    pid_adjustment_r = pid_drive_r.pid_adjust(outer_pos, pos_r);

    drive_l.spin(DIR_FWD, dir_mod * inner_vel_rpm + pid_adjustment_l, VEL_RPM);
    drive_r.spin(DIR_FWD, dir_mod * outer_vel_rpm + pid_adjustment_r, VEL_RPM);
}
else {      // right is inner side
    pid_adjustment_l = pid_drive_l.pid_adjust(outer_pos, pos_l);
    pid_adjustment_r = -1 * pid_drive_r.pid_adjust(inner_pos, pos_r);

    drive_l.spin(DIR_FWD, dir_mod * outer_vel_rpm + pid_adjustment_l, VEL_RPM);
    drive_r.spin(DIR_FWD, dir_mod * inner_vel_rpm + pid_adjustment_r, VEL_RPM);
}
```

Currently bugged. Supposed to turn in arc of 1 of 4 directions: forward-left, fwd-right, backward-left, bwd-right. Actually only turns fwd. If turning left, reversed must be true.

Intended behavior:  c
Determine which side (left or right) is the outside of the turn. Give that side `outer_vel_rpm`, and the inside `inner_vel_rpm`. Flip PID modifier on the inside of the turn.
