#include <Wire.h>
#define SLAVE 4

void setup() {
  Wire.begin(SLAVE);  // 슬레이브 모드로 Wire 라이브러리 초기화
  // 마스터로부터 데이터가 전송된 경우 처리할 함수 등록
  Wire.onReceive(receiveFromMaster);

  Serial.begin(9600);
}

void loop () {
}

void receiveFromMaster(int bytes) {
  for(int i = 0; i < bytes; i++){
    char ch = Wire.read();    // 수신 버퍼 읽기
    Serial.print(ch);
  }
}
