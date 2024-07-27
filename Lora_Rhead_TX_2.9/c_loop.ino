
void loop()
{
  // ppm input
  for (int i = 0; i < 6; i++)   //display all channels
  {
    // This section scales analogue pulse value in milli secs to 0 to 255 for radio control.
    // Values need adjusting for different TXs. A better, but more complicated system, would be to do an initial calibration of sticks, saved to memory.
    ppmValues[i] = map(ppmValues[i], 1800, 4140, 0, 255);
    ppmValues[i] = constrain (ppmValues[i], 1, 255);
    byteArr[i] = ppmValues[i]; // Store in Byte array
    //Serial.print(ppmValues[i]);
    //Serial.print("  ");
  }
  // Stick output
  Serial.print("Stick output  ");
  Serial.print("\n"); //newline
  for (int i = 0; i < 6; i++)   //display all channels
  {
    Serial.print(byteArr[i]);
    Serial.print("\t"); //tab
  }
  Serial.print("\n"); //newline
  // Serial.println();

  Serial.println("Sending to rf95_server");
  // Send a message to rf95_server
  // char radiopacket[20] = "Hello World #      ";
  // itoa(packetnum++, radiopacket + 13, 10);
  //  Serial.print("Sending "); Serial.println(radiopacket);
  //  radiopacket[19] = 0;

  Serial.println("Sending..."); delay(10);
  // rf95.send((uint8_t *)radiopacket, 20);
  rf95.send(byteArr, sizeof(byteArr));

  Serial.println("Waiting for packet to complete..."); delay(10);
  rf95.waitPacketSent();

  // Now wait for a reply
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  Serial.println("Waiting for reply..."); delay(10);
  if (rf95.waitAvailableTimeout(1000))
  {
    // Should be a telemetry message for us now
    if (rf95.recv(buf, &len))
    {
      // Serial.print("Got reply: ");
      // Serial.println((char*)buf);

      // Print telemetry
      Serial.print("\n"); //newline
      Serial.print("Telemetry  ");
      Serial.print(buf[0]);
      Serial.print("\t"); //tab
      Serial.print(buf[1]);
      Serial.print("\t"); //tab
      Serial.print(buf[2]);
      Serial.print("\n"); //newline

      // Send telemetry


      for (int i = 0; i < 10; i++)   //repeat telemetry send
      {
        mySerial.print('\n'); // new line
        mySerial.print(buf[0]);
        mySerial.print('\n'); // new line
        mySerial.print(buf[1]);
        mySerial.print('\n'); // new line
        mySerial.print(buf[2]);
        mySerial.print('\n'); // new line
      }

      if (buf[0] > 80) // This limit set for RSSI i.e low signal strength
      {
        beep();
      }
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);
      Serial.print("\n"); //newline
    }
    else
    {
      Serial.println("Receive failed");
    }
  }
  else
  {
    Serial.println("No reply, is there a listener around?");
  }
 // delay(200); // RDF was 1000 then removed entirely.
}
