/*
   For Nano Every (Which has the advantage of having several serial ports in hardware)(I have also had problems with clones stopping working and requiring sketch to be reloaded.)
   Four channels but could easliy be made to cope with more.
   Arduino serial data default is, serial baud rate (9600) and 8 data bits, no parity,no stop,LSB and not inverted - the default

*/

/*
   Simple example using the ppmHandler library
   Written by David Vella, Apr 2020
   https://github.com/David-Vella/ppm-handler
*/

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
  Serial1.begin(9600); // Was 57600, 9600

  Serial1.println("Wake-up Serial1 port!");
  delay(1000); // We wait 1 second

  // Associate and instance of the ppmHandler with a physical pin
  assignPpmHandlerToPin(ppm, pin); // Pin 2 usually

}

void loop()
{
  // Must be called at least once after assigning a handler to a pin.
  // Recommended to include in loop for noise immunity
  ppm.sync();

  // Use to handler.get(channel number) to get the pulse width a ppm channel.
  // The channel numbers are integers 1 - 6
  for (int i = 1; i <= 6; ++i)
  {
    rudder = ppm.get(1); //rudder =1,stern planes =2, throttle =3, dive =4
    rudder = (rudder - 700) / 3; // Adjust range
    stern_plane = ppm.get(2);
    stern_plane = (stern_plane - 700) / 3; // Adjust range
    throttle = ppm.get(3);
    throttle = (throttle - 700) / 3; // Adjust range
    dive  = ppm.get(4);
    dive = (dive - 700) / 3; // Adjust range

    //Test
    //rudder = 250;

    Serial.print(rudder);
    Serial.print(' ');
    Serial.print(stern_plane);
    Serial.print(' ');
    Serial.print(throttle);
    Serial.print(' ');
    Serial.print(dive);
    Serial.print('\n'); // new line

  }
  // Serial.println();
  //delay(1000);

  // Print the voltage sensor value to Serial1
  Serial1.print('\<'); // new line
  Serial1.print("Test");
  Serial1.print('\,'); // commma
  Serial1.print(rudder);
  Serial1.print('\,'); // commma
  Serial1.print(stern_plane);
  Serial1.print('\,'); // commma
  Serial1.print(throttle);
  Serial1.print('\,'); // commma
  Serial1.print(dive);
  Serial1.print('\>'); // new line

  delay (200); //RDF was 200

  //delay (200); //
  //delay(10); // We wait 10mS to print the next value

  //Test
  //Serial1.print("RDF");
  //Serial1.print('\n'); // new line
  //delay(100); // RDF was 1000. We wait to print the next value

}
