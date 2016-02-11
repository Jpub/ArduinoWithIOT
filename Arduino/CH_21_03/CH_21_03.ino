#include <SoftwareSerial.h>

SoftwareSerial xbee(2, 3);      // (RX, TX)
String receiveBuffer = "";
boolean process_it = false;

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);     // Xbee 모듈 연결 초기화
}

void loop() {
  if(xbee.available()){
    byte data = xbee.read();

    if(data == '$')     // 종료 문자 수신
      process_it = true;
    else              // 버퍼에 저장
      receiveBuffer = receiveBuffer + (char)data;
  }

  if(process_it){       // 수신 데이터 처리
    process_it = false;
    if(receiveBuffer.length() == 2){    // 메시지 길이는 종료 문자 제외 2바이트
      Serial.print((int)(receiveBuffer.charAt(0))); // 송신 ID
      Serial.print(" : ");
      Serial.println(receiveBuffer.charAt(1));  // 송신 데이터
    }
    receiveBuffer = "";     // 버퍼 비움
  }
}
