int count = 0;

void setup(){
  Serial.begin(9600);
  while(!Serial);
}

void loop(){
  Serial.println(count++);
  delay(1000);
}
