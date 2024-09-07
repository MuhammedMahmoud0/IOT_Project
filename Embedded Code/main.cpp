// Include the needed libraries.
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <LiquidCrystal_I2C.h>

// Include the sensors' classes from "Sensors" folder.
#include "Sensors/RainSensor.h"
#include "Sensors/DHTSensor.h"
#include "Sensors/GasSensor.h"
#include "Sensors/FlameSensor.h"
#include "Sensors/UVSensor.h"

// Include the warning classes from "Tools" folder.
#include "Tools/Warning.h"
#include "Tools/MyWiFiClass.h"
#include "Tools/MQTTClass.h"

// Define the Touch button pins.
#define BUTTON_UP_PIN 12
#define BUTTON_DOWN_PIN 13

// Define the output devices' pins.
#define RED_LED 14
#define GREEN_LED 2
#define YELLOW_LED 23
#define BUZZER_PIN 18

// Define the input devices' pins.
#define DHT_PIN 4
#define GAS_SENSOR_PIN 35
#define FLAME_SENSOR_PIN 33
#define UV_SENSOR_PIN 34
#define RAIN_SENSOR_PIN 36

// Define the type for "DHT" sensor.
#define DHT_TYPE DHT11

// Call the constructor for each sensor and set true for "Analog" connection or false for "digital".
DHTSensor dhtSensor(DHT_PIN, true);
GasSensor gasSensor(GAS_SENSOR_PIN, true);
FlameSensor flameSensor(FLAME_SENSOR_PIN, false);
UVSensor uvSensor(UV_SENSOR_PIN, true);
RainSensor rainSensor(RAIN_SENSOR_PIN, true);

// Create an object for LCD and DHT.
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHT_PIN, DHT_TYPE);

// MQTT topics for each sensor and buzzer.
const char* temp_topic = "esp32/temperature";
const char* humidity_topic = "esp32/humidity";
const char* gas_topic = "esp32/gas";
const char* flame_topic = "esp32/flame";
const char* uv_topic = "esp32/uv";
const char* rain_topic = "esp32/rain";
const char* buzzer_topic = "esp32/buzzer";

// Variable to hold the frequency of the buzzzer, default value set to 1000 hz.
int frequency = 1000;

// WiFi credentials.
const char* ssid = "WE_F321D4";
const char* password = "m4602962@";

// MQTT broker and credentials.
const char* mqtt_server = "480ad17d3ac146b38c39effc11356cae.s1.eu.hivemq.cloud";
const char* mqtt_user = "ESP32";
const char* mqtt_password = "Esp322026@";
const int mqtt_port = 8883;

// Root CA certificate.
const char* root_ca = \
"-----BEGIN CERTIFICATE-----\n" \
"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\n" \
"-----END CERTIFICATE-----";

// Create an WiFiClass object.
MyWiFiClass wifi(ssid, password, lcd);

// Create an MQTTClass object.
MQTTClass mqtt(mqtt_server, mqtt_port, mqtt_user, mqtt_password, root_ca, lcd, buzzer_topic);

void callback(char* topic, byte* payload, unsigned int length) {
  // Print on message arrival
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  // Create a null-terminated string from the payload
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0';

  Serial.print("Received message: ");
  Serial.println(message);

  // Check if the incoming message is for controlling the frequency of the buzzer
  if (strcmp(topic, buzzer_topic) == 0) {
    frequency = atoi(message);  // Convert the message to an integer
    Serial.print("Received Frequency: ");
    Serial.println(frequency);
  }
}

void setup() {
  // Set the communication baud rate to 115200.
  Serial.begin(115200);

  // Initialize the LCD and turn on the backlight.
  lcd.init();
  lcd.backlight();

  // Print a Power On message on the LCD.
  lcd.print("Power On");
  delay(500);
  lcd.clear();

  // Initialize DHT sensor.
  dht.begin();

  // Configure touch button pins.
  pinMode(BUTTON_UP_PIN, INPUT);
  pinMode(BUTTON_DOWN_PIN, INPUT);

 // Configure touch LED and buzzer pins.
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BUZZER_PIN,OUTPUT);

  // Configure the sensor pins.
  pinMode(GAS_SENSOR_PIN, INPUT);
  pinMode(FLAME_SENSOR_PIN, INPUT);
  pinMode(UV_SENSOR_PIN, INPUT);
  pinMode(RAIN_SENSOR_PIN, INPUT);

  // Connect to WiFi using the MyWiFiClass
  wifi.connect();

  // Initialize MQTT connection
  mqtt.setCallback(callback);
  
  // Connect to the MQTT broker using the MQTTCLass
  mqtt.connect();
}

