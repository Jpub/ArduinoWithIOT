#include <SoftwareSerial.h>

SoftwareSerial gps(2, 3);      // GPS 리시버 연결
String sentence = "";     // 문장 저장을 위한 버퍼
boolean process_sentence = false;

void setup() {
  Serial.begin(9600);
  gps.begin(9600);
}

void loop() {
  if(gps.available()){
    char data = gps.read();
    switch(data){
    case '\n':
      break;
    case '\r':
      process_sentence = true;    // 문장의 끝
      break;
    default:
      sentence = sentence + data;
      break;
    }
  }

  if(process_sentence){     // 문장이 끝난 경우
    process_sentence = false;
    if(sentence.startsWith("$GPGGA")) // GGA 문장 여부 판단
      Serial.println(sentence);
    sentence = "";
  }
}
