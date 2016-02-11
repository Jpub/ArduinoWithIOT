#include <SPI.h>

byte count;

void setup (void)
{
  // SPI 통신을 위한 핀들의 입출력 설정
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);

  // 마스터의 전송 속도에 맞추어 통신 속도를 설정한다.
  SPI.setClockDivider(SPI_CLOCK_DIV16);

  // SPI 통신을 위한 레지스터를 설정
  SPCR |= _BV(SPE);       // SPI 활성화
  SPCR &= ~_BV(MSTR);     // Slave 모드 선택
  SPCR |= _BV(SPIE);      // 인터럽트 허용

  count = 0;          // 카운터 초기화
}

// SPI 통신으로 데이터가 수신될 때 발생하는 인터럽트 처리 루틴
ISR (SPI_STC_vect)
{
  SPDR = count + '0';     // 카운터 값을 ASCII 값으로 전달
}

void loop (void)
{
  count = (count + 1) % 10;   // 카운터 값 증가
  delay(1000);
}
