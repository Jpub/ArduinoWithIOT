#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX) 형식으로 블루투스 모듈과 교차하여 연결
SoftwareSerial BTSerial(2, 3);
int LED1 = 9;        // LED 연결 핀
int LED2 = 10;

boolean state1 = false;     // 현재 LED의 상태
boolean state2 = false;

void setup()  
{
  BTSerial.begin(9600);     // 블루투스 연결 초기화

  pinMode(LED1, OUTPUT);    // LED 연결 핀을 출력으로 설정
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);    // LED는 꺼진 상태로 시작
  digitalWrite(LED1, LOW);
}

void loop()
{
  if (BTSerial.available()){      // 마스터로부터 데이터 수신
    char ch = BTSerial.read();

    if(ch == 'A'){        // ‘A’를 수신한 경우 첫 번째 LED 반전
      state1 = !state1;
      digitalWrite(LED1, state1);
    }
    else if(ch == 'B'){     // ‘B’를 수신한 경우 두 번째 LED 반전
      state2 = !state2;
      digitalWrite(LED2, state2);
    }
  }
}
