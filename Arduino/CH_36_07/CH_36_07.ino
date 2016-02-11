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
String buffer = "";       // 수신 데이터 버퍼
String valueString;     // 밝기값 저장을 위한 문자열

int pinLED = 3;       // LED 연결 핀
int brightness = 0;     // 현재 밝기

void setup(){
  Serial.begin(9600);

  Ethernet.begin(MAC, IP);    // 고정 IP 사용
  Serial.print("Local IP : ");
  Serial.println(Ethernet.localIP());
  delay(2000);        // 이더넷 쉴드의 초기화 대기

  server.begin();       // 웹 서버 시작

  pinMode(pinLED, OUTPUT);    // LED 연결 핀을 출력으로 설정
  analogWrite(pinLED, brightness);  // LED는 꺼진 상태로 시작
}

void loop() {
  // 웹 브라우저의 접속 여부 확인
  EthernetClient client = server.available();
  if (client) {       // 웹 브라우저가 접속한 경우
    int response_type = -1;
    Serial.println("** New client connected...");

    while (client.connected()) {
      // 줄 단위의 데이터 수신
      // HTML 요청의 끝을 알아내기 위해 빈 줄이 수신되었는지의 여부를 반환함
      boolean empty_line = read_one_line(client);
      Serial.println(buffer);

      int pos = buffer.indexOf("GET /led.cgi?brightness=");
      if(pos >= 0){
        valueString = "";
        pos += 24;
        int pos_end = -1;
        for(int i = pos; i < buffer.length(); i++){
          if(buffer[i] == ' '){   // 공백문자를 발견할 때까지 
            pos_end = i;
            break;
          }
        }
        if(pos_end != -1)     // 값 영역 추출
          valueString = buffer.substring(pos, pos_end);
      }

      if(empty_line) break;   // HTML 요청이 끝나면 결과 전송
    }

    int input = valueString.toInt();
    if(input >= 0 && input <= 255){ // 유효한 밝기값인 경우
      brightness = input;
      analogWrite(pinLED, brightness);
    }

    show_main_page(client);   // 페이지 전송

    client.stop();        // 웹 브라우저 연결 종료
    Serial.println("** Client disonnected...");
  }
}

boolean read_one_line(EthernetClient client)
{
  buffer = "";        // 버퍼 비움
  while(client.available()){
    char c = client.read();   // 바이트 데이터 읽기
    if(c == '\r'){        // 개행문자를 수신한 경우
      client.read();      // ‘\n’ 문자 버림
      break;
    }
    buffer = buffer + c;      // 개행문자 이외의 문자는 버퍼에 저장
  }

  return (buffer.length() == 0);    // 빈 줄 여부 반환
}

void show_main_page(EthernetClient client)
{
  // HTML 헤더
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();

  // HTML 내용
  client.println("<html>");
  client.println("<body>");

  client.print("LED brightness (0~255) is "); // 현태 LED 밝기
  client.println(brightness);

  // CGI를 통해 사용자 입력을 받음
  client.println("<br />");
  client.println("<FORM method=\"get\" action=\"/led.cgi\">");
  client.println("<P>Brightness <INPUT type=\"text\" name=\"brightness\">");
  client.println("<P><INPUT type=\"submit\" value=\"Submit\"> </FORM>");

  client.println("</body>");
  client.println("</html>");
  client.println();
}
