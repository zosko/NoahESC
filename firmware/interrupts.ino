// Interrumption vector for the Analog comparator
ISR (ANALOG_COMP_vect) {
  for (i = 0; i < 10; i++) {          //We check the comparator 10 times just to be sure
    if (sequence_step & 1) {            //If step = odd (0001, 0011, 0101) 1, 3 or 5
      if (!(ACSR & B00100000)) i -= 1; //!B00100000 -> B11011111 ACO = 0 (Analog Comparator Output = 0)
    }
    else {                              //else if step is 0, 2 or 4
      if ((ACSR & B00100000))  i -= 1; //else if B00100000 -> B11011111 ACO = 1 (Analog Comparator Output = 1)
    }
  }
  set_next_step();                    //set the next step of the sequence
  sequence_step++;                    //increment step by 1, next part of the sequence of 6
  sequence_step %= 6;                 //If step > 5 (equal to 6) then step = 0 and start over
}

/*This is the interruption routine on pin change
  in this case for digital pin D8 which is the PWM input*/
ISR(PCINT0_vect) {
  //First we take the current count value in micro seconds using the micros() function
  current_count = micros();
  ///////////////////////////////////////Channel 1
  if (PINB & B00000001) {                            //We make an AND with the pin state register, We verify if pin 8 is HIGH???
    if (last_PWM_state == 0) {                       //If the last state was 0, then we have a state change...
      last_PWM_state = 1;                            //Store the current state into the last state for the next loop
      counter_1 = current_count;                     //Set counter_1 to current value.
    }
  }
  else if (last_PWM_state == 1) {                    //If pin 8 is LOW and the last state was HIGH then we have a state change
    last_PWM_state = 0;                              //Store the current state into the last state for the next loop
    PWM_INPUT = current_count - counter_1;           //We make the time difference. PWM_INPUT is current_time - counter_1 in micro-seconds.
  }
}
