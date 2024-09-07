#ifndef GASSENSOR_H
#define GASSENSOR_H

#include "Sensor.h"

class GasSensor : public Sensor {
public:
    // Constructor to initialize the RainSensor using the Sensor constructor.
    GasSensor(int p, bool type);

    // Method to get Gas level.
    int getGasLevel();
};

#endif // RAINSENSOR_H.
