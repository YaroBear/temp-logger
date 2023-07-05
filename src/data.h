#include <ArduinoJson.h>
#include <FS.h>
#include "config.h"

void saveData(float temperature, unsigned long timestamp) {
  File file = SPIFFS.open("/data.json", "w");

  if (!file) {
    Serial.println("failed to open /data.json for writing");
  }

  StaticJsonDocument<128> doc;

  doc["sensor"] = "temp";
  doc["units"] = tempUnitStr[currentTempUnit];
  doc["temperature"] = temperature;
  doc["timestamp"] = timestamp;

  String jsonString;
  serializeJson(doc, jsonString);

  file.print(jsonString);

  file.close();
}

String getData() {
  File file = SPIFFS.open("/data.json", "r");

  if (!file) {
    Serial.println("failed to open /data.json for reading");
  }
  
  StaticJsonDocument<200> doc;
  
  String jsonString = file.readString();
  DeserializationError error = deserializeJson(doc, jsonString);
  file.close();
  
  if (error) {
    Serial.print("Parsing failed: ");
    Serial.println(error.c_str());
    return "";
  }
  
  return jsonString;
}