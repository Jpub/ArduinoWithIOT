#include <SPI.h>

void setup (void)
{
  SPI.begin ();     // SPI 통신 초기화
  digitalWrite(SS, HIGH);   // 슬레이브가 선택되지 않은 상태로 유지

  // 안정적인 전송을 위해 분주비를 높여 전송 속도를 낮춤
  SPI.setClockDivider(SPI_CLOCK_DIV16);
}

void loop (void)
{
  const char *p = "Hello, World\n";

  digitalWrite(SS, LOW);      // 슬레이브를 선택한다.
  for (int i = 0; i < strlen(p); i++){  // 문자열을 전송한다.
    SPI.transfer(p[i]);
  }

  digitalWrite(SS, HIGH);     // 슬레이브 선택을 해제한다.

  delay(1000);
}
