#include <SoftwareSerial.h>

// 2 : 시리얼 텍스트 LCD의 TX (사용되지 않음)
// 3 : 시리얼 텍스트 LCD의 RX
SoftwareSerial serialLCD = SoftwareSerial(2, 3);
int count = 0;

void setup(){
  serialLCD.begin(9600);      // 소프트웨어 시리얼 초기화
}

void loop(){
  serialLCD.print(count++);   // 카운트 증가 및 출력
  serialLCD.print(" ");
  delay(1000);
}
