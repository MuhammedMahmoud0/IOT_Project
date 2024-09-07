#include "GasSensor.h"

// Constructor that calls the base class constructor.
GasSensor::GasSensor(int p, bool type) : Sensor(p, type) {}

// Method to return the Gas level based on the sensor value.
int GasSensor::getGasLevel() {
    int value = read(); // Read the value using the inherited read() method.
    
    if (value>=2600){ // Return true if the reading exceeds 2600
        return 1;
    } else {
        return 0;
    }
}
