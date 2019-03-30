#include <Arduino.h>

struct quat { long quat[4]; };

void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
}

void calc_PID(struct quat q_m) {
  long q_ref[4], q_konjm[4], q_err[3][3], tau[3];
  for (int a=1; a<4; a++) {
    q_err[0][a] = q_ref[1] * q_konjm[a];
    q_err[1][a] = q_ref[2] * q_konjm[a];
    q_err[2][a] = q_ref[3] * q_konjm[a];
  }
}

void loop() {
  struct quat new_quat;

  calc_PID(new_quat);
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
