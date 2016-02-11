#include <SoftwareSerial.h>

int temperature_pin = A0;    // 온도 센서 연결 핀
SoftwareSerial mySerial(2, 3);    // 마스터 연결 시리얼 포트

void setup() {
  mySerial.begin(9600);     // UART 시리얼 포트 초기화
}

void loop() {
  if(mySerial.available()){     // 마스터로부터의 데이터 전송 확인
    char data = mySerial.read();
    if(data == 'T'){      // 현재 온도를 요구한 경우 온도 반환
      mySerial.print("Current temperature is ");
      mySerial.print(get_temperature());
      mySerial.println(" degrees C");
    }
  }
}

float get_temperature() {
  int reading = analogRead(temperature_pin);  // ADC 값 읽기
  float voltage = reading * 5.0 / 1024.0;   // Volt 단위 전압으로 변환
  float temperature = (voltage - 0.5) * 100;  // 온도로 변환

  return temperature;
}
