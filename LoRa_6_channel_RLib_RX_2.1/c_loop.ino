void loop() {
  wdt_reset(); //reset Watchdog in main loop
  currentMillis = millis(); // capture time for Failsafe function

  // check if the receive flag is set
  if (receivedFlag) { // If received flag is not set, go to ELSE at line 99

    // reset the failsafe delay timer
    previousMillis = currentMillis;

    // disable the interrupt service routine while
    // processing the data
    enableInterrupt = false;

    // reset flag
    receivedFlag = false;

    // you can read received data as an Arduino String
    //String str;
    //int state = radio.readData(str);

    // you can also read received data as byte array
    byte byteArr[8];
    int state = radio.readData(byteArr, 8);

    // print byte array
    Serial.print("Stick output  ");
    for (int i = 0; i < 8; ++i)
    {
      // Serial.println(byteArr[i]);
      Serial.print(byteArr[i]);
      ch1 = byteArr[0];
      Serial.print("\t"); //tab
      ch2 = byteArr[1];
      Serial.print("\t"); //tab
      ch3 = byteArr[2];
      Serial.print("\t"); //tab
      ch4 = byteArr[3];
      Serial.print("\t"); //tab
      ch5 = byteArr[4];
      Serial.print("\t"); //tab
      ch6 = byteArr[5];

    }

    if (state == ERR_NONE) {
      // packet was successfully received
      Serial.print("\n"); //newline
      Serial.println(F("[SX1278] Received packet!"));

      // print data of the packet
      //   Serial.print(F("[SX1278] Data:\t\t"));
      //   Serial.println(str);

      // print RSSI (Received Signal Strength Indicator)
      Serial.print(F("[SX1278] RSSI:\t\t"));
      Serial.print(radio.getRSSI());
      Serial.println(F(" dBm"));

      // print SNR (Signal-to-Noise Ratio)
      Serial.print(F("[SX1278] SNR:\t\t"));
      Serial.print(radio.getSNR());
      Serial.println(F(" dB"));

      // print frequency error
      Serial.print(F("[SX1278] Frequency error:\t"));
      Serial.print(radio.getFrequencyError());
      Serial.println(F(" Hz"));

    } else if (state == ERR_CRC_MISMATCH) {
      // packet was received, but is malformed
      Serial.println(F("[SX1278] CRC error!"));

    } else {
      // some other error occurred
      Serial.print(F("[SX1278] Failed, code "));
      Serial.println(state);

    }

    // put module back to listen mode
    radio.startReceive();

    // we're ready to receive more packets,
    // enable interrupt service routine
    enableInterrupt = true;

    // servo.writes to (pos);
    servo1.write(ch1);
    servo2.write(ch2);
    servo3.write(ch3);
    servo4.write(ch4);
    servo5.write(ch5);
    servo6.write(ch6);

  }

  // Failsafe loop
  else {
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Failsafe activated");
      // FAILSAFE values (0 to 250)
      ch1 = 50;
      ch2 = 130;
      ch3 = 27;
      ch4 = 27;
      ch5 = 50;
      ch6 = 95;

      // failsafe servo.writes to (pos);
      servo1.write(ch1);
      servo2.write(ch2);
      servo3.write(ch3);
      servo4.write(ch4);
      servo5.write(ch5);
      servo6.write(ch6);


      // Reset the processor
      resetFunc();

    }

  }
}
