#include "main.h"
#include "stddefs.h"
#include "vex_global.h"

void tune_pid() {
    const float TUNER = 0.025;
    PID rd = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID ld = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
    PID dir = PID(DIR_KP, DIR_KI, DIR_KD);
    while (true) {
        opdrive(TSA_STD, 1, SENSITIVITY);
        if (BTN_Y.PRESSED) {
            target_heading = ROTATION * GYRO_CORRECTION;
            while (!BTN_Y.PRESSED) {
                drive_r.spin(DIR_FWD, 250 + rd.pid_adjust(250, drive_r.velocity(VEL_RPM)) - dir.pid_adjust(target_heading, ROTATION * GYRO_CORRECTION), VEL_RPM);
                drive_l.spin(DIR_FWD, 250 + ld.pid_adjust(250, drive_l.velocity(VEL_RPM)) + dir.pid_adjust(target_heading, ROTATION * GYRO_CORRECTION), VEL_RPM);
                printf("\ngyro: %.1lf", ROTATION);
                printf("\ncorrection: %.1lf", ROTATION * GYRO_CORRECTION);
                printf("\npid_bit: %.1lf", dir.pid_adjust(target_heading, ROTATION * GYRO_CORRECTION));
                wait(20, vex::msec);
            }
        }
        dir.tune_kP(TUNER);
        dir.tune_kI(TUNER);
        dir.tune_kD(TUNER);

        wait(20, vex::msec);
    }
}
