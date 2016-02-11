#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <SPI.h>

byte MAC[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xD2, 0x16 };
IPAddress IP(192, 168, 0, 10);

void setup(){
  Serial.begin(9600);

  // Ethernet.begin(MAC, IP);   // 고정 IP를 사용하는 경우
  if(Ethernet.begin(MAC) == 0){   // DHCP로 유동 IP를 사용하는 경우
    Serial.println("* DHCP failed...");
    Ethernet.begin(MAC, IP);    // DHCP가 실패한 경우
  }

  delay(2000);        // 이더넷 쉴드의 초기화 대기
}

void loop(){
  IPAddress address;

  Serial.print("IP Address  : ");
  address = Ethernet.localIP();   // IP 주소
  print_address(address);

  Serial.print("Subnet Mask : ");
  address = Ethernet.subnetMask();  // 서브넷 마스크
  print_address(address);

  Serial.print("Gateway     : ");
  address = Ethernet.gatewayIP();   // 게이트웨이 주소
  print_address(address);

  Serial.print("DNS Server  : ");
  address = Ethernet.dnsServerIP(); // DNS 서버 주소
  print_address(address);

  while(true);
}

void print_address(IPAddress address) // IP 주소 출력
{
  for(int i = 0; i < 4; i++){
    Serial.print(address[i], DEC);
    if(i != 3) Serial.print(".");
  }
  Serial.println();
}
