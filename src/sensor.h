#ifndef SENSOR_H
#define SENSOR_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include "config.h"

#define ONE_WIRE_BUS D2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setupSensor() {
  sensors.begin();
}

float readTemperature() {
  sensors.requestTemperatures();
  if (currentTempUnit == tempUnit::celsius) {
    return sensors.getTempCByIndex(0);
  }
  return sensors.getTempFByIndex(0);
}

#endif 