#include <SoftwareSerial.h>

SoftwareSerial xbee(2, 3);      // (RX, TX)
unsigned long time_previous, time_current;
byte count = 0;       // 카운터

void setup() {
  xbee.begin(9600);     // Xbee 모듈 연결 초기화
  time_previous = millis();
}

void loop() {
  time_current = millis();
  if(time_current - time_previous > 1000){    // 1초 간격으로 카운터 값 증가
    time_previous = time_current;
    count++;
  }

  if(xbee.available()){
    byte data = xbee.read();
    if(data == 'C')       // 카운터 요청 문자를 수신한 경우
      xbee.write(count);      // 현재 카운터 값 전송
  }
}
