#include <IRremote.h>

int LED_pins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};

// 리모컨 숫자 버튼의 데이터 코드
// 그림 5의 리모컨으로 스케치 1을 통해 확인
unsigned int key_codes[] = {
  0x6897, 0x30CF, 0x18E7, 0x7A85, 0x10EF,
  0x38C7, 0x5AA5, 0x42BD, 0x4AB5, 0x52AD
};

int RECV_PIN = 11;      // 적외선 수신기의 DATA 핀 연결

IRrecv irrecv(RECV_PIN);      // 적외선 수신기 초기화
decode_results results;     // 수신 데이터

void setup() {
  for(int i = 0; i < 9; i++){   // LED 연결 핀을 출력으로 설정
    pinMode(LED_pins[i], OUTPUT);
    digitalWrite(LED_pins[i], LOW);
  }
  Serial.begin(115200);
  irrecv.enableIRIn();      // 적외선 수신기 시작
}

void loop() {
  if(irrecv.decode(&results)) {   // 디코딩 결과
    int index = -1;
    for(int i = 0; i <= 9; i++){    // 숫자 키 값과 비교
      if((results.value & 0xFFFF) == key_codes[i]){
        index = i;
        break;
      }
    }

    if(index == -1){
      Serial.println("** Unknown value...");
    }
    else{
      Serial.println(index + String(" LEDs are going to be on..."));
      for(int i = 0; i < index; i++)    // 숫자에 해당하는 개수의 LED 켜기
        digitalWrite(LED_pins[i], HIGH);
      for(int i = index; i <= 9; i++) // 나머지 LED 끄기
        digitalWrite(LED_pins[i], LOW);
    }

    irrecv.resume();      // 다음 데이터 수신
  }
}
