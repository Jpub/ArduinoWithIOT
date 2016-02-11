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

String buffer = "";      // 수신 데이터 저장 버퍼
boolean process_it = false;

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
    if(c == '\n')
      process_it = true;      // 한 줄 수신 종료
    else 
      buffer = buffer + c;
  }

  if(process_it) process_data();    // 수신 데이터 처리

  // 서버와의 접속이 종료된 경우 클라이언트 종료
  if (!client.connected()) {
    Serial.println();
    Serial.println("* Disconnecting...");
    client.stop();        // 클라이언트 종료

    while(true);
  } 
}

void process_data(void)
{
  String key[] = { "temperature", "humidity", "speed" };
  String value_string = "";
  int index, position, position_end;

  // 추출하고자 하는 정보의 키워드 검색
  for(index = 0; index < 3; index++){
    position = buffer.indexOf(key[index]);
    if(position != -1) break;
  }

  // 온도, 습도, 풍속 정보가 포함되어 있는 경우
  if(index < 3){
    position = buffer.indexOf("value") + 7; // 값 시작 위치
    position_end = -1;
    for(int i = position; i < buffer.length(); i++){
      if(buffer[i] == '\"'){
        position_end = i;     // 값 종료 위치
        break;
      }
    }

    if(position_end != -1){
      value_string = buffer.substring(position, position_end);
      Serial.println(" >> " + buffer);  // 수신된 문자열
      Serial.println(key[index] + " : " + value_string);  // 추출된 내용
    }
  }

  buffer = "";
  process_it = false;
}
