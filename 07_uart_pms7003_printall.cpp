/* 
 * Created by J. Yun, SCH Univ.
 * Read a dust sensor (PMS 7003) via USB-to-TTL convertor (PL2303)
 * Need to modify the path to USB port (e.g., /dev/ttyUSB0)
 * Just print all received data
 */

#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]){
    int dust;

    if ((dust = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY)) < 0){
        perror("UART: Failed to open the file.\n");
        return -1;
    }
    struct termios options;
    tcgetattr(dust, &options);
    options.c_cflag = B9600 | CS8 | CREAD | CLOCAL;
    options.c_iflag = IGNPAR | ICRNL;
    tcflush(dust, TCIFLUSH);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);  // make reads non-blocking
    tcsetattr(dust, TCSANOW, &options);

    unsigned char data[32];

    while (1) {
        if (read(dust, data, 32) > 0) {
            for (int i = 0; i < 16; i++) {
                cout << hex << setw(2) << setfill('0') << (int)data[i] << " ";
            }
            cout << endl;
            // for (int i = 0; i < 16; i++) {
            //      printf("%02x ", data[i]);
            // }
            // cout << endl;
            for (int i = 16; i < 32; i++) {
                cout << hex << setw(2) << setfill('0') << (int)data[i] << " ";
            }
            cout << endl;
            // for (int i = 16; i < 32; i++) {
            //     printf("%02x ", data[i]);
            // }
            // cout << endl;
            usleep(1000000);
        }
    }

    close(dust);
    return 0;
}
