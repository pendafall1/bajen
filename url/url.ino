const char* sensorTemp = "TC"; //SENSOR ID - example temperatureSensor_1
const char* sensorHum = "1";
const char* sensorAQ = "AQ";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
    //PARSING URL PATH FOR Temperature
  String url = "/api/v2/devices/ck-device/sensors/";
  String urlTemp;
  urlTemp += sensorTemp;
  urlTemp += "/value";
  //PARSING URL PATH FOR Humidity 
    String urlHum = url + sensorHum + "/value";
 // urlHum += devID;
 // urlHum += "/sensors/";
  //urlHum += sensorHum;
  //urlHum += "/value";
 //PARSING URL PATH FOR Air_Qality
    String urlAQ = url + sensorAQ + "/value";
  //urlAQ += devID;
  //urlAQ += "/sensors/";
 // urlAQ += sensorAQ;
 // urlAQ += "/value";
  Serial.println(urlAQ);
delay(1000);
}
