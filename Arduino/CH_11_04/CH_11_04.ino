#include <Stepper.h>

int pin_CLK = 2;        // Clock 출력 핀
int pin_DIR = 3;        // Direction 제어 핀

boolean state = false;      // 클록 상태

void setup() {
  pinMode(pin_CLK, OUTPUT);
  pinMode(pin_DIR, OUTPUT);

  digitalWrite(pin_CLK, LOW);   // 클록은 LOW 상태에서 시작
  digitalWrite(pin_DIR, HIGH);    // 정방향 회전
}

void loop() {
  // 2.5ms 마다 클록 상태를 반전시켜 출력
  // 즉, 5ms 마다 클록을 출력하여 초당 200개 펄스를 출력
  digitalWrite(pin_CLK, state);
  delayMicroseconds(2500);
  state = !state;
}