// Variable to hold the page currently displayed on the screen.
int currentPage = 0;

void loop() {
  // Ensure MQTT connection in each loop via mqtt.reconnect().
  if (!mqtt.getClient().connected()) {
    mqtt.reconnect();
  }
  mqtt.loop();

  // Create an object for the warning and give it the output devices.
  Warning warningSystem(GREEN_LED, RED_LED, YELLOW_LED, BUZZER_PIN, frequency);
  
  // Read sensor data.
  float humidity = dhtSensor.getHumidityLevel();
  float temperature = dhtSensor.getTemp();
  int gasValue = gasSensor.getGasLevel();
  int flameValue = flameSensor.getFlameLevel();
  int uvValue = uvSensor.getUVLevel();
  int rainValue = rainSensor.getRainLevel();
  
  // Give the warning's "check" function the sensors' readings.
  warningSystem.check(gasValue, flameValue);

  // Publish sensor data to MQTT topics.
  publishSensorData(mqtt.getClient(), temp_topic, temperature);
  publishSensorData(mqtt.getClient(), humidity_topic, humidity);
  publishSensorData(mqtt.getClient(), gas_topic, gasValue);
  publishSensorData(mqtt.getClient(), flame_topic, flameValue);
  publishSensorData(mqtt.getClient(), uv_topic, uvValue);
  publishSensorData(mqtt.getClient(), rain_topic, rainValue);

  lcd.clear();

  // Display different sensor readings on an LCD screen based on the current page
  switch (currentPage) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("1. Temp:");
      lcd.print(temperature);
      lcd.print("C");
      lcd.setCursor(0, 1);
      if (temperature < 0) {
          lcd.print("Cold Warning!!");
      } else if (temperature > 40) {
          lcd.print("Heat Warning!!");
      } else {
          lcd.print("Normal");
      }
      break;

    case 1:
      lcd.setCursor(0, 0);
      lcd.print("2. Hum:");
      lcd.print(humidity);
      lcd.print("%");
      lcd.setCursor(0, 1);
      if (humidity < 20) {
          lcd.print("Too Low!");
      } else if (humidity > 80) {
          lcd.print("Too High!");
      } else {
          lcd.print("Normal");
      }
      break;

    case 2:
      lcd.setCursor(0, 0);
      lcd.print("3. Gas: ");
      lcd.print(gasValue ? "Gas Leak Detected!!" : "Safe");
      break;

    case 3:
      lcd.setCursor(0, 0);
      lcd.print("4. Flame Detect:");
      lcd.setCursor(0, 1);
      lcd.print(flameValue ? "Fire Warning!!" : "Safe");
      break;

    case 4:
      lcd.setCursor(0, 0);
      lcd.print("5. UV Index:");
      lcd.print(uvValue);
      lcd.setCursor(0, 1);
      if (uvValue > 10) {
          lcd.print("Extreme UV!");
      } else if (uvValue > 8) {
          lcd.print("High UV");
      } else if (uvValue > 3) {
          lcd.print("Moderate UV");
      } else {
          lcd.print("Low UV");
      }
      break;

    case 5:
      lcd.setCursor(0, 0);
      lcd.print("6. Rain Level:");
      lcd.setCursor(0, 1);
      lcd.print(rainValue);
      break;

    // handle unexpected currentPage values
    default:
    lcd.setCursor(0, 0);
    lcd.print("Invalid Page");
    break;
  }

  // Check if the UP button was pressed
  if (digitalRead(BUTTON_UP_PIN) == HIGH) {
    Serial.println("Button UP pressed");
    if (currentPage > 0) {
      currentPage--;
    } else if (currentPage == 0){
      currentPage = 5;
    }
    delay(200); // Debounce delay
  }

  // Check if the DOWN button was pressed
  if (digitalRead(BUTTON_DOWN_PIN) == HIGH) {
    Serial.println("Button DOWN pressed");
    if (currentPage < 5) {
      currentPage++;
      
    } else if (currentPage == 5){
      currentPage = 0;
    }
    delay(200); // Debounce delay
  }
  delay(300);
}