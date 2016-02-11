#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

int speakerPin = 8;    // 스피커 연결 핀

int melody[] = {      // 학교종 멜로디. 0은 쉼표
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4, 0,
  NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, 0, 
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4, 0,
  NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_C4, 0
};

int noteDuration = 250;

void setup() {
}

void loop() { 
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(int); thisNote++) {
    tone(speakerPin, melody[thisNote], noteDuration); // 멜로디 재생
    delay(noteDuration);
  }

  while(true){ };
}
