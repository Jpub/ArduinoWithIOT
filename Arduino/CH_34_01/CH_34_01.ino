#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <SPI.h>

byte MAC[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xD2, 0x16 };
IPAddress IP(192, 168, 0, 10);
EthernetClient client;
char server_address[] = "api.openweathermap.org";
char server_page[] = "/data/2.5/weather?q=\"busan\"&mode=xml";

void setup(){
  Serial.begin(9600);

  Ethernet.begin(MAC, IP);    // 고정 IP 사용
  Serial.print("Local IP : ");
  Serial.println(Ethernet.localIP());
  delay(2000);        // 이더넷 쉴드의 초기화 대기

  Serial.println("* Connecting to server...");
  // 날씨 정보 제공 서버에 접속
  if(client.connect(server_address, 80)){
    Serial.println("* Connected to server...");

    // 부산의 현재 날씨 정보 요청
    client.println(String("GET ") + server_page);
    client.println("Connection: close");  // 데이터 수신 종료 후 접속 종료
    client.println();     // 요청 종료 알림
  }
  else{
    Serial.println("* Connection to server failed...");
  }
}

void loop()
{
  // 웹 서버로부터 수신한 데이터가 존재하는 경우
  if (client.available()) {
    char c = client.read();   // 수신 데이터를 읽기
    Serial.print(c);      // 시리얼 모니터로 수신 데이터 출력
  }

  // 서버와의 접속이 종료된 경우 클라이언트 종료
  if (!client.connected()) {
    Serial.println();
    Serial.println("* Disconnecting...");
    client.stop();        // 클라이언트 종료

    while(true);
  } 
}
