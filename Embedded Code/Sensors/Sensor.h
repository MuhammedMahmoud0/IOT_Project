#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <PubSubClient.h>

class Sensor {
private:
    int pin;
    bool readType; // true for analogRead, false for digitalRead.

public:
    // Constructor to initialize pin and readType.
    Sensor(int p, bool type);

    // Function to read from the sensor.
    int read();
};
// Function to publish sensor data.
void publishSensorData(PubSubClient& client, const char* topic, int value);

#endif // SENSOR_H.