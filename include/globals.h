// Physical bits
#define DRIVE_GEARING (GEAR_36 / GEAR_48)
#define DRIVE_REV__IN (DRIVE_GEARING * PI * MED_WHEEL_DIAM)
#define WHEEL_TO_WHEEL_DIST (10.75)

#define DRIVE_KP 0.03
#define DRIVE_KI 0.00
#define DRIVE_KD 0.00
// #define DIR_KP 2.33
#define DIR_KP 2.6
#define DIR_KI 0.03
#define DIR_KD 0.03

#define DRIVE_INSERT TRB_INSERT
#define INTAKE_INSERT TRB_INSERT

// Autonmous modes
#define AWP 0
#define HALF_AWP_NEAR 1
#define HALF_AWP_FAR 2
#define NEAR_ELIMS 3
#define FAR_ELIMS 4
#define SKILLS 5

// Control modes
#define TNK_STD 0
#define OSA_STD 1
#define TSA_STD 2
#define TNK_REV 3
#define OSA_REV 4
#define TSA_REV 5
#define XDRIVE 6

// Drive
#define POS_DRIVE_R (drive_r.position(ROT_REV) * DRIVE_REV__IN)
#define POS_DRIVE_L (drive_l.position(ROT_REV) * DRIVE_REV__IN)
#define VEL_DRIVE_R (drive_r.velocity(VEL_RPM) * DRIVE_REV__IN / 60.0)
#define VEL_DRIVE_L (drive_l.velocity(VEL_RPM) * DRIVE_REV__IN / 60.0)

// Brain
#define X 0
#define Y 1
#define LEFT 1
#define UP 1
#define RIGHT 2
#define DOWN 2

// Misc - defines
#define GYRO_CORRECTION (3600.0 / 3596.7)
#define CHAR_HI 20
#define CHAR_WI 12
#define DRIVE_VEL ((drive_r.velocity(VEL_RPM) + drive_l.velocity(VEL_RPM)) / 2)
#define DRIVE_POS ((drive_r.position(ROT_REV) * DRIVE_REV__IN + drive_l.position(ROT_REV) * DRIVE_REV__IN) / 2)
#define DEADBAND 5
#define TIME sands_of_time.time(vex::msec)

// Control
#define SENSITIVITY 0.9

// Autonomous
extern int auton_mode;
extern float target_heading;

// Selection
extern const char *control_types[6];
extern const char *auton_types[4];
