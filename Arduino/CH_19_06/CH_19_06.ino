#include <Wire.h>
#define SLAVE 4

int count = 0;    // 카운터

void setup() {
  // Wire 라이브러리 초기화
  // 슬레이브로 참여하기 위해서는 주소를 지정해야 한다.
  Wire.begin(SLAVE);

  // 마스터의 데이터 전송 요구가 있을 때 처리할 함수 등록
  Wire.onRequest(sendToMaster);
}

void loop () {
  count++;            // 초 단위 카운터
  delay(1000);
}

void sendToMaster() {
  Wire.write( (uint8_t *)(&count), 2 ); // 2바이트 크기의 카운터 값 전송
}
