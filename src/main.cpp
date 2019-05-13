#include <Arduino.h>

void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
}

void calc_PID(long *q_ref, long *q_m, long *tau_arr, long *PID_arr) {
  long q_konjm[4], q_err[3][3], v[9];

  q_konjm[0]=q_m[0];
  q_konjm[1]=-q_m[1];
  q_konjm[2]=-q_m[2];
  q_konjm[3]=-q_m[3];

  for (int a=1; a<4; a++) {
    q_err[0][a] = q_ref[1] * q_konjm[a];
    q_err[1][a] = q_ref[2] * q_konjm[a];
    q_err[2][a] = q_ref[3] * q_konjm[a];
  }

  //calculate vector v:
  v[0] = q_m[0]*q_m[0] + q_m[1]*q_m[1] - q_m[2]*q_m[2] - q_m[3]*q_m[3];
  v[1] = 2 * (q_m[1]*q_m[2] + q_m[0]*q_m[3]);
  v[2] = 2 * (q_m[1]*q_m[3] - q_m[0]*q_m[2]);
  v[3] = 2 * (q_m[1]*q_m[2] - q_m[0]*q_m[3]);
  v[4] = q_m[0]*q_m[0] - q_m[1]*q_m[1] + q_m[2]*q_m[2] - q_m[3]*q_m[3];
  v[5] = 2 * (q_m[2]*q_m[3] + q_m[0]*q_m[1]);
  v[6] = 2 * (q_m[1]*q_m[3] + q_m[0]*q_m[2]);
  v[7] = 2 * (q_m[2]*q_m[3] - q_m[0]*q_m[1]);
  v[8] = q_m[0]*q_m[0] - q_m[1]*q_m[1] - q_m[2]*q_m[2] + q_m[3]*q_m[3];
}

void loop() {
  long q_ref_arr[4], q_m_arr[4], tau_arr[3], PID_arr[3];

  calc_PID(q_ref_arr, q_m_arr, tau_arr, PID_arr);
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
