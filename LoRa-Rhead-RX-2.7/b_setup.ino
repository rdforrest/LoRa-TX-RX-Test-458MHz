
#include <SPI.h>
#include <RH_RF95.h>
//#include <Servo.h> // gives Timer1 interrupt clash
#include <ServoTimer2.h> // Works fine
#include <avr/wdt.h>
#include <Wire.h>  // For i2c coms
#include <Adafruit_INA219.h> // Voltage & current sensor

Adafruit_INA219 ina219;

// define the pins for the servos
#define servo1 5
#define servo2 6
#define servo3 7
#define servo4 8
#define servo5 9
#define servo6 10

// Declare variables for the servos
ServoTimer2 ch1;
ServoTimer2 ch2;
ServoTimer2 ch3;
ServoTimer2 ch4;
ServoTimer2 ch5;
ServoTimer2 ch6;

// RDF setup
#define RFM95_CS 4
#define RFM95_RST 2
#define RFM95_INT 3
#define RF95_FREQ 458.75

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

// Blinky on receipt
#define LED 13

unsigned long previousMillis = 0;        // for time delay used in Failsafe
const long interval = 5000;           // set time interval (milliseconds)
unsigned long currentMillis = millis();

uint32_t currentFrequency;

void setup()
{
  ch1.attach(servo1);     // attach a pin to the servos and they will start pulsing
  ch2.attach(servo2);
  ch3.attach(servo3);
  ch4.attach(servo4);
  ch5.attach(servo5);
  ch6.attach(servo6);

  pinMode(LED, OUTPUT);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  while (!Serial);
  Serial.begin(9600);
  delay(100);

  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    //while (1) {
    //  delay(10);
    // }
  }

  Serial.println("Arduino LoRa RX Test!");

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
