#include <WiFi.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

const char* serverName ="https://baj3n.herokuapp.com/api/device/";
StaticJsonDocument<500> doc;
StaticJsonDocument<500> docSensor;
RTC_DATA_ATTR int bootCount = 0;  
int smokeA0 = 35;
int AirPolution =300;
void setup() {
 Serial.begin(9600);
  // put your setup code here, to run once:
   WiFi.begin("ZACO", "cypher007@zaco06");
    Serial.println("Waiting for Connection");
   while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


 getDevice();
  Serial.println("Posting...");
  POSTDevice();
 // serializeJsonPretty(doc, Serial);
  Serial.println("\nDone.");
//Serial.println(nombre);
// Serial.println(IdBox);
 
}
void PostSensor(){

      if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");

      String json;
      serializeJson(docSensor, json);

      Serial.println(json);
      int httpResponseCode = http.POST(json);
      delay(1000);
      Serial.println(httpResponseCode);
}
}

void POSTDevice(){
      
      if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");

      String json;
      serializeJson(docSensor, json);

      Serial.println(json);
      int httpResponseCode = http.POST(json);
      Serial.println(httpResponseCode);

      }
}

int getCga(){
  int cga = 168;
//int cga = analogRead(35);
 int ValueAQMap = map(cga,0,4095,0,1024);
  Serial.print("Pin A0: ");
  Serial.println(cga);
  
  return cga;
  docSensor["sensor"]["cga"] = cga;
  docSensor["sensor"]["humidity"] = cga;
  docSensor["sensor"]["temperature"] = cga;
  docSensor["sensor"]["pm"] = cga;
  
}

  void getDevice()
{

    esp_sleep_wakeup_cause_t wakeup_reason;
    wakeup_reason = esp_sleep_get_wakeup_cause();

    uint64_t chipid=ESP.getEfuseMac();//The chip ID is essentially its MAC address(length: 6 bytes).
    Serial.printf("***ESP32 Chip ID = %04X%08X\n",(uint16_t)(chipid>>32),(uint32_t)chipid);//print High 2 bytes
    char buffer[200];
    sprintf(buffer, "%04X%08X",(uint16_t)(chipid>>32),(uint32_t)chipid);
    //sprintf(buffer, "esp32%" PRIu64, ESP.getEfuseMac());

    // int vbatt_raw = 0;
    // for (int i=0;i<SAMPLES;i++)
    // {
    //    vbatt_raw += analogRead(PIN_POWER);
    //    delay(100);
    // }
    // vbatt_raw = vbatt_raw/SAMPLES;
    //float vbatt = map(vbatt_raw, 0, 4096, 0, 4200);

    docSensor["ip"] = WiFi.localIP().toString();
    docSensor["rssi"] = String(WiFi.RSSI());
    docSensor["chipid"] = buffer;
 

}
void loop() {
  /*getCga();
Serial.println("Posting Sensors...");
PostSensor(); 

  serializeJsonPretty(docSensor, Serial);
  Serial.println("\nDone.");
  Délai pour l'affichage */
  
  
//  Serial.println(Serial2.readString());

  // put your main code here, to run repeatedly:

}