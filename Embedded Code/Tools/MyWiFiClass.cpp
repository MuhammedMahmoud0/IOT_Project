#include "MyWiFiClass.h"

MyWiFiClass::MyWiFiClass(const char* ssid, const char* password, LiquidCrystal_I2C& lcd)
    : ssid(ssid), password(password), lcd(lcd) {}

// Function to connect to the Wi-Fi network.
void MyWiFiClass::connect() {
    // Print connecting to on the LCD and in the Serial Monitor
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    lcd.print("Connecting to ");
    lcd.setCursor(0, 1);
    lcd.print(ssid);

    // Begin the Wi-Fi connection
    WiFi.begin(ssid, password);

    // Print dots until the connection is established
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        lcd.print(".");
    }
    lcd.clear();

    // Print the connected message in the Serial Monitor and on the LCD as well as the IP address
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi connected");
    delay(500);
    lcd.clear();
    lcd.print("IP address: ");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
    delay(500);
}

// Function to reconnect to the Wi-Fi network.
void MyWiFiClass::reconnect() {
    if (WiFi.status() != WL_CONNECTED) {
        connect();
    }
}