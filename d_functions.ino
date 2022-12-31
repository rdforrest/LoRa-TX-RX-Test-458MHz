// Reset function in software to kick start
void resetFunc() {

}

void beep() {   // Sounder output
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);   // Test. Turn the sounder on D7 on
  delay(500);              // wait
  digitalWrite(7, LOW);   // turn off
}

void Telemetry() {   // Telemetry output. This function not used yet.
  // Send telemetry but only after elapsed interval
  if (currentMillisTel - previousMillisTel >= interval) {
    previousMillisTel = currentMillisTel; // Reset Telemetry timer
    //  uint8_t data[] = "And hello back to you";
    uint8_t data[37]; // Array
    data[0] = Strength;
    data[1] = current_mA ; // Amps,say
    data[2] = busvoltage; // Voltage, say
    rf95.send(data, sizeof(data));
    rf95.waitPacketSent();
    Serial.println("Sent Telemetry");
    digitalWrite(LED, LOW);
  }

}
