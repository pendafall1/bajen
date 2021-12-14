#include <NTPClient.h>

#include <WiFi.h>;

const char* ssid = "Penda_hakim";
const char* password =  "cypher007@zaco06";
WiFiUDP ntpUDP;
NTPClient temps(ntpUDP, "fr.pool.ntp.org" ,0, 60000);
int heure = temps.getHours();
int minute = temps.getMinutes();
int seonde = temps.getSeconds();
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500); 
  }
 
  Serial.println("\nConnected to the WiFi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  if ((WiFi.status() == WL_CONNECTED)) //Check the current connection status
  {
    Serial.println("You can try to ping me");
     Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
    //Update de l'heure  
  temps.update();
//L'heure est envoyée sur le port serie au format 00:00:00 en 1 fois 
  Serial.println(temps.getFormattedTime());
//L'heure est envoyée en 3 fois (heure puis minutes puis secondes)

 
    delay(1000);
  }
  else
  {
    Serial.println("Connection lost");
  }
}
