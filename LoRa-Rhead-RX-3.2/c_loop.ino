
void loop()
{
  // Voltage and current measuring using ina219
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  //Serial.print("Bus Voltage:   ");
  //Serial.print(busvoltage);
  //Serial.println(" V");
  //Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  //Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  //Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  //Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  //Serial.println("");

  wdt_reset(); //reset Watchdog in main loop for Failsafe
  currentMillis = millis(); // capture time for Failsafe function
  currentMillisTel = millis(); // capture time for Telemetry

  // Serial.print(currentMillisTel);
  // Serial.print("\n"); //newline
  // Serial.print(previousMillisTel);

  if (rf95.available())
  {
    // reset the Failsafe timer
    previousMillis = currentMillis;

    // Should be a message for us now
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len))
    {
      digitalWrite(LED, HIGH);
      RH_RF95::printBuffer("Control signal received: ", buf, len);
      //  Serial.print("Got: ");
      //  Serial.println((char*)buf);

      // Print stick outputs
      for (int i = 0; i < 8; i++)   //display all channels
      {
        Serial.print(buf[i]);
        Serial.print("\t"); //tab
      }

      // print array and convert to val for Servo2
      Serial.print("Stick output  ");
      Serial.print("\n"); //newline

      int  val1 = buf[0] * 4 + 1000;
      int  val2 = buf[1] * 4 + 1000;
      int  val3 = buf[2] * 4 + 1000;
      int  val4 = buf[3] * 4 + 1000;
      int  val5 = buf[4] * 4 + 1000;
      int  val6 = buf[5] * 4 + 1000;

      Serial.print("\n"); //newline

      // Serial.print("RSSI: ");
      //  Serial.println(rf95.lastRssi(), DEC);
      int Strength = (rf95.lastRssi()) * -1; // Make it positive
      //Serial.println(Strength);

      // Servo.writes to position
      ch1.write(val1);
      ch2.write(val2);
      ch3.write(val3);
      ch4.write(val4);
      ch5.write(val5);
      ch6.write(val6);

      // Send telemetry but only after elapsed interval
      if (currentMillisTel - previousMillisTel >= interval) {
        previousMillisTel = currentMillisTel; // Reset Telemetry timer
        //  uint8_t data[] = "And hello back to you";
        // Test telemetry data
        uint8_t data[37]; // Array
        data[0] = Strength;
        data[1] = current_mA ; // Amps,say
        data[2] = busvoltage; // Voltage, say

        /*
          // Test data
          data[0] = 111;
          data[1] = 211;
          data[2] = 222;
        */

        rf95.send(data, sizeof(data));
        rf95.waitPacketSent();
        Serial.println("Sent Telemetry");
        digitalWrite(LED, LOW);
      }
    }
    else
    {
      Serial.println("Receive failed");
    }
  }

  // Failsafe section
  else {
    // set time interval (milliseconds)
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Failsafe values");
      // FAILSAFE values (1000 to 2000)
      val1 = 1600; // This is often for steering, so slight turn
      val2 = 1750;
      val3 = 1750;
      val4 = 1750;
      val5 = 1280; // This is often for piston tank, so empty
      val6 = 1660; // This is often for speed control, so slight ahead

      Serial.print((val1 - 1000) / 4);
      Serial.print("\n"); //newline
      Serial.print((val2 - 1000) / 4);
      Serial.print("\n"); //newline
      Serial.print((val3 - 1000) / 4);
      Serial.print("\n"); //newline
      Serial.print((val4 - 1000) / 4);
      Serial.print("\n"); //newline
      Serial.print((val5 - 1000) / 4);
      Serial.print("\n"); //newline
      Serial.print((val6 - 1000) / 4);
      Serial.print("\n"); //newline

      // servo.writes to position
      ch1.write(val1);
      ch2.write(val2);
      ch3.write(val3);
      ch4.write(val4);
      ch5.write(val5);
      ch6.write(val6);

      delay(200);

      // Reset the processor
      resetFunc();
    }
  }
}
