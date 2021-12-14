#include <LiquidCrystal_I2C.h>
#include <WiFi.h> //LIBRARY FOR ESP FUNCTIONALITY
#include <Wire.h> LIBRARY FOR SHT30
#include <NTPClient.h>
#include <HTTPClient.h>
WiFiUDP ntpUDP;
NTPClient temps(ntpUDP, "fr.pool.ntp.org" ,0, 60000);
int lcdColumns = 20;
int lcdRows = 4;
#define Addr 0x45 // WEMOS SHT30 I2C address is 0x45
const char* host = "api.waziup.io"; //WAZIUP SERVER
const char* devID = "ck-device"; //DEVICE ID - example 605db108af408600066050ae
const char* sensorTemp = "TC"; //SENSOR ID - example temperatureSensor_1
const char* sensorHum = "1";
const char* sensorAQ = "AQ";
const int http_port = 80; //HTTP PORT

//url
String url = "/api/v2/devices/ck-device/sensors/";
String urlTemp = url + sensorTemp + "/value";
String urlHum = url + sensorHum + "/value";
String urlAQ = url + sensorAQ + "/value";
//DECLARE OBJECT OF CLASS HTTPClient
    HTTPClient httpTemp;    
    HTTPClient httpHum; 
    HTTPClient httpAQ;
//declared the variable 
  int ValueAQ; //value Air Qality
  float CTemp;
  float Humidity;
  String dateTime;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
void setup() {
 
//SERIAL COMMUNICATION
  Serial.begin( 115200);
// initialize LCD
    lcd.init();
// turn on LCD backlight                      
    lcd.backlight();
//begin connection
    WiFi.begin("Penda_hakim", "cypher007@zaco06");
    Serial.println("Waiting for Connection");
   while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
//code for mq135
ValueAQ = analogRead(34);
// code for sht30 
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
  float CTemp = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;
  float Humidity = ((((data[3] * 256.0) + data[4]) * 100) / 65535.0);
 String valueTempCon = String(CTemp);
 String valueHumCon = String(Humidity);
 String valueAQCon = String(ValueAQ);
 temps.update();
//L'heure est envoyée sur le port serie au format 00:00:00 en 1 fois 
dateTime = temps.getFormattedTime();
  Serial.println(dateTime);
// Print in lcd 
    lcd.setCursor(0,0);
    lcd.print("Time:"+dateTime);
    lcd.setCursor(0,1);
    lcd.print( "Temperature:"+valueTempCon+"C");
    lcd.write(223);
    lcd.setCursor(0,2);
    lcd.print(" Humidity:"+valueHumCon+"%");
    lcd.setCursor(0,3);
    lcd.print("AirQuality:"+valueAQCon+"PPM");
    delay(10000);

//posting data
if (WiFi.status() == WL_CONNECTED) {
  //SPECIFY REQUEST DESTINATION
    httpTemp.begin(host,http_port, urlTemp);
   httpHum.begin(host,http_port, urlHum);
   httpAQ.begin(host,http_port, urlAQ );
   httpHum.addHeader("Content-Type", "text/plain;charset=utf-8");  
   httpTemp.addHeader("Content-Type", "text/plain;charset=utf-8");  
   httpAQ.addHeader("Content-Type", "text/plain;charset=utf-8");
   httpAQ.POST(valueAQCon);
   httpHum.POST(valueHumCon);
   httpTemp.POST(valueTempCon);
   //CLOSING HTTP CONNECTION
    httpTemp.end();
    httpHum.end();
    httpAQ.end();
    
} else {
    Serial.println("WiFi Connection Fail");
  }
   delay(5000);
}
