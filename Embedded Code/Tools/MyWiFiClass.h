#ifndef MYWIFICLASS_H
#define MYWIFICLASS_H

#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

class MyWiFiClass {
public:
    // Constructor to initialize the MyWiFiClass object with ssid, password and an LCD object for display
    MyWiFiClass(const char* ssid, const char* password, LiquidCrystal_I2C& lcd);
    // Function to connect to the Wi-Fi network.
    void connect();
    // Function to reconnect to the Wi-Fi network.
    void reconnect();

private:
    // Declare the needed variables
    const char* ssid;
    const char* password;
    LiquidCrystal_I2C& lcd;
};

#endif