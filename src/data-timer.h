#ifndef DATA-TIMER_H
#define DATA-TIMER_H

#include "Arduino.h"

const int delayTime = 30000;
unsigned long startingTime = 0;

bool shouldRecord() {
    if (startingTime == 0) {
        startingTime = millis();
        return true;
    }

    unsigned long currentTime = millis();

    if (currentTime >= delayTime + startingTime) {
        startingTime = millis();
        return true;
    }

    return false;
}

#endif