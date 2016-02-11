int pin = A0;        // 가변저항 연결 핀

void setup(){
  Serial.begin(9600);     // 시리얼 통신 초기화
}

void loop(){
  int value = analogRead(pin);    // 가변저항 값 읽기

  Serial.print("Current read is ");
  Serial.print(value);      // 디지털 값
  Serial.print(", approximately ");
  Serial.print(value * 5 / 1023.0);   // 아날로그 전압 값
  Serial.println(" V.");

  delay(1000);
}
