int relay_control = 2;      // 릴레이 제어 핀 연결

void setup() {
  Serial.begin(9600);
  pinMode(relay_control, OUTPUT); // 릴레이 제어 핀을 출력으로 설정
  digitalWrite(relay_control, LOW);
}

void loop() {
  if(Serial.available()){     // 시리얼 모니터에서 문자 수신
    char c = Serial.read();
    
    if(c == 'o' || c == 'O'){   // 스위치 켜기
      Serial.println("Switch ON...");
      digitalWrite(relay_control, HIGH);
    }
    else{           // 스위치 끄기
      Serial.println("Switch OFF...");
      digitalWrite(relay_control, LOW);
    }
  }
}
