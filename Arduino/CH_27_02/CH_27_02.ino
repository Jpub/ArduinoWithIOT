int button_pins[] = {4, 5, 6, 7, 8, 9, 10, 11};  // 버튼 연결 핀
boolean button_state[8];      // 버튼의 이전 상태

void setup(){
  for(int i = 0; i < 8; i++){   // 버튼 연결 핀을 입력으로 설정
    pinMode(button_pins[i], INPUT);
    button_state[i] = false;    // 눌러지지 않은 상태로 시작
  }
  Serial.begin(9600);     // 시리얼 모니터 초기화
}

void loop(){
  for(int i = 0; i < 8; i++){
    boolean current_state = digitalRead(button_pins[i]);
    if(button_state[i] != current_state){ // 상태가 변한 경우
      button_state[i] = current_state;  // 상태 업데이트

      Serial.print(String("Button ") + (i + 1) + " is ");
      if(current_state) Serial.println("ON !!");
      else Serial.println("OFF !");

      // 블루투스를 통해 전달할 문자열 메시지
      char message[4] = "  \n";
      message[0] = i + 1 + '0';
      message[1] = current_state + '0';
      Serial.print(message);

      delay(200);
    }
  }
}
