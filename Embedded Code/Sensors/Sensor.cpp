#include <Arduino.h>
#include <PubSubClient.h>
#include "Sensor.h"

// Constructor to initialize pin and readType.
Sensor::Sensor(int p, bool type) : pin(p), readType(type){}

// Function to read from the sensor.
int Sensor::read() {
    if (readType) {
        return analogRead(pin); // Analog read.
    } else {
        return digitalRead(pin); // Digital read.
    }
}

// Function to publish sensor data.
void publishSensorData(PubSubClient& client, const char* topic, int value) {
    char payload[50];
    snprintf(payload, sizeof(payload), "%d", value);
    client.publish(topic, payload);
}
