int redLed = 12;
int greenLed = 11;
int buzzer = 10;
int smokeA0 = A0;
// Your threshold value
int AirPolution = 300;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  
  Serial.begin(115200);
}

int getCga(){
  //int cga = 168;
  int cga = analogRead(A0);
 //int ValueAQMap = map(cga,0,4095,0,1024);
  Serial.print("Pin A0: ");
  Serial.println(cga);
  
  return cga;
  doc["sensor"]["cga"] = cga;
  doc["sensor"]["humidity"] = cga;
  doc["sensor"]["temperature"] = cga;
  doc["sensor"]["pm"] = cga;
  delay(2000);
}
void dataTraitement(){
 int AirData = getCga();
  if (AirData > AirPolution)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }
}
void loop() {
  getCga();
  dataTraitement();
  delay(2000);
  // Checks if it has reached the threshold value
 
}
void dataTraitement(){
  int redLed = 12;
int greenLed = 11;
int buzzer = 10;
 int AirData = getCga();
  if (AirData > AirPolution)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    //tone(buzzer, 1000, 200);
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    //noTone(buzzer);
  }
}
