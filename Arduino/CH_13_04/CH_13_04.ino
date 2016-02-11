#include <Mouse.h>

int buttonPin = 4;        // 버튼 입력 핀

void setup() {
  pinMode(buttonPin, INPUT);      // 버튼 입력 핀을 입력으로 설정
  Mouse.begin();          // 마우스 초기화
}

void loop() {
  int buttonState = digitalRead(buttonPin);   // 버튼 상태 읽기
  if (buttonState == HIGH) {      // 버튼이 눌러진 경우
    Mouse.click(2);       // 마우스 오른쪽 버튼 클릭
    delay(1000);
  }
}
