#include <Wire.h>
#include <Adafruit_PN532.h>

#define PN532_IRQ  2   // Interrupt Request
#define PN532_RESET 3     // 디폴트로 연결되어 있지 않음

// NFC 쉴드 객체 생성
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

void setup(void) {
  Serial.begin(115200);
  Serial.println("Hello!");

  nfc.begin();        // NFC 쉴드 초기화

  uint32_t versiondata = nfc.getFirmwareVersion(); // 버전 정보 확인
  if (!versiondata){
    Serial.print("Didn't find PN53x board");
    while(1);
  }

  Serial.print("Found chip PN5"); 
  Serial.println((versiondata >> 24) & 0xFF, HEX);    // 칩 번호
  Serial.print("Firmware ver.");
  Serial.print((versiondata >> 16) & 0xFF, DEC);    // Major 버전
  Serial.print('.'); 
  Serial.println((versiondata >> 8) & 0xFF, DEC);   // Minor 버전
  
  nfc.SAMConfig();      // NFC 쉴드를 읽기 상태로 설정
  
  Serial.println("Waiting for an ISO14443A Card ...");
}

void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // UID 저장 버퍼
  // UDI 길이 (MiFare Classic은 4 바이트, MiFare Ultralight는 7 바이트)
  uint8_t uidLength;

  // 태그 검사
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  
  if (success){
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length : ");
    Serial.print(uidLength, DEC);
    Serial.println(" bytes");
    Serial.print("  UID Value : ");

    nfc.PrintHex(uid, uidLength);   // UID 출력

  }
  delay(1000);
}
