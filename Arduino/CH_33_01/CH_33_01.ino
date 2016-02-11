#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <SPI.h>

byte address[] = {192, 168, 1, 1};

IPAddress ip1(192, 168, 1, 1);
IPAddress ip2(address);
IPAddress ip3(0xC0A80101);
  
void setup(){
  Serial.begin(9600);
}

void loop(){
  Serial.println(ip1);
  Serial.println(ip2);
  Serial.println(ip3);

  while(true);
}
