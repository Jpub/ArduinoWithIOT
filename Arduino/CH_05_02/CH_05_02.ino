#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// (I2C 주소, 칸 수(X), 줄 수(Y))
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  lcd.begin();        // LCD 초기화

  lcd.backlight();        // 백라이트 켜기

  lcd.print("1st line");
  lcd.setCursor(1, 1);
  lcd.print("2nd line");
  lcd.setCursor(2, 2);
  lcd.print("3rd line");
  lcd.setCursor(3, 3);
  lcd.print("last line");
}

void loop() { }
