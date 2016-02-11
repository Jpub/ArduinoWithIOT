#include <Keyboard.h>

int ON_OFF_BTN = 13;      // 마우스 & 키보드 on/off 버튼
int CTRL_C = 2;       // 복사하기 버튼
int CTRL_V = 3;       // 붙여넣기 버튼

void setup(){
  pinMode(ON_OFF_BTN, INPUT);   // 버튼을 입력으로 설정
  pinMode(CTRL_C, INPUT);
  pinMode(CTRL_V, INPUT);

  Keyboard.begin();     // 키보드 에뮬레이션 시작

  Serial.begin(9600);     // 시리얼 모니터 초기화
  while(!Serial);
}

void loop(){
  // 마우스 & 키보드 기능이 켜진 경우에만 
  // 컴퓨터로 마우스나 키보드 이벤트를 전송한다.
  if(digitalRead(ON_OFF_BTN) == HIGH){
    if(digitalRead(CTRL_C)){
      Keyboard.press(KEY_LEFT_CTRL);  // 컨트롤 키 누름
      Keyboard.press('c');    // ‘c’ 키 누름
      Keyboard.releaseAll();    // 두 개의 키 뗌
      Serial.println("Ctrl + C");
        delay(500);
    }
    else if(digitalRead(CTRL_V)){
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('v');
      Keyboard.releaseAll();
      Serial.println("Ctrl + V");
      delay(500);
    }
  }
}
