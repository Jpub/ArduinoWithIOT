int button_pins[] = {4, 5, 6, 7, 8, 9, 10, 11};  // 버튼 연결 핀

void setup(){
  for(int i = 0; i < 8; i++)    // 버튼 연결 핀을 입력으로 설정
    pinMode(button_pins[i], INPUT);
  Serial.begin(9600);     // 시리얼 모니터 초기화
}

void loop(){
  for(int i = 0; i < 8; i++){
    if(digitalRead(button_pins[i]))   // 버튼이 눌러진 경우
      Serial.print("O ");
    else            // 버튼이 눌러지지 않은 경우
      Serial.print(". ");
  }
  Serial.println();

  delay(1000);
}
