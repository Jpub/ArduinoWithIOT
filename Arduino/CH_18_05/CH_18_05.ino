#include <SPI.h>
#define SS1 10
#define SS2 9

char sendBuffer[20];      // 전송 문자열 저장 버퍼
int count;            // 현재 카운터

void setup (void)
{
  SPI.begin ();       // SPI 통신 초기화
  digitalWrite(SS1, HIGH);      // 슬레이브가 선택되지 않은 상태로 유지
  // 디폴트 SS핀인 10번 핀만이 출력으로 설정되므로
  // 추가 SS핀인 9번 핀을 출력으로 설정한다.
  pinMode(SS2, OUTPUT);
  digitalWrite(SS2, HIGH);

  // 안정적인 전송을 위해 분주비를 높여 전송 속도를 낮춤
  SPI.setClockDivider(SPI_CLOCK_DIV16);

  count = 0;          // 카운터 초기화
}

void loop (void)
{
  count = count + 1;

  if(count % 2) digitalWrite(SS1, LOW);   // 슬레이브를 선택
  else digitalWrite(SS2, LOW);

  String(count).toCharArray(sendBuffer, 20);  // 카운터 값을 문자열로 변환
  for (int i = 0; i < strlen(sendBuffer); i++){ // 문자열을 전송한다.
    SPI.transfer(sendBuffer[i]);
  }
  SPI.transfer('\n');       // 개행문자 추가

  if(count % 2) digitalWrite(SS1, HIGH);    // 슬레이브를 선택한다.
  else digitalWrite(SS2, HIGH);

  delay(1000);
}
