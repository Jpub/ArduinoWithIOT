int temperature_pin = A0;      // 온도 센서 연결 핀

void setup() {
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(temperature_pin);  // ADC 값 읽기
  float voltage = reading * 5.0 / 1024.0;   // Volt 단위 전압으로 변환
  float temperature = (voltage - 0.5) * 100;  // 온도로 변환

  Serial.print("Current Temperature : ");
  Serial.println(temperature);

  delay(1000);
}
