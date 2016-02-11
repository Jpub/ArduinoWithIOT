#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3);  // SoftwareSerial(RX, TX)

byte buffer[1024];    // 데이터 수신 버퍼
int bufferPosition;   // 버퍼에 기록할 위치

void setup()  
{
  BTSerial.begin(9600);   // 블루투스 모듈 초기화
  Serial.begin(9600);   // 시리얼 모니터 초기화
  bufferPosition = 0;
}

void loop()
{
  if (BTSerial.available()){      // 블루투스로 데이터 수신
    byte data = BTSerial.read();
    Serial.write(data);       // 수신된 데이터 시리얼 모니터로 출력
    buffer[bufferPosition++] = data;
    if(data == '\n'){     // 문자열 종료 표시
      buffer[bufferPosition] = '\0';

      // 스마트폰으로 전송할 문자열을 시리얼 모니터에 출력
      Serial.print("Echo Back : "); 
      Serial.write(buffer, bufferPosition);
      
      // 스마트폰으로 문자열 전송
      BTSerial.write(buffer, bufferPosition);

      bufferPosition = 0;
    }
  }
}
