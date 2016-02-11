#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX) 형식으로 블루투스 모듈과 교차하여 연결된다.
SoftwareSerial BTSerial(2, 3);
int LED_pins[] = {4, 5, 6, 7, 8, 9, 10, 11};  // LED 연결 핀
boolean LED_state[8];

void setup()  
{
  Serial.begin(9600);     // 컴퓨터와의 시리얼 통신 초기화
  BTSerial.begin(9600);     // 블루투스 모듈 초기화

  for(int i = 0; i < 8; i++){
    pinMode(LED_pins[i], OUTPUT); // LED 연결 핀을 출력으로 설정
    LED_state[i] = false;     // LED는 꺼진 상태로 시작
    digitalWrite(LED_pins[i], LED_state[i]);
  }
}

void loop()
{
  if(BTSerial.available()){     // 수신 데이터가 존재하는 경우
    byte data = BTSerial.read();    // 바이트 데이터 읽기
    if(data >= '1' && data <= '8'){ // ‘1’에서 ‘8’ 사이의 숫자인 경우
      int index = data - '0' - 1; // 배열은 0부터 시작하므로 ‘-1’이 필요
      LED_state[index] = !LED_state[index];   // 상태 반전
      digitalWrite(LED_pins[index], LED_state[index]);  // LED 제어

      Serial.print(String("LED ") + (index + 1) + " is turned ");
      if(LED_state[index]) Serial.println("ON !!");
      else Serial.println("OFF !!");
    }
  }
}
