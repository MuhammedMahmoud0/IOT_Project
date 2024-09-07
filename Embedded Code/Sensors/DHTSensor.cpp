#include "DHTSensor.h"

#define DHT_TYPE DHT11

// Constructor that calls the base class constructor and initializes the DHT object.
DHTSensor::DHTSensor(int p, bool type) : Sensor(p, type), dht(p, DHT_TYPE) {
    dht.begin();  // Initialize the DHT sensor.
}

// Method to return the temperature based on the DHT sensor value.
float DHTSensor::getTemp() {
    return dht.readTemperature();
}

// Method to return the humidity level based on the DHT sensor value.
float DHTSensor::getHumidityLevel() {
    return dht.readHumidity();
}
