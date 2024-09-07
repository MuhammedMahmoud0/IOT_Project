#include "MQTTClass.h"

MQTTClass::MQTTClass(const char* server, int port, const char* user, const char* password, const char* root_ca, LiquidCrystal_I2C& lcd, const char* topic_to_subscribe)
    : server(server), port(port), user(user), password(password), root_ca(root_ca), lcd(lcd), client(espClient) , topic_to_subscribe(topic_to_subscribe){
    // Set the certificate and server
    espClient.setCACert(root_ca);
    client.setServer(server, port);
}

void MQTTClass::connect() {
    // If the connection is successful, print an appropriate message and subscribe to the topic
    if (client.connect("ESP32Client", user, password)) {
        lcd.clear();
        lcd.print("MQTT connected");
        Serial.println("MQTT connected");
        delay(200);
        lcd.clear();
        client.subscribe(topic_to_subscribe);
    } else {
        // If the connection is unsuccessful, print the failed state
        Serial.print("MQTT connection failed, rc=");
        Serial.print(client.state());
        lcd.clear();
        lcd.print("MQTT connect failed");
        delay(5000);
    }
}
// Check if the "ESP32" is connected to MQTT or not and try to connect again if it is not connected.
void MQTTClass::reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        connect();  // Attempt to connect using the connect method
        // If the connection is succesful, do nothing otherwise print the failed state
        if (client.connected()) {
              continue;
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            lcd.clear();
            lcd.print("MQTT retry in 5s");
            delay(5000);
        }
    }
}

// Function to set the callback function.
void MQTTClass::setCallback(MQTT_CALLBACK_SIGNATURE) {
    client.setCallback(callback);
}

// Function to loop the client.
void MQTTClass::loop() {
    client.loop();
}

// Function to return the client object.
PubSubClient& MQTTClass::getClient() {
    return client;
}