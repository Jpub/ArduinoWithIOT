#include <Keyboard.h>
#include <Mouse.h>

int ON_OFF_BTN = 13;      // 마우스 & 키보드 on/off 버튼

int BUTTON_LEFT = 2;      // 왼쪽 키보드
int BUTTON_RIGHT = 3;     // 오른쪽 키보드
int BUTTON_UP = 4;      // 위쪽 키보드
int BUTTON_DOWN = 5;      // 아래쪽 키보드
int MOUSE_LEFT_BTN = 6;   // 왼쪽 마우스
int MOUSE_RIGHT_BTN = 7;    // 오른쪽 마우스

void setup(){
  Keyboard.begin();     // 키보드 에뮬레이션 시작
  Mouse.begin();        // 마우스 에뮬레이션 시작

  pinMode(ON_OFF_BTN, INPUT);   // 버튼을 입력으로 설정
  pinMode(BUTTON_LEFT, INPUT);
  pinMode(BUTTON_RIGHT, INPUT);
  pinMode(BUTTON_UP, INPUT);
  pinMode(BUTTON_DOWN, INPUT);
  pinMode(MOUSE_LEFT, INPUT);
  pinMode(MOUSE_RIGHT, INPUT);

  Serial.begin(9600);     // 시리얼 포트 초기화
}

void loop(){
  // 마우스 & 키보드 기능이 켜진 경우에만 
  // 컴퓨터로 마우스나 키보드 이벤트를 전송한다.
  if(digitalRead(ON_OFF_BTN) == HIGH){
    // 키보드 입력 전달
    if(digitalRead(BUTTON_LEFT) == HIGH){
      Keyboard.write(KEY_LEFT_ARROW);
      Serial.println("Left Key");
    }
    if(digitalRead(BUTTON_RIGHT) == HIGH){
      Keyboard.write(KEY_RIGHT_ARROW);
      Serial.println("Right Key");
    }
    if(digitalRead(BUTTON_UP) == HIGH){
      Keyboard.write(KEY_UP_ARROW);
      Serial.println("Up  Key");
    }
    if(digitalRead(BUTTON_DOWN) == HIGH){
      Keyboard.write(KEY_DOWN_ARROW);
      Serial.println("Down Key");
    }

    // 마우스 입력 전달
    if(digitalRead(MOUSE_LEFT_BTN) == HIGH){
      Mouse.click(MOUSE_LEFT);
      Serial.println("Left Button");
    }
    if(digitalRead(MOUSE_RIGHT_BTN) == HIGH){
      Mouse.click(MOUSE_RIGHT);
      Serial.println("Right Button");
    }

    delay(100);
  }
}
