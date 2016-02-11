#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <SPI.h>

byte MAC[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xD2, 0x16 };
IPAddress IP(192, 168, 0, 10);
EthernetServer server(80);    // 80번 포트를 이용하는 웹 서버 생성

void setup(){
  Serial.begin(9600);

  Ethernet.begin(MAC, IP);    // 고정 IP 경우
  delay(2000);        // 이더넷 쉴드의 초기화 대기

  server.begin();       // 웹 서버 시작
  Serial.print("* Web Server Address : ");  // 웹 서버 주소를 시리얼 모니터로 출력
  Serial.println(Ethernet.localIP());
}

void loop()
{
  // 아두이노의 웹 서버로 요청을 보낸 클라이언트 검사
  EthernetClient client = server.available();

  if(client){         // 클라이언트가 존재하는 경우
    while(client.available()) 
      client.read();      // 클라이언트의 요청은 읽어서 버림

    // HTTP 메시지 전송
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");  // 응답 전송 후 연결 종료
    client.println("Refresh: 3");   // 3초 마다 웹 페이지 자동 갱신
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.print("Analog Input (0 ~ 1023) : ");
    client.println(analogRead(A0));   // 가변 저항의 값을 읽어 전송
    client.println("</html>");
    client.println();

    client.stop();
  }
}
