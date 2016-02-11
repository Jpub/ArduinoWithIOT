#include <SoftwareSerial.h>

// 2 : 시리얼 텍스트 LCD의 TX (사용되지 않음)
// 3 : 시리얼 텍스트 LCD의 RX
SoftwareSerial serialLCD = SoftwareSerial(2, 3);
int count = 0;

void setup(){
  serialLCD.begin(9600);      // 소프트웨어 시리얼 초기화
  serialLCD.print("$B,0\r");    // 커서 끔
  serialLCD.print("$G,2,1\r");    // 2행 1열로 커서를 옮겨 문자열 출력
  serialLCD.print("$T,Current Count : \r");
}

void loop(){
  serialLCD.print("$G,2,17\r");   // 카운트 값 출력 위치로 커서 옮김
  serialLCD.print("$T,");     // 문자열 출력 명령
  serialLCD.print(count++);
  serialLCD.print('\r');
  delay(1000);
}
