// #include "main.h"
// #include "stddefs.h"
// #include "vex_global.h"

// void tune_pid() {
//     // PID rd = PID(drive_kp)
// }

// // void tune_pid() {
// //     const float TUNER = 0.025;
// //     PID rd = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
// //     PID ld = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
// //     PID dir = PID(DIR_KP, DIR_KI, DIR_KD);
// //     while (true) {
// //         opdrive(TSA, 1, SENSITIVITY);
// //         if (BTN_Y.PRESSED) {
// //             target_heading = imu_rotation();
// //             while (!BTN_Y.PRESSED) {
// //                 drive_r.spin(DIR_FWD, 400 + rd.adjust(400, drive_r.velocity(VEL_RPM)) - dir.adjust(target_heading, imu_rotation()), VEL_RPM);
// //                 drive_l.spin(DIR_FWD, 400 + ld.adjust(400, drive_l.velocity(VEL_RPM)) + dir.adjust(target_heading, imu_rotation()), VEL_RPM);
// //                 wait(20, vex::msec);
// //             }
// //         }
// //         dir.tune_kP(TUNER);
// //         dir.tune_kI(TUNER);
// //         dir.tune_kD(TUNER);
// //
// //         wait(20, vex::msec);
// //     }
// // }

// void tune_drive_pid() {
//     const float TUNER = 0.025;
//     PID rd = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
//     PID ld = PID(DRIVE_KP, DRIVE_KI, DRIVE_KD);
//     PID dir = PID(DIR_KP, DIR_KI, DIR_KD);
//     while (true) {
//         opdrive(TSA, 1, SENSITIVITY);
//         if (BTN_Y.PRESSED) {
//             target_heading = imu_rotation();
//             while (!BTN_Y.PRESSED) {
//                 drive_r.spin(DIR_FWD, 250 + rd.adjust(250, drive_r.velocity(VEL_RPM)) - dir.adjust(target_heading, imu_rotation()), VEL_RPM);
//                 drive_l.spin(DIR_FWD, 250 + ld.adjust(250, drive_l.velocity(VEL_RPM)) + dir.adjust(target_heading, imu_rotation()), VEL_RPM);
//                 wait(20, vex::msec);
//             }
//         }
//         ld.tune_kP(TUNER);
//         ld.tune_kI(TUNER);
//         ld.tune_kD(TUNER);
//         rd.tune_kP(TUNER);
//         rd.tune_kI(TUNER);
//         rd.tune_kD(TUNER);

//         wait(20, vex::msec);
//     }
// }

// void tune_simple_pid() {
//     const float TUNER = 0.025;
//     PID drive = PID(move_kp, move_ki, move_kd);
//     while (true) {
//         opdrive(TSA, 1, SENSITIVITY);
//         if (BTN_R1.PRESSED) {
//             target_heading = imu_rotation();
//             straight_pid(30);
//         }
//         if (BTN_R2.PRESSED) {
//             target_heading = imu_rotation();
//             straight_pid(60);
//         }
//         if (BTN_L1.PRESSED) {
//             target_heading = imu_rotation();
//             straight_pid(12);
//         }
//         if (BTN_L2.PRESSED) {
//             target_heading = imu_rotation();
//             straight_pid(90);
//         }
//         drive.tune_kP(TUNER);
//         drive.tune_kI(TUNER);
//         drive.tune_kD(TUNER);

//         move_kp = drive.get_const('p');
//         move_ki = drive.get_const('i');
//         move_kd = drive.get_const('d');

//         wait(20, vex::msec);
//     }
// }
