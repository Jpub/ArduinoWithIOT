#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);    // 슬레이브 통신 포트

void setup() {
  Serial.begin(9600);     // 컴퓨터 연결 포트
  mySerial.begin(9600);
}

void loop() {
  // 시리얼 모니터 --> 마스터 --> 슬레이브
  if(Serial.available())
    mySerial.write(Serial.read());

  // 슬레이브 --> 마스터 --> 시리얼 모니터
  if(mySerial.available())
    Serial.write(mySerial.read());
}
