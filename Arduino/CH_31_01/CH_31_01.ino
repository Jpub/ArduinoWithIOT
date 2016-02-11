// 모터 1 제어를 위한 연결 핀
int PWM1 = 6;        // 속도 제어
int Enable1 = 7;        // 활성/비활성 상태 제어
int DIR1 = 8;       // 회전 방향 제어

void setup(){
  // 모터 제어를 위한 핀들을 출력으로 설정
  pinMode(PWM1, OUTPUT);
  pinMode(Enable1, OUTPUT);
  pinMode(DIR1, OUTPUT);

  digitalWrite(Enable1, HIGH);    // 초기 상태는 비활성화 상태
}

void loop(){
  digitalWrite(Enable1, LOW);   // 모터 1 활성화

  digitalWrite(DIR1, HIGH);   // 정방향 회전
  for(int i = 0; i < 256; i++){   // 속도 조절을 위한 PWM 신호 출력
    analogWrite(PWM1, i);
    delay(25);
  }
  analogWrite(PWM1, 0);     // 모터 정지

  delay(1000);

  digitalWrite(DIR1, LOW);    // 역방향 회전
  for(int i = 0; i < 256; i++){   // 속도 조절을 위한 PWM 신호 출력
    analogWrite(PWM1, i);
    delay(25);
  }
  analogWrite(PWM1, 0);     // 모터 정지

  digitalWrite(Enable1, HIGH);    // 모터 1 비활성화

  while(true);
}
