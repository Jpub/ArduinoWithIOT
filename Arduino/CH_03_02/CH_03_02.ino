#include <SoftwareSerial.h>

// 2 : 시리얼 텍스트 LCD의 TX (사용되지 않음)
// 3 : 시리얼 텍스트 LCD의 RX
SoftwareSerial serialLCD = SoftwareSerial(2, 3);
int count = 0;

void setup(){
  serialLCD.begin(9600);      // 소프트웨어 시리얼 초기화
  serialLCD.print("$$B0\r");    // 커서 끔
}

void loop(){
  serialLCD.print("$$CS\r");    // 화면 지우기 명령
  serialLCD.print('\r');      // 줄바꿈
  serialLCD.print("Current Count : ");
    serialLCD.print(count++);   // 카운트 증가 및 출력
  delay(1000);
}
