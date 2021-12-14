#include <Wire.h>
 
// WEMOS SHT30 I2C address is 0x45
#define Addr 0x45
 
void setup()
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  delay(300);
}
 
void loop()
{
  unsigned int data[6];
 
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Send measurement command
  Wire.write(0x2C);
  Wire.write(0x06);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(500);
 
  // Request 6 bytes of data
  Wire.requestFrom(Addr, 6);
 
  // Read 6 bytes of data
  // cTemp msb, cTemp lsb, cTemp crc, humidity msb, humidity lsb, humidity crc
  if (Wire.available() == 6)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
  }
 
  // Convert the data
  float cTemp = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;
  float humidity = ((((data[3] * 256.0) + data[4]) * 100) / 65535.0);
  // Output data to serial monitor
  Serial.print("Relative Humidity : ");
  Serial.print(humidity);
  Serial.println(" %RH");
  Serial.print("Temperature in Celsius : ");
  Serial.print(cTemp);
  Serial.println(" C");

  delay(500);
}
