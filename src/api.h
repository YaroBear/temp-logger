#ifndef API_H
#define API_H

#include <ESP8266WebServer.h>
#include "config.h"
#include "data.h"

ESP8266WebServer server(80);

void handleConfig() {
  if (server.method() == HTTP_PUT) {
    String temperatureUnit = server.arg("temperatureUnit");

    if (temperatureUnit == "f") {
      setTemperatureUnit(tempUnit::fahrenheit);
    }

    if (temperatureUnit == "c" ) {
      setTemperatureUnit(tempUnit::celsius);
    }

    // Send a response indicating success
    server.send(200, "text/plain", "Configuration updated successfully");
  } else {
    // Send a response indicating unsupported method
    server.send(405, "text/plain", "Method Not Allowed");
  }
}

void handleData() {
  if (server.method() == HTTP_GET) {
    // Retrieve the temperature readings from the data.h file
    String readings = getData();

    // Send the readings in JSON format as the response
    server.send(200, "application/json", readings);
  } else {
    // Send a response indicating unsupported method
    server.send(405, "text/plain", "Method Not Allowed");
  }
}

void setupAPI() {
  // Configure the API endpoints
  server.on("/config", handleConfig);
  server.on("/data", handleData);

  // Start the server
  server.begin();
}

void handleAPI() {
  // Handle incoming client requests
  server.handleClient();
}

#endif