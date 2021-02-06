/*
 *Fast and accurate PWM reader 
 * 
 * Note values will need to be halved to bring them back to real world values
 * 
 * Source
 * https://forum.arduino.cc/index.php?topic=85603.0
 * 
 * Note due to increased accuracy values are read to 0.5us * 
 * To get the array values back to real world full 'us' values the array value must be divided by 2
 * 
 * 
 * Hardware connections
 *  * use pin 8 as ppm in
 * 
 * Note - ICR = the "Input Capture Register"
 */
