#include <ppmHandler.h>

// Arduino pin connected to ppm signal
// NOTE: this pin must support interrupts.
// On ATmega328 based boards these should be pins 2 and 3
// Check the data sheet for your specific board
// RDF change number of channels in ppmHandler.h to 8
const int pin = 2;

int rudder;
int stern_plane;
int throttle;
int dive;

// Create and instance of the ppmHandler class
ppmHandler ppm;

void setup()
{

  // Open USB serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Wake-up-you Serial usb port!");
  delay(1000); // We wait 1 second

  // Open second hardware serial port
  //Serial1.begin(9600);
  Serial1.begin(115200); // Was 57600, 9600

  Serial1.println("Wake-up Serial1 port!");
  delay(1000); // We wait 1 second

  // Associate and instance of the ppmHandler with a physical pin
  assignPpmHandlerToPin(ppm, pin); // Pin 2 usually

}
