#ifndef UVSENSOR_H
#define UVSENSOR_H

#include "Sensor.h"

class UVSensor : public Sensor {
public:
    // Constructor to initialize the UVSensor using the Sensor constructor.
    UVSensor(int p, bool type);

    // Method to get UV level.
    int getUVLevel();
};

#endif // UVSENSOR_H.