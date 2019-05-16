#include <Arduino.h>

#define PQ 5
#define PW 5

void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
}

void calc_PID(long *q_ref, long *q_m, long *tau_arr, long *ang_velo) {

  //calculate the error quaternion:
  long q_err[3] = {q_ref[0]*(-q_m[1]) + q_ref[1]*q_m[0] + q_ref[2]*(-q_m[3]) - q_ref[3]*(-q_m[2]),
                   q_ref[0]*(-q_m[2]) - q_ref[1]*(-q_m[3]) + q_ref[2]*q_m[0] + q_ref[3]*(-q_m[1]),
                   q_ref[0]*(-q_m[3]) + q_ref[1]*(-q_m[2]) - q_ref[2]*(-q_m[1]) + q_ref[3]*q_m[0]};

  //outer loop proportional controller for angular velocity reference tracking:
  tau_arr[0] = - (PQ * q_err[0]);
  tau_arr[1] = - (PQ * q_err[1]);
  tau_arr[2] = - (PQ * q_err[2]);

  //inner loop proportional controller for angular velocity:
  tau_arr[0] -= PW * ang_velo[0];
  tau_arr[1] -= PW * ang_velo[1];
  tau_arr[2] -= PW * ang_velo[2];

  /*calculate Rotation Matrix:
  R[0][0] = q_m[0]*q_m[0] + q_m[1]*q_m[1] - q_m[2]*q_m[2] - q_m[3]*q_m[3];
  R[1][0] = 2 * (q_m[1]*q_m[2] + q_m[0]*q_m[3]);
  R[2][0] = 2 * (q_m[1]*q_m[3] - q_m[0]*q_m[2]);
  R[0][1] = 2 * (q_m[1]*q_m[2] - q_m[0]*q_m[3]);
  R[1][1] = q_m[0]*q_m[0] - q_m[1]*q_m[1] + q_m[2]*q_m[2] - q_m[3]*q_m[3];
  R[2][1] = 2 * (q_m[2]*q_m[3] + q_m[0]*q_m[1]);
  R[0][2] = 2 * (q_m[1]*q_m[3] + q_m[0]*q_m[2]);
  R[1][2] = 2 * (q_m[2]*q_m[3] - q_m[0]*q_m[1]);
  R[2][2] = q_m[0]*q_m[0] - q_m[1]*q_m[1] - q_m[2]*q_m[2] + q_m[3]*q_m[3];*/
}


void loop() {
  long q_ref_arr[4], q_m_arr[4], tau_arr[3], ang_velo[3];

  calc_PID(q_ref_arr, q_m_arr, tau_arr, ang_velo);
}

void Loop_Motors() {
  for (int i=50; i<256; i++) {
    analogWrite(9, i);
    analogWrite(10, i);
    analogWrite(11, i);
    analogWrite(6, i);
    delay(10);
  }
  for (int j=255; j>=50; j--) {
    analogWrite(9, j);
    analogWrite(10, j);
    analogWrite(11, j);
    analogWrite(6, j);
    delay(10);
  }
}
