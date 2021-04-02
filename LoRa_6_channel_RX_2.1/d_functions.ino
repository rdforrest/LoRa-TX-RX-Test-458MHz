// Reset function in software to kick start
void resetFunc() {

}

void beep() {   // Sounder output
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);   // Test. Turn the sounder on D7 on
  delay(500);              // wait
  digitalWrite(7, LOW);   // turn off
}
