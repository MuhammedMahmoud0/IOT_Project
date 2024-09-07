#ifndef WARNING_H
#define WARNING_H

class Warning {
public:
    // Constructor to initialize the pins of the LEDs and buzzer.
    Warning(int greenLedPin, int redLedPin, int yellowLedPin, int buzzerPin, int frequency);
    // Method to check the sensor values and trigger the warning system.
    void check(int gasValue, int flameValue);

private:
    // Declare the needed variables
    int greenLedPin;
    int redLedPin;
    int yellowLedPin;
    int buzzerPin;
    int frequency;
};

#endif // WARNING_H.
