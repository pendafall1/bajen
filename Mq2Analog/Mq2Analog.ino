int redLed = 12;
int greenLed = 11;
int buzzer = 10;
int smokeA0 = A0;
// Your threshold value
int AirPolution = 200;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  
  Serial.begin(9600);
    int timer = 50;

  for(timer; timer >=0; timer--){
    Serial.println(" | warming up");   
  }
  Serial.println(" Done!");
}

int getCga(){
  //int cga = 168;
 int cga = analogRead(A0);
  Serial.print("Pin A0: ");
  Serial.println(cga);
  
  return cga;
 
  delay(2000);
}
void Traitement(){
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
delay(2000);
Traitement();
delay(2000);
}
