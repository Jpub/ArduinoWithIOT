#include <Wire.h>
#define SLAVE 4      // 슬레이브 주소

void setup() {
  Wire.begin();     // 마스터 모드로 Wire 라이브러리 초기화
}

void loop() {
  const char *p = "Hello, World\n";

  // I2C 통신을 통한 전송 시작
  Wire.beginTransmission(SLAVE);

  for(int i = 0; i < strlen(p); i++){   // 버퍼에 데이터 기록
    Wire.write(p[i]);
  }

  // I2C 통신을 통한 전송 끝
  Wire.endTransmission(SLAVE);

  delay(1000);
}
