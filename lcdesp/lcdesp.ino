
#include <WiFi.h>

#include <WiFiUdp.h>

#include <NTPClient.h>

#include <LiquidCrystal_I2C.h>


WiFiUDP ntpUDP;
NTPClient temps(ntpUDP, "fr.pool.ntp.org" ,0, 60000);
const char* ssid = "Penda_hakim";
const char* password =  "cypher007@zaco06";
String heure =temps.getFormattedTime();

// set the LCD number of columns and rows
int lcdColumns = 20;
int lcdRows = 4;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup(){
    // initialize LCD
    lcd.init();
    // turn on LCD backlight                      
    lcd.backlight();
    Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000); 

  }
    Serial.println("\nConnected to the WiFi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop(){
  if ((WiFi.status() == WL_CONNECTED)) //Check the current connection status
  {
    Serial.println("You can try to ping me");
     Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
    //Update de l'heure  

  
  }
    temps.update();
  String heure =temps.getFormattedTime();
   Serial.print(heure);
  lcd.setCursor(0,0);
  lcd.print("Heure ");
  lcd.print(heure);
  lcd.setCursor(0,1);
  lcd.print(" temperature: ");
  lcd.print("24°C");
  lcd.setCursor(1,2);
  lcd.print(" Humidité: ");
  lcd.print("68%");
   delay(1000);
}
