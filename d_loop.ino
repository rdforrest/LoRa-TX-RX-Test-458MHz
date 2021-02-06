void loop()
{
  
 for(int i = 0; i < 8; i++)    //display all channels
  {
    Serial.print((ppmValues[i]/2));  // the array value is divided by 2 to bring it back to real world value
    Serial.print("  ");
  }
  Serial.println();
}
