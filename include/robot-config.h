extern vex::brain Brain;
extern vex::controller master;

extern vex::motor drive_r1;
extern vex::motor drive_r2;
extern vex::motor drive_r3;
extern vex::motor drive_r4;
extern vex::motor drive_l1;
extern vex::motor drive_l2;
extern vex::motor drive_l3;
extern vex::motor drive_l4;

extern vex::motor intakeLow;
extern vex::motor intakeHigh;
extern vex::motor intakeMid;
extern vex::motor lift;

extern vex::digital_out mogo_clamp;
extern vex::digital_out Smith_Mech;
extern vex::digital_out intake_lift;
extern vex::digital_out PTO;

extern vex::inertial imu;
extern vex::optical colorSort;
extern vex::vision::signature red_ring;
extern vex::vision::signature blue_ring;
extern vex::vision::signature neutral_post;
extern vex::vision vision1;

extern vex::motor_group drive_r;
extern vex::motor_group drive_l;
extern vex::motor_group drive_full;
extern vex::motor_group intake;