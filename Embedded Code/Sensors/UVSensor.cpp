#include "UVSensor.h"

// Constructor that calls the base class constructor.
UVSensor::UVSensor(int p, bool type) : Sensor(p, type) {}

// Method to return the uv level based on the sensor value.
int UVSensor::getUVLevel() {
    int value = read(); // Read the value using the inherited read() method.

    // Map the analog value (0-4095) to a level from (0 to 15).
    int mappedValue = map(value, 0, 4095, 0, 15);
    
    return mappedValue;
}