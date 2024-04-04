#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
using namespace std;

#define LED_GPIO1      13      // this is GPIO17, Pin 11
#define LED_GPIO2      18
#define LED_GPIO3      27
#define BUTTON_GPIO1   17      // this is GPIO27, Pin 13
#define BUTTON_GPIO2   19
#define BUTTON_GPIO3   26

// the Interrupt Service Routine (ISR) to light the LED
void lightLED1(void) {
    static int x = 1;
    if (x / 2 != 0) {
        digitalWrite(LED_GPIO1, HIGH);         // turn the LED on
        cout << "led1 " << x++ << endl;
    }
    else {
        digitalWrite(LED_GPIO1, LOW);
    }
}

void lightLED2(void) {
    static int x = 1;
    if (x / 2 != 0) {
        digitalWrite(LED_GPIO2, HIGH);         // turn the LED on
        cout << "led2 " << x++ << endl;
    }
    else {
        digitalWrite(LED_GPIO2, LOW);
    }
}

void lightLED3(void) {
    static int x = 1;
    if (x / 2 != 0) {
        digitalWrite(LED_GPIO3, HIGH);         // turn the LED on
        cout << "led3 " << x++ << endl;
    }
    else {
        digitalWrite(LED_GPIO3, LOW);
    }
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
