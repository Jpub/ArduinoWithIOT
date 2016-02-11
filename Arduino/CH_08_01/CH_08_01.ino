#include <hidboot.h>

// 마우스 동작 처리 클래스
class MouseActionParser : public MouseReportParser
{
protected:
  void OnMouseMove(MOUSEINFO *mi);
  void OnLeftButtonUp(MOUSEINFO *mi);
  void OnLeftButtonDown(MOUSEINFO *mi);
  void OnRightButtonUp(MOUSEINFO *mi);
  void OnRightButtonDown(MOUSEINFO *mi);
  void OnMiddleButtonUp(MOUSEINFO *mi);
  void OnMiddleButtonDown(MOUSEINFO *mi);
};

void MouseActionParser::OnMouseMove(MOUSEINFO *mi)  // 마우스 이동
{
  Serial.print("dX = ");
  Serial.print(mi->dX, DEC);
  Serial.print(" dY = ");
  Serial.println(mi->dY, DEC);
};

void MouseActionParser::OnLeftButtonUp(MOUSEINFO *mi) // 왼쪽 버튼 뗌
{
  Serial.println("Left Button Up");
};

void MouseActionParser::OnLeftButtonDown(MOUSEINFO *mi) // 왼쪽 버튼 누름
{
  Serial.println("Left Button Down");
};

void MouseActionParser::OnRightButtonUp(MOUSEINFO *mi) // 오른쪽 버튼 뗌
{
  Serial.println("Right Button Up");
};

void MouseActionParser::OnRightButtonDown(MOUSEINFO *mi) // 오른쪽 버튼 누름
{
  Serial.println("Right Button Down");
};

void MouseActionParser::OnMiddleButtonUp(MOUSEINFO *mi) // 가운데 버튼 누름
{
  Serial.println("Middle Button Up");
};

void MouseActionParser::OnMiddleButtonDown(MOUSEINFO *mi) // 가운데 버튼 뗌
{ 
  Serial.println("Middle Button Down");
};

USB Usb;            // USB 연결을 위한 클래스
// USB를 통해 HID 프로토콜을 사용하는 마우스 연결
HIDBoot<USB_HID_PROTOCOL_MOUSE> HidMouse(&Usb);

MouseActionParser parser;

void setup()
{
  Serial.begin(115200);
  Serial.println("Start");

  Usb.Init();         // USB 연결 초기화
  delay(200);

  // 마우스 동작 처리 객체 등록
  HidMouse.SetReportParser(0, (HIDReportParser*)&parser);
}

void loop()
{
  Usb.Task();       // 마우스 동작 감시
}
