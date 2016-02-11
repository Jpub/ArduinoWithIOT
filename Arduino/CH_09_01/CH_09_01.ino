#include <SoftwareSerial.h>

SoftwareSerial gps(2, 3);      // GPS 리시버 연결

void setup() {
  Serial.begin(9600);
  gps.begin(9600);
}

void loop() {
  if(gps.available()){
    Serial.write(gps.read());
  }
}
