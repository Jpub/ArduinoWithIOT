#include <Wire.h>

void setup()
{
  Wire.begin();

  Serial.begin(9600);
}

void loop() 
{
  byte error, address;
  int nDevices = 0;

  Serial.println("Start Scanning...");
  for(address = 1; address < 127; address++ ){
    // 1바이트의 의미 없는 데이터를 전송
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0){
      Serial.print("I2C device found at address 0x");
      if(address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println();

      nDevices++;
    }
  }
  if(nDevices == 0)
    Serial.println("No I2C devices found\n");

  delay(5000);        // 5초 후 다시 스캐닝
}
