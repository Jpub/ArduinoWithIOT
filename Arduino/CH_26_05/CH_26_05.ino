#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX) 형식으로 블루투스 모듈과 교차하여 연결된다.
SoftwareSerial BTSerial(2, 3);
int LED_pins[] = {4, 5, 6, 7, 8, 9, 10, 11};  // LED 연결 핀
boolean LED_state[8];
String buffer = "";

void setup()  
{
  Serial.begin(9600);     // 컴퓨터와의 시리얼 통신 초기화
  BTSerial.begin(9600);     // 블루투스 모듈 초기화

  for(int i = 0; i < 8; i++){
    pinMode(LED_pins[i], OUTPUT); // LED 연결 핀을 출력으로 설정
    LED_state[i] = false;   // LED는 꺼진 상태로 시작
    digitalWrite(LED_pins[i], LED_state[i]);
  }
}

void loop()
{
  if(BTSerial.available()){   // 수신 데이터가 존재하는 경우
    byte data = BTSerial.read();    // 바이트 데이터 읽기
    if(data == '\n'){     // 개행문자 발견
      int index = buffer.toInt();   // 버퍼 내용을 정수로 변환
      if(index >= 1 && index <= 8){ // LED 번호인 경우 처리
        int arrayIndex = index - 1;
        LED_state[arrayIndex] = !LED_state[arrayIndex];
        digitalWrite(LED_pins[arrayIndex], LED_state[arrayIndex]);

        Serial.print(String("LED ") + index + " is turned ");
        if(LED_state[arrayIndex]) Serial.println("ON !!");
        else Serial.println("OFF !!");
      }
      buffer = "";      // 수신 버퍼 비움
    }
    else buffer += (char)data;  // 개행문자가 아닌 경우 수신 버퍼에 저장
  }
}
