#include <XBee.h>
#include <SoftwareSerial.h>

uint8_t xbee_RX = 2;
uint8_t xbee_TX = 3;
SoftwareSerial xbee_serial(xbee_RX, xbee_TX);  // xbee 모듈 연결

XBee xbee = XBee();     // xbee 객체 생성

// ADC 데이터 전송을 위한 프레임
Rx16IoSampleResponse ioSample = Rx16IoSampleResponse();

void setup() { 
  Serial.begin(9600);
  
  xbee_serial.begin(9600);
  // SoftwareSerial을 통해 전달된 데이터를 xbee 객체와 연결
  xbee.setSerial(xbee_serial);
}

void loop() {
  xbee.readPacket();      // 프레임 읽기

  if (xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == RX_16_IO_RESPONSE) {
      xbee.getResponse().getRx16IoSampleResponse(ioSample);

      Serial.print("** Received I/O Sample from: ");
      // 프레임 송신 노드 주소
      Serial.println(ioSample.getRemoteAddress16(), HEX);

      if(ioSample.containsAnalog()){  // 아날로그 데이터 포함 여부
        for (int i = 0; i <= 5; i++) {
          if (ioSample.isAnalogEnabled(i)) {
            Serial.print("Analog (AI");
            Serial.print(i, DEC);
            Serial.print(") is ");
            Serial.println(ioSample.getAnalog(i, 0));  
          }
        }
      }

      if(ioSample.containsDigital()){ // 디지털 데이터 포함 여부
        for (int i = 0; i <= 8; i++) {
          if (ioSample.isDigitalEnabled(i)) {
            Serial.print("Digtal (DI");
            Serial.print(i, DEC);
            Serial.print(") is ");
            Serial.println(ioSample.isDigitalOn(i, 0));
          }
        }
      }
    }
    else {
      Serial.print("Expected I/O Sample, but got ");
      Serial.print(xbee.getResponse().getApiId(), HEX);
    }
  } 
  else if (xbee.getResponse().isError()) {
    Serial.print("Error reading packet.  Error code: ");  
    Serial.println(xbee.getResponse().getErrorCode());
  }
}
