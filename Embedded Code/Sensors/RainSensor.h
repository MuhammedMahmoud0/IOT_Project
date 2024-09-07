#ifndef RAINSENSOR_H
#define RAINSENSOR_H

#include "Sensor.h"

class RainSensor : public Sensor {
public:
    // Constructor to initialize the RainSensor using the Sensor constructor.
    RainSensor(int p, bool type);

    // Method to get Rain level.
    int getRainLevel();
};

#endif // RAINSENSOR_H.
