void loop() {

  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0
    parseData();
    showParsedData();
    newData = false;
  }

  // check if the previous transmission finished
  if (transmittedFlag) {
    // disable the interrupt service routine while
    // processing the data
    enableInterrupt = false;

    // reset flag
    transmittedFlag = false;

    if (transmissionState == ERR_NONE) {
      // packet was successfully sent
      Serial.println(F("transmission finished!"));

      // NOTE: when using interrupt-driven transmit method,
      //       it is not possible to automatically measure
      //       transmission data rate using getDataRate()

    } else {
      Serial.print(F("failed, code "));
      Serial.println(transmissionState);

    }

    // RDF Test. print RSSI (Received Signal Strength Indicator)
    //radio.getRSSI();
    float getRSSI();
    
    Serial.print(F("[SX1278] RSSI (Not working):\t\t"));
    Serial.print(radio.getRSSI());
    //Serial.print(getRSSI());
    Serial.println(F(" dBm"));

    // wait a period before transmitting again
    delay(250); // RDF original was 1000

    // send another one
    Serial.print(F("[SX1278] Sending another packet ... "));

    // you can transmit C-string or Arduino string up to
    // 256 characters long
    transmissionState = radio.startTransmit("In loop");

    // you can also transmit byte array up to 256 bytes long
    byte byteArr[] = {integerFromPC, integerFromPC1, integerFromPC2, integerFromPC3, 1, 2, 3, 4};
    int state = radio.startTransmit(byteArr, 8);

    // we're ready to send more packets,
    // enable interrupt service routine
    enableInterrupt = true;
  }
}
