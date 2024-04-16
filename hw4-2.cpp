#include <stdio.h>
#include <wiringPi.h>
#include <mcp3004.h>

#define BASE 200
#define SPI_CHAN 0

#define LED_GPIO1      4      
#define LED_GPIO2      12
#define LED_GPIO3      27

int main(void) {
    pinMode(LED_GPIO1, OUTPUT);            // the LED
    digitalWrite(LED_GPIO1, LOW);         // LED is off

    pinMode(LED_GPIO2, OUTPUT);            // the LED
    digitalWrite(LED_GPIO2, LOW);

    pinMode(LED_GPIO3, OUTPUT);            // the LED
    digitalWrite(LED_GPIO3, LOW);

    wiringPiSetupGpio();

    mcp3004Setup(BASE, SPI_CHAN);

    int val;

    while (1) {
        val = analogRead(BASE);

        if (val < 50 && val >= 0) {
            cout << "RED ON" << endl;
            digitalWrite(LED_GPIO1, HIGH);
            digitalWrite(LED_GPIO2, LOW);
            digitalWrite(LED_GPIO3, LOW);
        }
        else if (val < 512 && val >= 50) {
            cout << "GREEN ON" << endl;
            digitalWrite(LED_GPIO2, HIGH);
            digitalWrite(LED_GPIO1, LOW);
            digitalWrite(LED_GPIO3, LOW);
        }
        else if (val <= 900 && val >= 512) {
            cout << "BLUE ON" << endl;
            digitalWrite(LED_GPIO3, HIGH);
            digitalWrite(LED_GPIO1, LOW);
            digitalWrite(LED_GPIO2, LOW);
        }
        else {
            cout << "LED OFF" << endl;
            digitalWrite(LED_GPIO1, LOW);
            digitalWrite(LED_GPIO2, LOW);
            digitalWrite(LED_GPIO3, LOW);
        }
        delay(100);
    }


}
