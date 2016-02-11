#include <hidboot.h>

// 키보드 동작 처리 클래스
class KeyboardActionParser : public KeyboardReportParser
{
  void PrintKey(uint8_t mod, uint8_t key);

protected:
  void OnKeyDown(uint8_t mod, uint8_t key);
  void OnKeyUp(uint8_t mod, uint8_t key);
};

void KeyboardActionParser::PrintKey(uint8_t m, uint8_t key) // 키 값 화면 출력
{
  MODIFIERKEYS mod;     // 모디파이어 키 상태
  *((uint8_t*)&mod) = m;

  // 왼쪽 모디파이어 키
  Serial.print((mod.bmLeftCtrl == 1) ? "Ctrl " : " ");
  Serial.print((mod.bmLeftShift == 1) ? "Shift " : " ");
  Serial.print((mod.bmLeftAlt == 1) ? "Alt " : " ");

  Serial.print(" << ");
  Serial.print(key);      // 키 값 출력

  // 아스키 문자로 변환 가능한 키가 눌러진 경우 아스키 문자 출력
  uint8_t c = OemToAscii(m, key); // 아스키 문자로 변환
  if(c) Serial.print(String(", ") + (char)c);
  Serial.print(" >> ");

  // 오른쪽 모디파이어 키
  Serial.print((mod.bmRightCtrl == 1) ? "Ctrl " : " ");
  Serial.print((mod.bmRightShift == 1) ? "Shift" : " ");
  Serial.print((mod.bmRightAlt == 1) ? "Alt" : " ");
  Serial.println();
};

void KeyboardActionParser::OnKeyDown(uint8_t mod, uint8_t key) // 키 누름
{
  Serial.print("Down : ");
  PrintKey(mod, key);
}

void KeyboardActionParser::OnKeyUp(uint8_t mod, uint8_t key) // 키 뗌
{
  Serial.print("Up   : ");
  PrintKey(mod, key);
}

USB Usb;            // USB 연결을 위한 클래스
// USB를 통해 HID 프로토콜을 사용하는 키보드 연결
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> HidKeyboard(&Usb);

KeyboardActionParser parser;

void setup()
{
  Serial.begin(115200);
  Serial.println("Start");

  Usb.Init();         // USB 연결 초기화

  delay(200);

  // 키보드 동작 처리 객체 등록
  HidKeyboard.SetReportParser(0, (HIDReportParser*)&parser);
}

void loop()
{
  Usb.Task();       // 키보드 동작 감시
}
