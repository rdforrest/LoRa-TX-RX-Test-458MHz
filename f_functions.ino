void setup_timer1() {
  //WGM -> Fast PWM
  //Prescaler -> 1/8
  //Compare Output Mode - > non-inverting mode
  //Input capture interrupt enable
  TIMSK1 &= ~( _BV(TOIE1) | _BV(ICIE1) | _BV(OCIE1A) | _BV(OCIE1B));
  TCCR1B &= ~(_BV(ICNC1));
  TCCR1A |= _BV(WGM11) | _BV(WGM10) | _BV(COM1A1) | _BV(COM1B1);
  TCCR1B |= _BV(WGM12) | _BV(WGM13) | _BV(ICES1);
  TCCR1B |= _BV(CS11);
  TCCR1B &= ~( _BV(CS12) | _BV(CS10) );
  TCCR1A &= ~( _BV(COM1A0) | _BV(COM1B0));
  TIMSK1 |= (1 << ICIE1);
  OCR1A = 0xFFFF;
  OCR1B = 0x0;
}

//Interrupt routine
ISR(TIMER1_CAPT_vect) {

  static unsigned int lasticr; //Input Capture Register at at last capture
  static unsigned char currentChannel; //current channel

  unsigned int licr;

  licr = ICR1 - lasticr;
  lasticr = ICR1;

  if (licr > 5000)
  { //pulse too long, means start of new frame
    currentChannel = 0;
  }
  else if (licr > 1000)
  {
    //pulse good, take reading, go to next channel
    ppmValues[currentChannel] = licr;
    if (currentChannel < 8)
    {
      currentChannel++;
    }
  }
  else {
    //too short, nothing to see here
  }

}
