int pin_red = 11;
int pin_green = 10;
int pin_blue = 9;

void setup(){
  pinMode(pin_red, OUTPUT);
  pinMode(pin_green, OUTPUT);
  pinMode(pin_blue, OUTPUT);

  analogWrite(pin_red, 255);    // 꺼진 상태로 시작
  analogWrite(pin_green, 255);
  analogWrite(pin_blue, 255);
}

void loop(){
  for(int i = 255; i >= 0; i--){    // 서서히 밝아짐
    analogWrite(pin_red, i);
    analogWrite(pin_green, i);
    analogWrite(pin_blue, i);
    delay(5);
  }

  for(int i = 0; i < 256; i++){   // 서서히 어두워짐
    analogWrite(pin_red, i);
    analogWrite(pin_green, i);
    analogWrite(pin_blue, i);
    delay(5);
  }
}
