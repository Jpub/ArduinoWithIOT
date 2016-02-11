#include <IRremote.h>

IRsend irsend;
int button_pin = 4;

void setup()
{
  Serial.begin(115200);       // 시리얼 통신 초기화
  pinMode(button_pin, INPUT_PULLUP);  // 내부 풀업 저항을 사용한 버튼 연결
}

void loop() 
{
  if(!digitalRead(button_pin)){   // 버튼이 눌러진 경우
    Serial.println("** Data Sending...");
    // NEC 방식의 4바이트 데이터 전송
    // 매개변수는 전송되는 데이터의 비트 수를 지정
    irsend.sendNEC(0x18E758A7, 32);
    delay(200);
  }
}
