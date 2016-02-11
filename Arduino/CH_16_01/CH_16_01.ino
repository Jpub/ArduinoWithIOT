#include <SoftwareSerial.h>

SoftwareSerial xbee(2, 3);      // (RX, TX)
byte count = 0;
unsigned long time_previous, time_current;

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);     // Xbee 모듈 연결 초기화
  time_previous = millis();
}

void loop() {
  time_current = millis();
  if(time_current - time_previous > 1000){    // 1초에 한 번 실행
    time_previous = time_current;
    count++;          // 카운터 증가
    xbee.println(count);      // 데이터 전송
  }

  if(xbee.available()){     // 수신 데이터를 시리얼 모니터로 출력
    Serial.write(xbee.read());
  }
}
