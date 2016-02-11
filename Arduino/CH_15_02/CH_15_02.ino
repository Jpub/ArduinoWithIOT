#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX) 형식으로 블루투스 모듈과 교차하여 연결
SoftwareSerial BTSerial(2, 3);
int pins[] = {4, 5, 6, 7, 8, 9, 10, 11};  // LED 연결 핀

void setup()  
{
  Serial.begin(9600);     // 컴퓨터와의 시리얼 통신 초기화
  BTSerial.begin(9600);     // 블루투스 모듈 초기화

  for(int i = 0; i < 8; i++){   // LED 제어 핀 설정
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }
}

void loop()
{
  if(BTSerial.available()){     // 블루투스로 데이터 수신
    byte no = BTSerial.read();
    if(no < 0 || no > 255)    // 번위 검사
      Serial.println("** Wrong Number...");
    else{
      for(int i = 0; i < 8; i++){   // LED 제어
        if( no & (1 << i) )
          digitalWrite(pins[i], HIGH);
        else
          digitalWrite(pins[i], LOW);
      }
    }
  }
}
