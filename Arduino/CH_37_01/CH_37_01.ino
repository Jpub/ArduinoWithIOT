#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <SPI.h>

void setup() {
  Serial.begin(9600);

  listNetworks();       // 액세스 포인트 검색
}

void loop() { }

void listNetworks() {
  Serial.println("** Scan Networks **");
  byte numSsid = WiFi.scanNetworks(); // 액세스 포인트 검색

  Serial.print("Number of available networks:");
  Serial.println(numSsid);      // 검색된 액세스 포인트 개수

  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet)); // SSID
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet)); // 신호 강도
    Serial.print(" dBm");
    Serial.print("\tEncryption: ");
    Serial.println(WiFi.encryptionType(thisNet)); // 암호화 종류
  }
}
