#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <SPI.h>

char ssid[] = "hgycap";         // 네트워크의 SSID
char pass[] = "your_password";    // AP의 패스워드
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);

  if (WiFi.status() == WL_NO_SHIELD) {  // 와이파이 쉴드 검사
    Serial.println("** WiFi shield NOT present.");
    while (true);
  }

  String fv = WiFi.firmwareVersion(); // 펌웨어 버전 검사
  Serial.println("* Firmware : v." + fv);

  while(status != WL_CONNECTED) {
    Serial.print("Attempting to connect to \"");
    Serial.print(ssid);
    Serial.println("\"");

    status = WiFi.begin(ssid, pass);  // WPA/WPA2 네트워크에 연결

    delay(10000);       // 접속 대기
  }

  Serial.print("You're connected to the network \"");
  Serial.print(ssid);
  Serial.println("\"");

  printCurrentNet();      // 접속된 네트워크 정보
  printWifiData();        // 와이파이 쉴드 정보
}

void loop() { }

void printWifiData() {
  IPAddress ip = WiFi.localIP();
  Serial.print(" >> IP Address: ");
  Serial.println(ip);

  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print(" >> MAC address: ");
  for(int i = 5; i >= 0; i--){
    Serial.print(mac[i], HEX);
    if(i != 0) Serial.print(":");
  }
  Serial.println();
}

void printCurrentNet() {
  Serial.print(" >> SSID : ");
  Serial.println(WiFi.SSID());

  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print(" >> BSSID : ");
  for(int i = 5; i >= 0; i--){
    Serial.print(bssid[i], HEX);
    if(i != 0) Serial.print(":");
  }
  Serial.println();

  long rssi = WiFi.RSSI();
  Serial.print(" >> Signal strength (RSSI) : ");
  Serial.println(rssi);

  byte encryption = WiFi.encryptionType();
  Serial.print(" >> Encryption Type : ");
  Serial.println(encryption, HEX);
}
