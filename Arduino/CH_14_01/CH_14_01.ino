#include <Keyboard.h>

int ON_OFF_BTN = 13;      // 마우스 & 키보드 on/off 버튼
int count = 0;

void setup(){
  pinMode(ON_OFF_BTN, INPUT);   // 버튼을 입력으로 설정
  Keyboard.begin();     // 키보드 에뮬레이션 시작
}

void loop(){
  // 마우스 & 키보드 기능이 켜진 경우에만 
  // 컴퓨터로 마우스나 키보드 이벤트를 전송한다.
  if(digitalRead(ON_OFF_BTN) == HIGH){
    Keyboard.println("Test String : " + String(count));
  }

  delay(1000);
  count++;
}
