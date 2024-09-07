#include "RainSensor.h"

// Constructor that calls the base class constructor.
RainSensor::RainSensor(int p, bool type) : Sensor(p, type) {}

// Method to return the rain level based on the sensor value.
int RainSensor::getRainLevel() {
    int value = read(); // Read the value using the inherited read() method.

    // Map the analog value (0-4095) to a percentage (100-0).
    int mappedValue = map(value, 0, 4095, 100, 0);
    
    return mappedValue;
}
