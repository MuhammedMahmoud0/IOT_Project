#include "Warning.h"
#include <Arduino.h>

Warning::Warning(int greenLedPin, int redLedPin, int yellowLedPin, int buzzerPin, int frequency)
    : greenLedPin(greenLedPin), redLedPin(redLedPin), yellowLedPin(yellowLedPin), buzzerPin(buzzerPin), frequency(frequency) {
    pinMode(greenLedPin, OUTPUT);
    pinMode(redLedPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);

    // Initialize the LEDC peripheral
    ledcSetup(0, frequency, 8);
    ledcAttachPin(buzzerPin, 0);
}

// Method to check the sensor values and trigger the warning system.
void Warning::check(int gasValue, int flameValue) {
    // Warning triggers if the readings of the sensors are true.
    if (gasValue == 1 || flameValue == 1) {
        digitalWrite(greenLedPin, LOW);
        tone(buzzerPin, frequency);
        // Different LED light up depending on the cause of the warning.
        if (gasValue == 1){
            digitalWrite(yellowLedPin, HIGH);
        }
        if (flameValue == 1){
            digitalWrite(redLedPin, HIGH);
        }
    } else {
        // Otherwise in the safe state, green LED turn on and the rest off along with the buzzer.
        digitalWrite(greenLedPin, HIGH);
        digitalWrite(redLedPin, LOW);
        digitalWrite(yellowLedPin, LOW);
        noTone(buzzerPin);
        digitalWrite(buzzerPin, LOW);
    }
}
