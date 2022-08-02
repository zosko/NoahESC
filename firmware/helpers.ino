/*This function will only change the PWM values according to the received width_value
  that is given by the PWM read on pin D8*/
void SET_PWM(byte width_value) {
  //We keep the range of PWM between min and max (8 bit value)
  if (width_value < PWM_min_value)    width_value  = PWM_min_value;
  if (width_value > PWM_max_value)    width_value  = PWM_max_value;
  OCR1A  = width_value;                   // Set pin 9  PWM duty cycle
  OCR1B  = width_value;                   // Set pin 10 PWM duty cycle
  OCR2A  = width_value;                   // Set pin 11 PWM duty cycle
}


//Switch to next step functions
void set_next_step() {
  switch (sequence_step) {
    case 0:
      AH_BL();
      BEMF_C_RISING();
      break;
    case 1:
      AH_CL();
      BEMF_B_FALLING();
      break;
    case 2:
      BH_CL();
      BEMF_A_RISING();
      break;
    case 3:
      BH_AL();
      BEMF_C_FALLING();
      break;
    case 4:
      CH_AL();
      BEMF_B_RISING();
      break;
    case 5:
      CH_BL();
      BEMF_A_FALLING();
      break;
  }
}
