#include <ArduinoJson.h>
#include <FS.h>

void saveData(float temperature, unsigned long timestamp) {
  File file = SPIFFS.open("/data.json", "a");
  
  StaticJsonDocument<200> doc;
  
  doc["temperature"] = temperature;
  doc["timestamp"] = timestamp;
  
  String jsonString;
  serializeJson(doc, jsonString);
  
  file.println(jsonString);
  
  file.close();
}

String getData() {
  File file = SPIFFS.open("/data.json", "r");
  
  StaticJsonDocument<200> doc;
  
  String jsonString = file.readString();
  DeserializationError error = deserializeJson(doc, jsonString);
  
  if (error) {
    Serial.print("Parsing failed: ");
    Serial.println(error.c_str());
    return "";
  }
  
  String dataString;
  serializeJson(doc, dataString);
  
  file.close();
  
  return dataString;
}