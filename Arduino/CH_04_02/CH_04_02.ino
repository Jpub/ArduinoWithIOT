#include "U8glib.h"

// OLED 디스플레이 연결
// SCK = 13, MOSI = 11, CS = 10, DC = 9
U8GLIB_SH1106_128X64 u8g(13, 11, 10, 9);  

int count = 0;
unsigned long time_previous, time_current;

void draw(void){        // 그리기 명령어 집합
  u8g.setFont(u8g_font_unifont);    // 폰트 설정
  u8g.setPrintPos(10, 20);
  u8g.print("Count : ");
  u8g.setPrintPos(20, 35);    // 문자열 출력 시작 위치
  u8g.print(count);
}

void setup(void) {
  time_previous = millis();
}

void loop(void) {
  time_current = millis();
  // 1초에 한 번 카운트 값을 증가시키고 카운터 값이 변한 경우 디스플레이 갱신
  if(time_current - time_previous > 1000){
    time_previous = time_current;
    count++;

    // 그리기 루틴
    u8g.firstPage();        // 첫 번째 영역
    do{
      draw();
    }while(u8g.nextPage());   // 다음 영역
  }
}
