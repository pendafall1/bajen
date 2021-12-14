int redLed = 11;
int greenLed = 12;
int buzzer = 10;
void setup() {
pinMode(redLed, OUTPUT);
pinMode(greenLed, OUTPUT);
digitalWrite(redLed, LOW);
}
void loop() {
    digitalWrite(greenLed, LOW);
digitalWrite(redLed, HIGH);

tone(buzzer, 1000, 200);
delay(1000);
digitalWrite(redLed, LOW);
digitalWrite(greenLed, HIGH);
noTone(buzzer);
delay(1000);
}