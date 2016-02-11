int LED_pins[] = {4, 5, 6, 7, 8, 9, 10, 11};  // LED 연결 핀
int position = 0;

void setup(){
  for(int i = 0; i < 8; i++)    // LED 연결 핀을 출력으로 설정
    pinMode(LED_pins[i], OUTPUT);
}

void loop(){
  position = (position + 1) % 8;    // LED를 켤 위치

  for(int i = 0; i < 8; i++){
    if(position == i) digitalWrite(LED_pins[i], HIGH);
    else digitalWrite(LED_pins[i], LOW);
  }

  delay(500);
}
