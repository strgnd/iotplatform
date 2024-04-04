#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
using namespace std;

#define PWM_LED1       18      // this is PWM0, pin 12
#define PWM_LED2       13
bool running = true;          // fade in/out until button pressed

int main() {                             // must be run as root
    wiringPiSetupGpio();                  // use the GPIO numbering
    pinMode(PWM_LED1, PWM_OUTPUT);         // the PWM LED - PWM0
    pinMode(PWM_LED2, PWM_OUTPUT);
    
    pwmSetRange(2040);

    while (running) {
        for (int i = 1; i < 2040; i++) {       // Fade fully on
            pwmWrite(PWM_LED1, i);
            usleep(2040);
        }
        for (int i = 2039; i >= 0; i--) {       // Fade fully off
            pwmWrite(PWM_LED1, i);
            usleep(2040);
        }
        for (int i = 1; i < 2040; i++) {       // Fade fully on
            pwmWrite(PWM_LED2, i);
            usleep(2040);
        }
        for (int i = 2039; i >= 0; i--) {       // Fade fully off
            pwmWrite(PWM_LED2, i);
            usleep(2040);
        }
    }

    return 0;
}
