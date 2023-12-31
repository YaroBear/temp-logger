#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

enum tempUnit
{
  fahrenheit,
  celsius
};

const char * const tempUnitStr[] =
{
    [fahrenheit] = "f",
    [celsius] = "c"
};

tempUnit currentTempUnit = tempUnit::fahrenheit;

void setTemperatureUnit(tempUnit temperatureUnit) {
  currentTempUnit = temperatureUnit;
}

#endif  // CONFIG_H