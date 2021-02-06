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
      rudder = byteArr[0];
      Serial.print("\t"); //tab
      stern_plane = byteArr[1];
      Serial.print("\t"); //tab
      throttle = byteArr[2];
      Serial.print("\t"); //tab
      dive = byteArr[3];
      Serial.print("\t"); //tab
      aux1 = byteArr[4];
      Serial.print("\t"); //tab
      aux2 = byteArr[5];

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
    servo1.write(rudder);
    servo2.write(stern_plane);
    servo3.write(throttle);
    servo4.write(dive);
    servo5.write(aux1);
    servo6.write(aux2);

  }

  // Failsafe loop
  else {
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Failsafe activated");
      // FAILSAFE values (0 to 250)
      rudder = 125;
      stern_plane = 50;
      throttle = 125;
      dive = 50;
      aux1 = 50;
      aux2 = 50;

      // failsafe servo.writes to (pos);
      servo1.write(rudder);
      servo2.write(stern_plane);
      servo3.write(throttle);
      servo4.write(dive);
      servo5.write(aux1);
      servo6.write(aux2);


      // Reset the processor
      resetFunc();

    }

  }
}
