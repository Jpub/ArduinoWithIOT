#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX) 형식으로 블루투스 모듈과 교차하여 연결
SoftwareSerial BTSerial(2, 3);
char buffer[100];      // 수신 문자열 버퍼

void setup()  
{
  Serial.begin(9600);   // 시리얼 통신 초기화
  BTSerial.begin(9600);   // 블루투스 모듈 초기화
}

void loop()
{
  if(BTSerial.available()){   // 슬레이브로부터 데이터 수신
    int bytes = BTSerial.readBytes(buffer, 99);
    buffer[bytes] = 0;
    Serial.print("Slave Echo : ");
    Serial.println(buffer);
  }

  if(Serial.available()){   // 시리얼 모니터의 데이터 입력
    int bytes = Serial.readBytes(buffer, 99);
    buffer[bytes] = 0;
    Serial.println(buffer);
    BTSerial.write(buffer);
  }
}
