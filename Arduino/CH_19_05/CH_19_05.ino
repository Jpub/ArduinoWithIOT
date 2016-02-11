#include <Wire.h>
#define SLAVE 4      // 슬레이브 주소

void setup() {
  Wire.begin();     // Wire 라이브러리 초기화
  Serial.begin(9600);   // 직렬 통신 초기화
}

void loop() {
  if(Serial.available()){
    char ch = Serial.read();
    if(ch == 'C'){
      i2c_communication();  // 슬레이브로 데이터 요구 및 수신 데이터 처리
    }
  }
}

void i2c_communication() {
  Wire.requestFrom(SLAVE, 2); // 2바이트 데이터 요청
  
  byte c1 = Wire.read();    // 수신 데이터 읽기
  byte c2 = Wire.read();

  Serial.println((int)( (c2 << 8) + c1 ));  // 수신 데이터 출력
}
