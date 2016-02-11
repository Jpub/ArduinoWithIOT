#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX) 형식으로 블루투스 모듈과 교차하여 연결
SoftwareSerial BTSerial(2, 3);

int switch1 = 9;        // 스위치 연결 핀
int switch2 = 10;

void setup()  
{
  BTSerial.begin(9600);     // 블루투스 연결 초기화

  pinMode(switch1, INPUT_PULLUP); // 내부 풀업 저항을 사용하는 버튼 설정
  pinMode(switch2, INPUT_PULLUP);
}

void loop()
{
  if(digitalRead(switch1) == 0){    // 1번 버튼이 눌러지면 ‘A’ 전송
    BTSerial.write('A');
    delay(200);
  }

  if(digitalRead(switch2) == 0){    // 2번 버튼이 눌러지면 ‘B’ 전송
    BTSerial.write('B');
    delay(200);
  }
}
