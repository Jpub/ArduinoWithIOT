#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);    // 슬레이브 데이터 입력 포트

void setup() {
  Serial.begin(9600);     // 컴퓨터 연결 포트
  mySerial.begin(9600);
}

void loop() {
  while(mySerial.available()){    // 슬레이브로 부터의 데이터 수신 확인
    char data = mySerial.read();    // 슬레이브 데이터 읽기
    Serial.print(data);     // 컴퓨터로 재전송
  }
}
