#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX) 형식으로 블루투스 모듈과 교차하여 연결
SoftwareSerial BTSerial(2, 3);

void setup()  
{
  Serial.begin(9600);   // 컴퓨터와의 시리얼 통신 초기화
  BTSerial.begin(9600);   // 블루투스 모듈 초기화
}

void loop()
{
  // 블루투스 모듈 → 아두이노 → 시리얼 모니터
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  // 시리얼 모니터 → 아두이노 → 블루투스 모듈
  if (Serial.available())
    BTSerial.write(Serial.read());
}
