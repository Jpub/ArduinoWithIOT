#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX) 형식으로 블루투스 모듈과 교차하여 연결된다.
SoftwareSerial BTSerial(2, 3);

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
  BTSerial.begin(9600);
}

void loop(){
  if(BTSerial.available()){
    char data = BTSerial.read();
    if(data == '\n'){
      Serial.println(buffer);
      if(buffer.length() > 1){
        int brightness = buffer.substring(1).toInt();
        switch(buffer[0]){
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
