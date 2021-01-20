void loop()
{
  // Must be called at least once after assigning a handler to a pin.
  // Recommended to include in loop for noise immunity
  ppm.sync();

  // Use to handler.get(channel number) to get the pulse width a ppm channel.
  // The channel numbers are integers 1 - 6
  for (int i = 1; i <= 6; ++i)
  {
    rudder = ppm.get(1); //rudder =1,stern planes =2, throttle =3, dive =4
    rudder = (rudder - 700) / 3.5; // Adjust range
    stern_plane = ppm.get(2);
    stern_plane = (stern_plane - 700) / 3.5; // Adjust range
    throttle = ppm.get(3);
    throttle = (throttle - 700) / 3.5; // Adjust range
    dive  = ppm.get(4);
    dive = (dive - 700) / 3.5; // Adjust range

    //Test
    //rudder = 250;

    Serial.print(rudder);
    Serial.print(' ');
    Serial.print(stern_plane);
    Serial.print(' ');
    Serial.print(throttle);
    Serial.print(' ');
    Serial.print(dive);
    Serial.print('\n'); // new line

  }
  // Serial.println();
  //delay(1000);

  // Print the voltage sensor value to Serial1
  Serial1.print('\<'); // new line
  Serial1.print("T");
  Serial1.print('\,'); // commma
  Serial1.print(rudder);
  Serial1.print('\,'); // commma
  Serial1.print(stern_plane);
  Serial1.print('\,'); // commma
  Serial1.print(throttle);
  Serial1.print('\,'); // commma
  Serial1.print(dive);
  Serial1.print('\>'); // new line

  delay (200); //RDF was 200

  //delay (200); //
  //delay(10); // We wait 10mS to print the next value

  //Test
  //Serial1.print("RDF");
  //Serial1.print('\n'); // new line
  //delay(100); // RDF was 1000. We wait to print the next value

}
