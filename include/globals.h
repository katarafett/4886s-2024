// Physical bits
#define DRIVE_GEARING (GEAR_36 / GEAR_48)
#define DRIVE_REV_TO_IN (DRIVE_GEARING * PI * MED_WHEEL_DIAM)
#define WHEEL_TO_WHEEL_DIST (10.75)

#define DRIVE_KP 0.005
#define DRIVE_KI 0.00
#define DRIVE_KD 1.9

#define DIR_KP 2.925
#define DIR_KI 0.00
#define DIR_KD 0.183

#define TURN_KP_L 0.1
#define TURN_KI_L 0.0
#define TURN_KD_L 0.1

#define TURN_KP_R 0.1
#define TURN_KI_R 0.0
#define TURN_KD_R 0.1

// Autonmous modes
#define AWP 0
#define HALF_AWP_NEAR 1
#define HALF_AWP_FAR 2
#define NEAR_ELIMS 3
#define FAR_ELIMS 4
#define SKILLS 5
#define SKILLS_DRIVER 6

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
#define IMU_CORRECTION (3600 / 3593.6)
#define CHAR_HI 20
#define CHAR_WI 12
#define DRIVE_VEL ((drive_r.velocity(VEL_RPM) + drive_l.velocity(VEL_RPM)) / 2)
#define DRIVE_POS ((drive_r.position(ROT_REV) * DRIVE_REV__IN + drive_l.position(ROT_REV) * DRIVE_REV__IN) / 2)
#define DEADBAND 5
#define TIME sands_of_time.time(vex::msec)

// Control
#define SENSITIVITY 0.85

// Autonomous
extern int auton_mode;
extern float target_heading;

// Selection
extern const char *control_types[6];
extern const char *auton_types[4];

extern float turn_kp_l;
extern float turn_ki_l;
extern float turn_kd_l;

extern float turn_kp_r;
extern float turn_ki_r;
extern float turn_kd_r;

extern float move_kp, move_ki, move_kd;
