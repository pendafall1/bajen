#include <LiquidCrystal_I2C.h>

#include <HTTPClient.h> //LIBRARY FOR HTTP
#include <WiFi.h> //LIBRARY FOR ESP FUNCTIONALITY
#include <Wire.h> LIBRARY FOR SHT30
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient temps(ntpUDP, "fr.pool.ntp.org" ,0, 60000);
#define Addr 0x45 // WEMOS SHT30 I2C address is 0x45
const char* host = "api.waziup.io"; //WAZIUP SERVER
const char* devID = "ck-device"; //DEVICE ID - example 605db108af408600066050ae
const char* sensorTemp = "TC"; //SENSOR ID - example temperatureSensor_1
const char* sensorHum = "1";
const char* sensorAQ = "AQ";
const int http_port = 80; //HTTP PORT
// set the LCD number of columns and rows
int lcdColumns = 20;
int lcdRows = 4;
// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  
//declared the variable 
  int ValueAQ; //value Air Qality
  float CTemp;
  float Humidity;
  String dateTime;
// convert value of air qality
  String valueAQCon;
 String  valueTempCon;
 String valueHumCon;
  int ValueAQMap; // map value of air qality
  
void setup() {
    //SERIAL COMMUNICATION
  Serial.begin( 115200);
  // initialize LCD
    lcd.init();
    // turn on LCD backlight                      
    lcd.backlight();
  //YOUR WIFI NAME XXXX, PASSWORD YYYY
  WiFi.begin("TDSI_Secure", "@ccessPointTDSI");   //ESTABLISH WIFI CONNECTION
  Wire.begin();
  Serial.println("Waiting for Connection");
  
  //IF WIFI DOESNT CONNECT CODE WONT GO PAST THIS BLOCK
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.print(".");
  }
 
  //PRINT IP ADDRESS ASSIGNED TO ESP
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
      //Update de l'heure  
  temps.update();
//L'heure est envoyée sur le port serie au format 00:00:00 en 1 fois 
dateTime = temps.getFormattedTime();
  Serial.println(dateTime);
//L'heure est envoyée en 3 fois (heure puis minutes puis secondes)

  
  //PARSING URL PATH FOR Temperature
  String url = "/api/v2/devices/ck-device/sensors/";
  String urlTemp = url + sensorTemp + "/value";
  //PARSING URL PATH FOR Humidity 
    String urlHum = url + sensorHum + "/value";
 //PARSING URL PATH FOR Air_Qality
    String urlAQ = url + sensorAQ + "/value";
   //retrieval of values ​​and mapping
      ValueAQ = analogRead(34);
    ValueAQMap = map(ValueAQ,0,4095,0,1024);

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
  float CTemp = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;
  float Humidity = ((((data[3] * 256.0) + data[4]) * 100) / 65535.0);
  // Output data to serial monitor
  Serial.print("Relative Humidity : ");
  Serial.print(Humidity);
  Serial.println(" %RH");
  Serial.print("Temperature in Celsius : ");
  Serial.print(CTemp);
  Serial.println(" C");
    //convert value to string
   valueAQCon = String(ValueAQ);
   valueTempCon = String(CTemp);
   valueHumCon = String(Humidity);
   Serial.println(ValueAQ);
   Serial.println(valueTempCon);
   Serial.println(valueHumCon);

 // Print in lcd 
    lcd.setCursor(0,0);
  //lcd.print("Heure ");
 // lcd.print(dateTime);
  lcd.setCursor(1,1);
  lcd.print(" temperature: ");
  lcd.print(valueTempCon);
  lcd.setCursor(2,2);
  lcd.print(" Humidity: ");
  lcd.print(valueHumCon);
   lcd.setCursor(3,3);
  lcd.print(" AirQality: ");
  lcd.print(ValueAQ);
  delay(1000);
   
  if (WiFi.status() == WL_CONNECTED) { //CHECK WIFI CONNECTION STATUS
    Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 //DECLARE OBJECT OF CLASS HTTPClient
    HTTPClient httpTemp;    
    HTTPClient httpHum; 
    HTTPClient httpAQ; 
  //SPECIFY REQUEST DESTINATION
    httpTemp.begin(host,http_port, urlTemp);
   httpHum.begin(host,http_port, urlHum);
   httpAQ.begin(host,http_port, urlAQ );
   //SPECIFY CONTENT TYPE
    httpHum.addHeader("Content-Type", "text/plain;charset=utf-8");  
     httpTemp.addHeader("Content-Type", "text/plain;charset=utf-8");  
      httpAQ.addHeader("Content-Type", "text/plain;charset=utf-8");  
   
    //SENDING VALUES TO THE CLOUD
    int httpCodeAQ = httpAQ.POST(valueAQCon);  
     //GETTING RESPONSE PAYLOAD
    int httpCodeHum = httpHum.POST(valueHumCon);
     int httpCodeTemp = httpTemp.POST(valueTempCon);
    String payload = httpTemp.getString();
    Serial.println(httpCodeAQ);   //PRINT HTTP RETURN CODE
    Serial.println(payload);    //PRINT PAYLOAD RESPONSE
 //CLOSING HTTP CONNECTION
    httpTemp.end();
    httpHum.end();
    httpAQ.end();
  } else {
    Serial.println("WiFi Connection Fail");
  }
  delay(1000);  //SEND REQUEST EVERY 10 SECONDS
}
