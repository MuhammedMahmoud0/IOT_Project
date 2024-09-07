#ifndef DHTSENSOR_H
#define DHTSENSOR_H

#include "Sensor.h"
#include <DHT.h>

class DHTSensor : public Sensor {
public:
    // Constructor to initialize the DHT sensor using the Sensor constructor.
    DHTSensor(int p, bool type);

    // Methods to get temperature and humidity levels.
    float getTemp();
    float getHumidityLevel();

private:
    DHT dht;  // DHT object as a member variable.
};

#endif // DHTSENSOR_H.