#include <Wire.h>
#include <Adafruit_PN532.h>
#define USE_KEY_B  1   // 인증에 사용할 키
#define USE_KEY_A 0

#define PN532_IRQ 2   // Interrupt Request
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
  Serial.println((versiondata >> 24) & 0xFF, HEX);  // 칩 번호
  Serial.print("Firmware ver.");
  Serial.print((versiondata >> 16) & 0xFF, DEC);  // Major 버전
  Serial.print('.'); 
  Serial.println((versiondata >> 8) & 0xFF, DEC); // Minor 버전
  
  nfc.SAMConfig();      // NFC 쉴드를 읽기 상태로 설정
  
  Serial.println("Waiting for an ISO14443A Card ...");
}

void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // UID 저장 버퍼
  // UDI 길이 (MiFare Classic은 4 바이트, MiFare Ultralight는 7 바이트)
  uint8_t uidLength;
  uint8_t currentblock;     // 현재 블록 번호
  bool authenticated = false;   // 인증 여부
  uint8_t data[16];     // 블록 데이터 저장 버퍼

  // NDEF와 MiFare Classic에서 Key B는 0xFFFFFFFFFFFF로 동일함
  uint8_t key[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if(success){
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length : ");
    Serial.print(uidLength, DEC);
    Serial.println(" bytes");
    Serial.print("  UID Value : ");
    nfc.PrintHex(uid, uidLength);   // UID 출력

    // 4개 블록을 포함하는 16개 섹터, 총 64개 블록 데이터 읽기
    // 섹터별로 인증을 수행
    for (currentblock = 0; currentblock < 64; currentblock++){
      bool isFirstBlock = nfc.mifareclassic_IsFirstBlock(currentblock);

      if(isFirstBlock){
        Serial.print("------------------------Sector ");
        Serial.print(currentblock / 4, DEC);
        Serial.println("-------------------------");

        authenticated = false;
      }

      // 섹터의 첫 번째 블록에서 인증
      if (!authenticated){
        // MiFare Classic의 Key A 디폴트값 : FF FF FF FF FF FF
        // NDEF의 Key A 디폴트값 : A0 A1 A2 A3 A4 A5
        // MiFare Classic & NDEF의 Key B 디폴트값 : FF FF FF FF FF FF
        success = nfc.mifareclassic_AuthenticateBlock (uid, uidLength, currentblock, USE_KEY_B, key);

        if (success) authenticated = true;
      }

      Serial.print("Block ");
      Serial.print(currentblock, DEC);
      if(currentblock < 10) Serial.print("  ");
      else Serial.print(" ");

      if (!authenticated){
        Serial.println(" unable to authenticate");
      }
      else{
        // 블록 데이터 읽기
        success = nfc.mifareclassic_ReadDataBlock(currentblock, data);

        if(success){
          nfc.PrintHexChar(data, 16); // 16 바이트 데이터 출력
        }
        else{
          Serial.println(" unable to read");
        }
      }
    }
  }
  else{
    Serial.println("This doesn't seem to be a Mifare Classic card!");
  }

  // 태그 스캔을 위해 문자 입력 대기
  Serial.println("\n\nSend a character to run the mem dumper again!\n\n");

  while (!Serial.available());
  while (Serial.available()) Serial.read();
}
