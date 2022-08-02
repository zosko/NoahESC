/*On each step we change the digital pins to be HIGH or LOW or to be PWM or no-PWM
  depending on which step of the sequence we are*/
//D9 PWM and D3 HIGH.
void AH_BL() {
  PORTD = B00001000;      //Set D3 (BL) to HIGH and the rest to LOW
  TCCR2A =  0;            //OC2A - D11 normal port.
  TCCR1A =  0x81;         //OC1A - D9 (AH) compare match noninverting mode, downcounting ,PWM 8-bit
}
//D9 PWM and D2 HIGH
void AH_CL() {
  PORTD = B00000100;      //Set D2 (CL) to HIGH and the rest to LOW
  TCCR2A =  0;            //OC2A - D11 normal port.
  TCCR1A =  0x81;         //OC1A - D9 (AH) compare match noninverting mode, downcounting ,PWM 8-bit
}
//D10 PWM and D2 HIGH
void BH_CL() {
  PORTD = B00000100;      //Set D2 (CL) to HIGH and the rest to LOW
  TCCR2A =  0;            //OC2A - D11 normal port.
  TCCR1A =  0x21;         //OC1B - D10 (BH) compare match noninverting mode, downcounting ,PWM 8-bit
}
//D10 PWM and D4 HIGH
void BH_AL() {
  PORTD = B00010000;      //Set D4 (AL) to HIGH and the rest to LOW
  TCCR2A =  0;            //OC2A - D11 normal port.
  TCCR1A =  0x21;         //OC1B - D10 (BH) compare match noninverting mode, downcounting ,PWM 8-bit
}
//D11 PWM and D4 HIGH
void CH_AL() {
  PORTD = B00010000;      //Set D4 (AL) to HIGH and the rest to LOW
  TCCR1A =  0;            // OC1A and OC1B normal port
  TCCR2A =  0x81;         // OC2A - D11 (CH) compare match noninverting mode, downcounting ,PWM 8-bit
}
//D11 PWM and D3 HIGH
void CH_BL() {
  PORTD = B00001000;      //Set D3 (BL) to HIGH and the rest to LOW
  TCCR1A =  0;            // OC1A and OC1B normal port
  TCCR2A =  0x81;         // OC2A - D11 (CH) compare match noninverting mode, downcounting ,PWM 8-bit
}
