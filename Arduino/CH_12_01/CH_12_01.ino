#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);    // DB9 연결, COM1, RealTerm

void setup(){
  Serial.begin(9600);     // USB 연결, COM6, 시리얼 모니터
  mySerial.begin(9600);     // DB9 연결, COM1, RealTerm
}

void loop(){
  if(Serial.available() > 0){
    mySerial.write(Serial.read());
  }

  if(mySerial.available() > 0){
    Serial.write(mySerial.read());
  }
}
