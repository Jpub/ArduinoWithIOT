#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX) 형식으로 블루투스 모듈과 교차하여 연결된다.
SoftwareSerial BTSerial(2, 3);
int pin = A0;        // 가변저항 연결 핀
int value_previous, value_current;

void setup(){
  Serial.begin(9600);     // 시리얼 모니터 초기화
  BTSerial.begin(9600);     // 블루투스 모듈 초기화

  value_previous = analogRead(pin); // 초기값
  sendData(value_previous);
}

void sendData(int value){     // 블루투스 모듈을 통해 데이터 전송
  String message = String(value) + '\n';
  BTSerial.print(message);
}

void loop(){
  value_current = analogRead(pin);  // 가변저항 값 읽기

  if(value_current != value_previous){  // 가변저항 값이 바뀐 경우에만 전송
    value_previous = value_current;

    Serial.print("Current read is ");
    Serial.print(value_current);    // 디지털 값
    Serial.print(", approximately ");
    Serial.print(value_current * 5 / 1023.0); // 아날로그 전압 값
    Serial.println(" V.");

    sendData(value_current);    // 블루투스 모듈을 통해 데이터 전송
  }
  delay(1000);
}
