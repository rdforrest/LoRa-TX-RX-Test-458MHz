
#include <SPI.h>
#include <RH_RF95.h>
#include <Wire.h>  // For i2c coms
#include <SoftwareSerial.h>  // For i2c comms etc

SoftwareSerial mySerial(5, 6); // Pin D5 RX, Pin D6 TX Use this one, not the TX output!

unsigned int ppmValues[8];

byte byteArr[8];

// RDF setup
#define RFM95_CS 4
#define RFM95_RST 2
#define RFM95_INT 3
#define RF95_FREQ 458.75

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup()
{
  pinMode(8, INPUT); // ppm input
  setup_timer1();

  beep(); //beep function in setup
  delay(500);              // wait
  beep();
  delay(500);              // wait
  beep();

  // Serial1.begin(115200); // Was 57600, 9600
  Serial.println("Data in");
  Serial.println();

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.print(123);

  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  while (!Serial);
  Serial.begin(9600);
  delay(100);

  Serial.println("Arduino LoRa TX Test!");

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);

  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
}

int16_t packetnum = 0;  // packet counter, we increment per xmission
