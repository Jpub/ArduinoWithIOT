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
      print_info();
  }
}

void print_info(void) {
  int pos[6] = {0, };       // 콤마의 위치
  int start = 0;        // 검색 시작 위치

  Serial.println(sentence);

  for(int i = 0; i < 6; i++){   // 콤마 위치 검색
    pos[i] = sentence.indexOf(',', start + 1);
    start = pos[i];
  }

  // 콤마 사이의 부분 문자열 추출 및 출력
  Serial.print("Time      : ");
  Serial.println(sentence.substring(pos[0] + 1, pos[1]));
  Serial.print("Latitude  : ");
  Serial.print(sentence.substring(pos[1] + 1, pos[2]));
  Serial.println(sentence.substring(pos[2] + 1, pos[3]));
  Serial.print("Longitude : ");
  Serial.print(sentence.substring(pos[3] + 1, pos[4]));
  Serial.println(sentence.substring(pos[4] + 1, pos[5]));
}
