#include "TinyGPS++.h"
#include <SoftwareSerial.h>

TinyGPSPlus gps;      // TinyGPS++ 파서
SoftwareSerial gps_receiver(2, 3);    // GPS 리시버 연결
unsigned long time_previous, time_current;

void setup() {
  Serial.begin(9600);
  gps_receiver.begin(9600);

  time_previous = millis();
}

void loop() {
  if(gps_receiver.available())
    gps.encode(gps_receiver.read());  // 파서로 GPS 데이터 입력

  time_current = millis();
  if(time_current - time_previous > 1000){    // 1초에 한번씩 출력
    time_previous = time_current;

    Serial.print("Time      : ");
    Serial.print(gps.time.hour());    // 시간
    Serial.print("H ");
    Serial.print(gps.time.minute());  // 분
    Serial.print("M ");
    Serial.print(gps.time.second());  // 초
    Serial.println("S ");

    Serial.print("Latitude  : ");
    Serial.println(gps.location.lat()); // 위도
    Serial.print("Longitude : ");
    Serial.println(gps.location.lng()); // 경도
  }
}
