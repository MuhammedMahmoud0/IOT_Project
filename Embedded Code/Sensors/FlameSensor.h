#ifndef FLAMESENSOR_H
#define FLAMESENSOR_H

#include "Sensor.h"

class FlameSensor : public Sensor {
public:
    // Constructor to initialize the RainSensor using the Sensor constructor.
    FlameSensor(int p, bool type);

    // Method to get Flame level.
    int getFlameLevel();
};

#endif // RAINSENSOR_H.
