int pin_red = 11;
int pin_green = 10;
int pin_blue = 9;

String buffer = "";

void setup(){
  pinMode(pin_red, OUTPUT);
  pinMode(pin_green, OUTPUT);
  pinMode(pin_blue, OUTPUT);

  analogWrite(pin_red, 255);    // 꺼진 상태로 시작
  analogWrite(pin_green, 255);
  analogWrite(pin_blue, 255);

  Serial.begin(9600);
}

void loop(){
  if(Serial.available()){
    char data = Serial.read();
    if(data == '\n'){     // 문자열 수신 종료
      Serial.println(buffer);
      if(buffer.length() > 1){
        int brightness = buffer.substring(1).toInt();   // 값 추출
        switch(buffer[0]){      // 각 색상 성분 제어
        case 'R':
          analogWrite(pin_red, 255 - brightness);
          Serial.println(String("Red : ") + brightness);
          break;
        case 'G':
          analogWrite(pin_green, 255 - brightness);
          Serial.println(String("Green : ") + brightness);
          break;
        case 'B':
          analogWrite(pin_blue, 255 - brightness);
          Serial.println(String("Blue : ") + brightness);
          break;
        }
      }
      buffer = "";
    }
    else buffer = buffer + data;
  }
}
