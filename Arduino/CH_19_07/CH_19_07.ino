#include <Wire.h>
#define SLAVE1 4      // 슬레이브 주소
#define SLAVE2 5      // 슬레이브 주소

char sendBuffer[20];      // 전송 문자열 저장 버퍼
int count;            // 현재 카운터

void setup() {
  Wire.begin();       // 마스터 모드로 Wire 라이브러리 초기화
  count = 0;          // 카운터 초기화
}

void loop() {
  count++;
  String(count).toCharArray(sendBuffer, 20);  // 카운터 값을 문자열로 변환

  if(count % 2){
    Wire.beginTransmission(SLAVE1);   // 전송 준비
    for(int i = 0; i < strlen(sendBuffer); i++) // 버퍼에 데이터 기록
      Wire.write(sendBuffer[i]);
    Wire.write('\n');
    Wire.endTransmission(SLAVE1);   // 전송
  }
  else{
    Wire.beginTransmission(SLAVE2);
    for(int i = 0; i < strlen(sendBuffer); i++)
      Wire.write(sendBuffer[i]);
    Wire.write('\n');
    Wire.endTransmission(SLAVE2);
  }

  delay(1000);
}
