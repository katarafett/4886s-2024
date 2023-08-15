// Physical bits
#define DRIVE_GEARING (GEAR_48 / GEAR_72)
#define DRIVE_REV__IN (DRIVE_GEARING * PI * TRACT_WHEEL_DIAM)
#define WHEEL_TO_WHEEL_DIST 12

#define DRIVE_KP 0.92
#define DIR_KP 3.75
#define FLY_KP 0.3
#define FLY_ACCEL 18

#define DRIVE_INSERT SPD_INSERT
#define FLYWHEEL_INSERT TRB_INSERT
#define INTAKE_INSERT TRB_INSERT

// Autonmous modes
#define AWP 0
#define HALF_AWP_L 1
#define HALF_AWP_R 2
#define ROLLER 3
#define SKILLS 4

// Control modes
#define TNK_STD 0
#define OSA_STD 1
#define TSA_STD 2
#define TNK_REV 3
#define OSA_REV 4
#define TSA_REV 5
#define XDRIVE 6

// Drive
#define SLOW 0.5
#define FAST 1.0

#define POS_DRIVE_R drive_r.position(ROT_REV)
#define POS_DRIVE_L drive_l.position(ROT_REV)

// Flywheel speeds
#define IDLE 1000
#define LOW 1800
#define HIGH 3050

// Brain
#define X 0
#define Y 1
#define LEFT 1
#define UP 1
#define RIGHT 2
#define DOWN 2

// Misc - defines
#define GYRO_CORRECTION (7218.70 / 7200.0)
#define CHAR_HI 20
#define CHAR_WI 12
#define VEL_FLY_HI rot_flywheel_hi.velocity(VEL_RPM)
#define VEL_FLY_LO rot_flywheel_lo.velocity(VEL_RPM)
#define DRIVE_VEL ((drive_r.velocity(VEL_RPM) + drive_l.velocity(VEL_RPM)) / 2)
#define DRIVE_POS ((drive_r.position(ROT_REV) * DRIVE_REV__IN + drive_l.position(ROT_REV) * DRIVE_REV__IN) / 2)
#define DEADBAND 5
#define TIME sands_of_time.time(vex::msec);

// Control
#define SENSITIVITY 0.7

// Autonomous
extern int auton_mode;
extern float current_heading;
extern float fly_rpm;
extern bool fly_pid_enabled;

// Selection
extern const char *control_types[6];
extern const char *auton_types[4];
