#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX) 형식으로 블루투스 모듈과 교차하여 연결
SoftwareSerial BTSerial(2, 3);
char buffer[100];      // 수신 문자열 버퍼

void setup()
{
  BTSerial.begin(9600);   // 블루투스 모듈 통신 속도의 디폴트값
}

void loop()
{
  if(BTSerial.available()){   // 마스터로부터의 데이터 수신
    int no = BTSerial.readBytes(buffer, 99);
    BTSerial.write(buffer, no); // 마스터로 재전송
  }
}
