#include "FlameSensor.h"

// Constructor that calls the base class constructor.
FlameSensor::FlameSensor(int p, bool type) : Sensor(p, type) {}

// Method to return the Flame level.
int FlameSensor::getFlameLevel() {
    int value = read();
    // If the sensor reading is 1, it returns 0 and vice versa.
    if (value==1){
        return 0;
    } else {
        return 1;
    }
}