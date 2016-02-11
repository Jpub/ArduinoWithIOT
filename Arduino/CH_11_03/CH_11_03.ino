#include <Stepper.h>

const int stepsPerRevolution = 200;  // 1바퀴 회전을 위해 필요한 스텝 수

// 아두이노의 디지털 9, 8, 7, 6번 핀은
// 스텝 모터 제어 모듈의 A, /A, B, /B 핀으로 연결
Stepper myStepper(stepsPerRevolution, 9, 8, 7, 6);

void setup() {
  myStepper.setSpeed(60);   // 분당 60회전, 초당 1회전
}

void loop() {
  // 양수인 경우 정방향 회전
  // 200 스텝 진행 → 1회전에 해당
  myStepper.step(stepsPerRevolution);
  delay(500);         // 0.5초 대기

  myStepper.step(-stepsPerRevolution);  // 음수인 경우 역방향 회전
  delay(500);
}
