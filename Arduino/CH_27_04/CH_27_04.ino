#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX) 형식으로 블루투스 모듈과 교차하여 연결된다.
SoftwareSerial BTSerial(2, 3);

int button_pins[] = {4, 5, 6, 7, 8, 9, 10, 11};  // 버튼 연결 핀
boolean button_state[8];      // 버튼의 이전 상태

void setup(){
  for(int i = 0; i < 8; i++){   // 버튼 연결 핀을 입력으로 설정
    pinMode(button_pins[i], INPUT);
    button_state[i] = false;    // 눌러지지 않은 상태로 시작
  }
  Serial.begin(9600);     // 시리얼 모니터 초기화
  BTSerial.begin(9600);     // 블루투스 모듈 초기화
}

void loop(){
  for(int i = 0; i < 8; i++){
    boolean current_state = digitalRead(button_pins[i]);
    if(button_state[i] != current_state){ // 상태가 변한 경우
      button_state[i] = current_state;  // 상태 업데이트

      Serial.print(String("Button ") + (i + 1) + " is ");
      if(current_state) Serial.println("ON !!");
      else Serial.println("OFF !");

      char message[4] = "  \n";
      message[0] = i + 1 + '0';
      message[1] = current_state + '0';
      Serial.print(message);

      BTSerial.print(message);    // 블루투스로 데이터 전송

      delay(200);
    }
  }
}
