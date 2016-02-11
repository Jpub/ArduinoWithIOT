#include <SoftwareSerial.h>

#define DATA_START   'a'   // 전송 데이터 범위 시작
#define DATA_END  'z'   // 전송 데이터 범위 끝
#define NODE_ID   1   // 노드 ID

SoftwareSerial xbee(2, 3);      // (RX, TX)
unsigned long time_previous, time_current;
char sendData = DATA_START;

void setup() {
  xbee.begin(9600);     // Xbee 모듈 연결 초기화
  time_previous = millis();
}

void loop() {
  time_current = millis();
  if(time_current - time_previous > 1000){
    time_previous = time_current;
    xbee.write(NODE_ID);      // 노드 ID
    xbee.write(sendData);     // 전송 데이터
    xbee.write('$');      // 종료 문자

    sendData++;
    if(sendData > DATA_END) 
      sendData = DATA_START;
  }
}
