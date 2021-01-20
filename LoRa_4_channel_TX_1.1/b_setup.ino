// For receiving and parsing seria data
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];   // temporary array for use when parsing

// variables to hold the parsed data
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
int integerFromPC1 = 0;
int integerFromPC2 = 0;
int integerFromPC3 = 0;
float floatFromPC = 0.0;

boolean newData = false;

// include the library
#include <RadioLib.h>

// SX1278 has the following connections:
// NSS or CS pin:   10
// DIO0 pin:  2
// RESET pin: 9
// DIO1 pin:  3
//SX1278 radio = new Module(10, 2, 9, 3);
/*  As module wired by RDF
          1 GND - Ground
          15 DIO1 I/O Digital I/O, software configured
          16 DIO2 I/O Digital I/O, software configured
          11 DIO3 I/O Digital I/O, software configured
  Ard 3.3v  Socket 10 LV  PCB no 1    13 VCC 3.3V - Supply voltage
  Ard D12 Socket 4  HV4   PCB no 2    2 MISO O SPI Data output
  Ard D11 Socket 3  HV3   PCB no 3    3 MOSI I SPI Data input
  Ard D13 Socket 5  HV2   PCB no 4    4 SCK I SPI Clock input
  Ard D04 Socket 2  HV1   PCB no 5    5 NSS or CS   I SPI Chip select input
  Ard D03 Socket 6  Direct  PCB no 6    14 DIO0 or GO  I/O Digital I/O, software configured
  Ard D02 Socket 1  Direct  PCB no 7    6 RESET I Reset trigger input
  Gnd Socket 8        8 GND - Ground
*/
SX1278 radio = new Module(4, 3, 9, 9);   // RDF Not sure about two final 9s ?

// or using RadioShield
// https://github.com/jgromes/RadioShield
//SX1278 radio = RadioShield.ModuleA;

// save transmission state between loops
int transmissionState = ERR_NONE;

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200); // Was 57600, 9600
  Serial.println("Data in");
  Serial.println();

  // initialize SX1278 with default settings
  Serial.print(F("[SX1278] Initializing ... "));
  int state = radio.begin();
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  // set the function that will be called
  // when packet transmission is finished
  radio.setDio0Action(setFlag);

  // start transmitting the first packet
  Serial.print(F("[SX1278] Sending first packet ... "));

  // you can transmit C-string or Arduino string up to
  // 256 characters long
  transmissionState = radio.startTransmit("Lora Test!");

  // you can also transmit byte array up to 256 bytes long
  /*
    byte byteArr[] = {0x01, 0x23, 0x45, 0x67,
                      0x89, 0xAB, 0xCD, 0xEF};
    state = radio.startTransmit(byteArr, 8);
  */
}

// flag to indicate that a packet was sent
volatile bool transmittedFlag = false;

// disable interrupt when it's not needed
volatile bool enableInterrupt = true;

// this function is called when a complete packet
// is transmitted by the module
// IMPORTANT: this function MUST be 'void' type
//            and MUST NOT have any arguments!
void setFlag(void) {
  // check if the interrupt is enabled
  if (!enableInterrupt) {
    return;
  }

  // we sent a packet, set the flag
  transmittedFlag = true;
}
