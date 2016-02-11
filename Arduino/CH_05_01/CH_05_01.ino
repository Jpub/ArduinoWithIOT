#include <Wire.h>

int MPU_Address = 0x68;      // MPU6050 칩의 I2C 주소

// 가속도, 온도, 각속도 저장을 위한 변수
int AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_Address);  // MPU6050 선택
  Wire.write(0x6B);     // PWR_MGMT_1 레지스터 선택
  Wire.write(0);        // 슬립 모드 해제
  Wire.endTransmission();
  Serial.begin(115200);     // UART 직렬 통신 초기화
}

void loop(){
  Wire.beginTransmission(MPU_Address);  // MPU6050 선택
  Wire.write(0x3B);     // X축 방향 가속도 레지스터 선택
  // 연결을 종료하지 않으므로 beginTransmission 없이 읽기 가능
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_Address, 14);  // 14바이트 데이터 요청

  AcX = Wire.read() << 8 | Wire.read(); // ACCEL_XOUT
  AcY = Wire.read() << 8 | Wire.read(); // ACCEL_YOUT
  AcZ = Wire.read() << 8 | Wire.read(); // ACCEL_ZOUT
  Tmp = Wire.read() << 8 | Wire.read(); // TEMP_OUT
  GyX = Wire.read() << 8 | Wire.read(); // GYRO_XOUT
  GyY = Wire.read() << 8 | Wire.read(); // GYRO_YOUT
  GyZ = Wire.read() << 8 | Wire.read(); // GYRO_ZOUT

  Serial.print("AX = "); Serial.print(AcX);
  Serial.print(", AY = "); Serial.print(AcY);
  Serial.print(", AZ = "); Serial.print(AcZ);

  // 레지스터 값을 섭씨 온도로 변환
  Serial.print(", Tmp = "); Serial.print(Tmp / 340.00 + 36.53);

  Serial.print(", GX = "); Serial.print(GyX);
  Serial.print(", GY = "); Serial.print(GyY);
  Serial.print(", GZ = "); Serial.println(GyZ);

  Wire.endTransmission();   // 데이터 읽기 종료

  delay(1000);
}
