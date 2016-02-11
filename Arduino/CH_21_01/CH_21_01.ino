#include <SoftwareSerial.h>

SoftwareSerial xbee(2, 3);      // (RX, TX)
unsigned long time_previous, time_current;

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);     // Xbee 모듈 연결 초기화
  time_previous = millis();
}

void loop() {
  time_current = millis();
  // 2초 간격으로 노드 2로 현재 카운터 값 요청
  if(time_current - time_previous > 2000){
    time_previous = time_current;
    xbee.write('C');      // 카운터 값 요청 문자 ‘C’
  }

  if(xbee.available()){
    Serial.println(xbee.read());    // 수신 데이터 출력
  }
}
