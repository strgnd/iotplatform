#include <iostream>
#include <wiringPi.h>

using namespace std;
#define PIN_TRIG 23
#define PIN_ECHO 24
#define LED_GPIO1      4      
#define LED_GPIO2      17
#define LED_GPIO3      27


int main(int argc, char* argv[]) {
	wiringPiSetupGpio(); unsigned int T, L;
	pinMode(PIN_TRIG, OUTPUT); pinMode(PIN_ECHO, INPUT);

	pinMode(LED_GPIO1, OUTPUT);            // the LED
    	pinMode(BUTTON_GPIO1, INPUT);          // the Button
    	digitalWrite(LED_GPIO1, LOW);         // LED is off

    	pinMode(LED_GPIO2, OUTPUT);            // the LED
    	pinMode(BUTTON_GPIO2, INPUT);          // the Button
    	digitalWrite(LED_GPIO2, LOW);

    	pinMode(LED_GPIO3, OUTPUT);            // the LED
    	pinMode(BUTTON_GPIO3, INPUT);          // the Button
    	digitalWrite(LED_GPIO3, LOW);

	while (1) {
		digitalWrite(PIN_TRIG, LOW); delayMicroseconds(2);
		digitalWrite(PIN_TRIG, HIGH); delayMicroseconds(20);
		digitalWrite(PIN_TRIG, LOW);

		while (digitalRead(PIN_ECHO) == LOW);

		unsigned int startTime = micros();

		while (digitalRead(PIN_ECHO) == HIGH);
		T = micros() - startTime;
		L = T / 58.2;


		if (L > 0 && L < 10) {
			cout << "RED ON" << endl;
			digitalWrite(LED_GPIO1, HIGH);
			digitalWrite(LED_GPIO2, LOW);
			digitalWrite(LED_GPIO3, LOW);
		}
		else if (L >= 10 && L < 15) {
			cout << "GREEN ON" << endl;
			digitalWrite(LED_GPIO2, HIGH);
			digitalWrite(LED_GPIO1, LOW);
			digitalWrite(LED_GPIO3, LOW);
		}
		else if (L >= 15 && L < 30) {
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
		delay(50);
	}
}
