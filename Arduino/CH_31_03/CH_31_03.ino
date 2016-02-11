#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX) 형식으로 블루투스 모듈과 교차하여 연결된다.
SoftwareSerial BTSerial(2, 3);

int PWM1 = 6;        // 모터 1 제어를 위한 연결 핀
int Enable1 = 7;
int DIR1 = 8;

int current_speed = 0;

void setup(){
  // 모터 제어를 위한 핀들을 출력으로 설정
  pinMode(PWM1, OUTPUT);
  pinMode(Enable1, OUTPUT);
  pinMode(DIR1, OUTPUT);

  digitalWrite(Enable1, LOW);   // 활성화 상태
  digitalWrite(DIR1, HIGH);   // 전진
  analogWrite(PWM1, 0);     // 속도 0

  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop(){
  if(BTSerial.available()){
    byte data = BTSerial.read();
    if(data >= '1' && data <= '5'){
      switch(data){
        case '1':       // 후진
          Serial.println("** Backward...");
          digitalWrite(DIR1, LOW);
          break;
        case '2':       // 전진
          Serial.println("** Forward...");
          digitalWrite(DIR1, HIGH);
          break;
        case '3':       // 정지
          Serial.println("** Stop...");
          analogWrite(PWM1, 0);
          break;
        case '4':       // 속도 10% 증가
          current_speed += 10;
          if(current_speed > 100)   // 최대 속도는 100%
            current_speed = 100;
          Serial.println(String("** Increase speed to ") + current_speed + "%.");
          analogWrite(PWM1, current_speed * 255 / 100);
          break;
        case '5':       // 속도 10% 감소
          current_speed -= 10;
          if(current_speed < 10)    // 최소 속도는 10%
            current_speed = 10;
          Serial.println(String("** Decrease speed to ") + current_speed + "%.");
          analogWrite(PWM1, current_speed * 255 / 100);
          break;
      }
    }
  }
}
