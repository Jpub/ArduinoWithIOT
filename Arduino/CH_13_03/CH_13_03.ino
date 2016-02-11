#include <Keyboard.h>

int buttonPin = 4;        // 버튼 입력 핀
int previousButtonState = LOW;      // 버튼의 상태
int counter = 0;          // 버튼을 누른 횟수

void setup() {
  pinMode(buttonPin, INPUT);      // 버튼 입력 핀을 입력으로 설정
  Keyboard.begin();       // 키보드 초기화
}

void loop() {
  int buttonState = digitalRead(buttonPin);   // 버튼 상태 읽기
  // 이전 버튼 상태와 다르고 현재 버튼이 눌러진 경우
  if ((buttonState != previousButtonState) && (buttonState == HIGH)) {
    counter++;          // 버튼 누른 횟수 증가
    Keyboard.print("You pressed the button ");  // 메시지 출력
    Keyboard.print(counter); 
    Keyboard.println(" times.");
  }
  previousButtonState = buttonState;    // 현재 상태 저장
  delay(100); 
}
