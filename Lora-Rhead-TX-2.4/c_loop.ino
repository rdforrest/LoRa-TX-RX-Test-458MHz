
void loop()
{
  // ppm input
  for (int i = 0; i < 8; i++)   //display all channels
  {
    ppmValues[i] = ((((ppmValues[i]) / 2) - 1000) / 4); // the array value is processed to bring it back to real world value
    //ppmValues[i] = ((((ppmValues[i]) / 2) - 870) / 4); // fiddle factors to get array value back to real world value
    byteArr[i] = ppmValues[i]; // Store in Byte array
    // Serial.print(ppmValues[i]);
    //  Serial.print("  ");
  }
  // Stick output
  Serial.print("Stick output  ");
  Serial.print("\n"); //newline
  for (int i = 0; i < 8; i++)   //display all channels
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
      Serial.print("Telemetry  ");
      Serial.print(buf[0]);
      Serial.print("\t"); //tab
      Serial.print(buf[1]);
      Serial.print("\t"); //tab
      Serial.print(buf[2]);
      Serial.print("\n"); //newline

      // Send telemetry
      mySerial.print(buf[0]);
      mySerial.print('\n'); // new line
      mySerial.print(buf[1]);
      mySerial.print('\n'); // new line
      mySerial.print(buf[2]);
      mySerial.print('\n'); // new line

      if (buf[0] > 80) // This limit set for RSSI i.e low signal strength
      {
        beep();
      }

      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);

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
  delay(200); // RDF was 1000
}
