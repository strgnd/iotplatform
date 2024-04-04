#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
using namespace std;
#define DEBOUNCE_TIME 200

#define LED_GPIO1      13      // this is GPIO17, Pin 11
#define LED_GPIO2      18
#define LED_GPIO3      27
#define BUTTON_GPIO1   17      // this is GPIO27, Pin 13
#define BUTTON_GPIO2   19
#define BUTTON_GPIO3   26

// the Interrupt Service Routine (ISR) to light the LED
void lightLED1(void) {
    static unsigned long lastISRTime = 0;
    unsigned long currentISRTime = millis();
    static int x1 = 1;
    if(currentISRTime – lastISRTime > DEBOUNCE_TIME) {
         if (x1 / 2 != 0) {
            digitalWrite(LED_GPIO1, HIGH);         // turn the LED on
            cout << "led1 on " << x1++ << endl;
        }
        else {
            digitalWrite(LED_GPIO1, LOW);
            cout << "led1 off" << x1++ <<endl;
        }
    }
    lastISRTime = currentISRTime;
}

void lightLED2(void) {
    static unsigned long lastISRTime = 0;
    unsigned long currentISRTime = millis();
    static int x2 = 1;
    if(currentISRTime – lastISRTime > DEBOUNCE_TIME) {
         if (x2 / 2 != 0) {
            digitalWrite(LED_GPIO1, HIGH);         // turn the LED on
            cout << "led1 on " << x2++ << endl;
        }
        else {
            digitalWrite(LED_GPIO1, LOW);
            cout << "led1 off" << x2++ <<endl;
        }
    }
    lastISRTime = currentISRTime;
}

void lightLED3(void) {
    static unsigned long lastISRTime = 0;
    unsigned long currentISRTime = millis();
    static int x3 = 1;
    if(currentISRTime – lastISRTime > DEBOUNCE_TIME) {
         if (x3 / 2 != 0) {
            digitalWrite(LED_GPIO1, HIGH);         // turn the LED on
            cout << "led1 on " << x3++ << endl;
        }
        else {
            digitalWrite(LED_GPIO1, LOW);
            cout << "led1 off" << x3++ <<endl;
        }
    }
    lastISRTime = currentISRTime;
}

int main() {                             // must be run as root
    wiringPiSetupGpio();                  // use the GPIO numbering
    
    pinMode(LED_GPIO1, OUTPUT);            // the LED
    pinMode(BUTTON_GPIO1, INPUT);          // the Button
    digitalWrite(LED_GPIO1, LOW);         // LED is off

    pinMode(LED_GPIO2, OUTPUT);            // the LED
    pinMode(BUTTON_GPIO2, INPUT);          // the Button
    digitalWrite(LED_GPIO2, LOW);

    pinMode(LED_GPIO3, OUTPUT);            // the LED
    pinMode(BUTTON_GPIO3, INPUT);          // the Button
    digitalWrite(LED_GPIO3, LOW);

    // call the lightLED() ISR on the rising edge (i.e., button press)
    wiringPiISR(BUTTON_GPIO1, INT_EDGE_RISING, &lightLED1);
    wiringPiISR(BUTTON_GPIO2, INT_EDGE_RISING, &lightLED2);
    wiringPiISR(BUTTON_GPIO3, INT_EDGE_RISING, &lightLED3);

    for(;;) { }

    return 0;                             // program ends after 10s
}
