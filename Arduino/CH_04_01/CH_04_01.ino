#include "U8glib.h"

// OLED 디스플레이 연결
// SCK = 13, MOSI = 11, CS = 10, DC = 9
U8GLIB_SH1106_128X64 u8g(13, 11, 10, 9);  

void draw(void){        // 그리기 명령어 집합
  u8g.setFont(u8g_font_unifont);    // 폰트 설정
  u8g.setPrintPos(10, 20);    // 문자열 출력 시작 위치
  u8g.print("Hello OLED...");
  u8g.setPrintPos(30, 50);
  u8g.print("by hgycap");
  u8g.drawLine(10, 10, 120, 60);    // 직선 그리기 (x1, y1, x2, y2)
}

void setup(void) {
}

void loop(void) {
  // 그리기 루틴
  u8g.firstPage();        // 첫 번째 영역
  do{
    draw();
  }while(u8g.nextPage());     // 다음 영역

  delay(500);         // 이미지 갱신
}
