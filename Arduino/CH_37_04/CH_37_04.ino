#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <SPI.h>

char ssid[] = "hgycap";         // 네트워크의 SSID
char pass[] = "your_password";    // AP의 패스워드
int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  if (WiFi.status() == WL_NO_SHIELD) {  // 와이파이 쉴드 검사
    Serial.println("** WiFi shield NOT present.");
    while (true);
  }

  while(status != WL_CONNECTED) {
    Serial.print("* Attempting to connect to \"");
    Serial.print(ssid);
    Serial.println("\"");

    status = WiFi.begin(ssid, pass);  // WPA/WPA2 네트워크에 연결

    delay(3000);        // 접속 대기
  }

  Serial.print("* You're connected to the network \"");
  Serial.print(ssid);
  Serial.println("\"");

  server.begin();       // 웹 서버 시작
  Serial.print("* Web Server Address : ");  // 웹 서버 주소출력
  Serial.println(WiFi.localIP());
}

void loop()
{
  // 아두이노의 웹 서버로 요청을 보낸 클라이언트 검사
  WiFiClient client = server.available();

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
    client.println(analogRead(A0)); // 가변 저항의 값을 읽어 전송
    client.println("</html>");
    client.println();

    client.stop();
  }
}
