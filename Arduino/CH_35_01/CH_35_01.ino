#include <Twitter.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <SPI.h>

byte MAC[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xD2, 0x16 };
IPAddress IP(192, 168, 0, 10);
char msg[] = "Hello from Arduino.";

// 토큰을 이용하여 트위터 서비스 사용
Twitter twitter("토큰_문자열을_여기에_넣는다");

void setup(){
  Serial.begin(9600);

  Ethernet.begin(MAC, IP);    // 고정 IP 사용
  Serial.print("Local IP : ");
  Serial.println(Ethernet.localIP());
  delay(2000);        // 이더넷 쉴드의 초기화 대기
}

void loop() {
  Serial.println("* Connecting to twitter...");
  if(twitter.post(msg)){      // 단문 메시지 작성
    int status = twitter.wait();
    if(status == 200){
      Serial.println("Okay... Arduino made a tweet...");
    }
    else{
      Serial.print("Error occurred... ");
      Serial.println(status);
    }
  }
  else{
    Serial.println("Connection failed...");
  }

  while(true);
}
