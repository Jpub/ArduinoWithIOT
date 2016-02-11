#include <SPI.h>

char buf[100];      // 수신된 문자 저장을 위한 버퍼
volatile byte pos;    // 수신 버퍼에 문자를 기록할 위치
volatile boolean process_it;  // 개행 문자를 만난 경우 시리얼 모니터로 출력

void setup (void)
{
  Serial.begin (9600);    // 직렬 통신 초기화

  // SPI 통신을 위한 핀들의 입출력 설정
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);

  // 마스터의 전송 속도에 맞추어 통신 속도를 설정한다.
  SPI.setClockDivider(SPI_CLOCK_DIV16);

  // SPI 통신을 위한 레지스터를 설정
  SPCR |= _BV(SPE);     // SPI 활성화
  SPCR &= ~_BV(MSTR);   // Slave 모드 선택
  SPCR |= _BV(SPIE);    // 인터럽트 허용

  pos = 0;          // 수신 문자 기록 위치 초기화
  process_it = false;
}

// SPI 통신으로 데이터가 수신될 때 발생하는 인터럽트 처리 루틴
ISR (SPI_STC_vect)
{
  byte c = SPDR;      // 수신된 문자를 얻어온다.
  
  if (pos < sizeof(buf) - 1){   // 현재 버퍼에 저장할 공간이 있는 경우
    buf[pos++] = c;     // 버퍼에 수신된 문자 기록
    
    if (c == '\n'){     // 개행 문자를 만나면 출력
      process_it = true;
    }
  }
}

void loop (void)
{
  if (process_it){        // Serial로 출력할 문자열이 있는 경우
    buf[pos] = 0;       // 문자열의 끝 표시
    Serial.print(buf);
    pos = 0;          // 버퍼가 비었음을 표시
    process_it = false;
  }
}
