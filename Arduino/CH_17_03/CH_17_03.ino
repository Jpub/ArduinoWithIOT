#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);    // 마스터 연결 시리얼 포트

int count = 0;        // 카운터

void setup() {
  mySerial.begin(9600);     // UART 시리얼 포트 초기화
}

void loop() {
  count = count + 1;
  mySerial.println(count);      // 카운터 값 전송

  delay(1000);        // 1초 대기
}
