#ifndef MQTTCLASS_H
#define MQTTCLASS_H

#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <LiquidCrystal_I2C.h>

class MQTTClass {
public:
    /*
    Constructor to initialize the MQTTClass object with server details, credentials, 
    the root certificate, an LCD object for display, and a topic to subscribe to.
    */ 
    MQTTClass(const char* server, int port, const char* user, const char* password, const char* root_ca, LiquidCrystal_I2C& lcd, const char* topic_to_subscribe);
    // Function to connect to the MQTT broker.
    void connect();
    // Function to reconnect to the MQTT broker.
    void reconnect();
    // Function to set the callback function.
    void setCallback(MQTT_CALLBACK_SIGNATURE);
    // Function to loop the client.
    void loop();
    // Function to return the client object.
    PubSubClient& getClient();

private:
    // Declare the needed variables
    const char* server;
    int port;
    const char* user;
    const char* password;
    const char* root_ca;
    const char* topic_to_subscribe;
    LiquidCrystal_I2C& lcd;
    WiFiClientSecure espClient;
    PubSubClient client;
};

#endif