/*
   Four channels but could easliy be made to cope with more.
   Don't use this in conjunction with radio module - interrupt clashes! Use the Accurateppm routine instead.
   For Nano Every (Which has the advantage of having several serial ports in hardware)(I have also had problems with clones stopping working and requiring sketch to be reloaded.)
   Arduino serial data default is, serial baud rate (9600) and 8 data bits, no parity,no stop,LSB and not inverted - the default
*/

/*
   Simple example using the ppmHandler library
   Written by David Vella, Apr 2020
   https://github.com/David-Vella/ppm-handler
*/
