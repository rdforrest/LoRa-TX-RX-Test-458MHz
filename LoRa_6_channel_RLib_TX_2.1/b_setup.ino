
#include <RadioLib.h>

unsigned int ppmValues[8];
int pulse = 0;
int ch1;
int ch2;
int ch3;
int ch4;
int ch5;
int ch6;

byte byteArr[8];

// SX1278 has the following connections:
// NSS or CS pin:   10
// DIO0 pin:  2
// RESET pin: 9
// DIO1 pin:  3
//SX1278 radio = new Module(10, 2, 9, 3);
SX1278 radio = new Module(4, 3, 9, 9);   // RDF Not sure about two final 9s ?

// or using RadioShield
// https://github.com/jgromes/RadioShield
//SX1278 radio = RadioShield.ModuleA;

// save transmission state between loops
int transmissionState = ERR_NONE;

void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT); // ppm input
  setup_timer1();
  void beep(); // Create beep function

  // Serial1.begin(115200); // Was 57600, 9600
  Serial.println("Data in");
  Serial.println();

  // initialize SX1278 with default settings
  // Set frequency & bandwidth (Values need to be changed in SX1278.h)
  //  setFrequency(458.75);
  //  setBandwidth(62.5);

  Serial.print(F("[SX1278] Initializing ... "));
  int state = radio.begin();

  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
    beep ();
  }

  beep (); // Switch on beeps
  delay(500);
  beep ();

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
