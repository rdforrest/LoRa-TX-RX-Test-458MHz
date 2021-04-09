/*
   Uses RadioHead library
   http://www.airspayce.com/mikem/arduino/RadioHead/
   For 6 channel radio control using LoRa.
   For bare SX1278 (with level convertor) and also Adafruit RFM96W breakout board
   For Nano

   https://learn.adafruit.com/adafruit-rfm69hcw-and-rfm96-rfm95-rfm98-lora-packet-padio-breakouts/rfm9x-test
  // LoRa 9x_TX
  // -*- mode: C++ -*-
  // Example sketch showing how to create a simple messaging client (transmitter)
  // with the RH_RF95 class. RH_RF95 class does not provide for addressing or
  // reliability, so you should only use RH_RF95 if you do not need the higher
  // level messaging abilities.
  // It is designed to work with the other example LoRa9x_RX

   ppm reader for transmitter "buddy box" output.
   ppmReaderAccurate-1.1
   Thanks to Jonathan Askey for introducing this to me. RDF
   Fast and accurate PPM reader

   Note values will need to be halved to bring them back to real world values

   Source
   https://forum.arduino.cc/index.php?topic=85603.0

   Note due to increased accuracy values are read to 0.5us
   To get the array values back to real world full 'us' values the array value must be divided by 2


  /*
   Hardware notes  for Adafruit RFM95W and Semtech SX1278:
  Adafruit RFM95W
  - This is the simplest to connect. No need to use  level shifter for a 5v Arduino.
  RFM95W      to      Arduino Nano
  RST                 D2  to radio CS (or any other digital I/O pin)
  CS                  D4  to radio CS (or any other digital I/O pin)
  MOSI                D11
  MISO                D12
  SCK                 D13
  G0                  D3  (This is the interrupt)
  EN                  Not connected
  GND                 GND
  VIN                 5V

  5v sounder on pin D7 for TX
  Servo outputs pins D5 to D10 for RX

  OR:
  For bare SX1278 chip connecting to Arduino Nano through level shifter
  Semtech SX1278 LORA Module Long Range RF Wireless DRF1278F SPI Arduino Pi IoT UK
  Condition:New.   Ebay UK. tangle.of.tings (4151)   153412183277

  https://how2electronics.com/interfacing-sx1278-lora-module-with-arduino/

  The LoRa SX1278 is not 5V friendly so do not supply 5V to it else the board will get damaged. Use 3.3V of Arduino to connect it to VCC pin. Connect all the GND pins to GND. Connect the RST pin to D9 and DIO0 to D2 of Arduino. Connect the SPI Pins NSS, MOSI, MISO, SCK to Arduino D10, D11, D12, D13 of Arduino respectively as shown in circuit diagram above.
  Arduino<<<<<<<<<Level shifter<<PCB<<SX1278
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
  Ard 5v  Socket 9  HV

  Socket 7 - Not used     9 ANT - RF signal output/input.
          10 GND - Ground
          7 DIO5 I/O Digital I/O, software configured
          12 DIO4 I/O Digital I/O, software configured

  Semtech SX1278 LORA Module Long Range RF Wireless DRF1278F SPI Arduino Pi IoT UK from Ebay

  SOP14 SSOP14 TSSOP14 to DIP PCB SMD DIP/Adapter plate Pitch 0.65/1.27mm + Pins
  ( 272682553778 ) (eBay)
  No Required: 4
  ITEM PRICE:
  £2.50

  IIC I2C Bi-Directional Logic Level Shifter Converter Module 5V to 3.3V
  puretek-innovations (12579 ) (eBay)

  Notes from Wiki for Radio Lib:
  SPI modules: Module(cs, irq, rst, gpio). For example: RF69 rf = new Module(10, 2, 3);
  CS: this is the pin that's used as SPI chip select.
  IRQ: this is the interrupt pin, it's usually connected to external interrupt on Arduino. It's a fast way for the module to tell Arduino something has happened - for example, a packet was received. All SPI modules have at least one interrupt pin.
  RST: most modules have a hardware reset pin. If the module doesn't have a reset or chip enable pin (e.g. CC1101), set rst to RADIOLIB_NC.
  GPIO: this is the fourth possible pin. It's optional for most modules, but may be required for some. SX127x requires additional interrupt pin to perform CAD and blocking receive. SX126x also uses this pin as the BUSY indication pin. If not in use, this pin can be left unassigned, or set to RADIOLIB_NC.

*/
