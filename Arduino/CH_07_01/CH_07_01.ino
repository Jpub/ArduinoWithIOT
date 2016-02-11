#include <IRremote.h>

int RECV_PIN = 11;      // 적외선 수신기의 DATA 핀 연결

IRrecv irrecv(RECV_PIN);      // 적외선 수신기 초기화
decode_results results;     // 수신 데이터

void setup()
{
  Serial.begin(115200);       // 시리얼 통신 초기화
  irrecv.enableIRIn();      // 적외선 수신기 시작
}

void loop() 
{
  if(irrecv.decode(&results)) {   // 디코딩 결과
    Serial.print("Received data : 0x");
    Serial.println(results.value, HEX); // 수신 데이터 출력

    irrecv.resume();      // 다음 데이터 수신
  }
  
  delay(200);
}
