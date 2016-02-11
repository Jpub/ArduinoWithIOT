#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX) 형식으로 블루투스 모듈과 교차하여 연결된다.
SoftwareSerial BTSerial(2, 3);

void setup()  
{
  Serial.begin(9600);   // 컴퓨터와의 시리얼 통신 초기화
  BTSerial.begin(9600);   // 블루투스 모듈 초기화
}

void loop()
{
  if(BTSerial.available()){
    Serial.write(BTSerial.read());
  }
}
