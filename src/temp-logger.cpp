#include <NTPClient.h>
#include <WiFiUdp.h>

#include "config.h"
#include "api.h"
#include "network.h"
#include "sensor.h"
#include "data-timer.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

const char *ssid = "";
const char *password = "";

void setup() {
  Serial.begin(115200);

  SPIFFS.begin();
  connectToWiFi(ssid, password);
  setupSensor();
  setupAPI();
  timeClient.begin();
}

void loop() {
  timeClient.update();

  handleAPI();

  if (shouldRecord()) {
    float temperature = readTemperature();
    saveData(temperature, timeClient.getEpochTime());
  }
}