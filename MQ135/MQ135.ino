int ValueAQ;
int NewValue;
void setup() {
  int ValueAQ;
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  //ValueAQ = digitalRead(2);
  ValueAQ = analogRead(A0);
//int  ValueAQ = analogRead(34);
NewValue = map(ValueAQ,0,4095,0,1024);
  //Serial.print("valeur\n");
  Serial.println(ValueAQ,DEC);
 // Serial.print("ppm\n");
  // put your main code here, to run repeatedly:
delay(1000);
}
