#include "EEPROMAnything.h"         //This is used to store more than just one byte to the EEPROM
//Inputs/Outputs
int buzzer = 5;
/* PWM in pin - D8
   High A - D9
   LOW A - D4
   HIGH B - D10
   LOW B - D3
   HIGH C - D11
   LOW C - D2
   Comparator - D6
*/
#define PWM_max_value      255
#define PWM_min_value      30
#define PWM_value    50

int PWM_IN_MAX = 2000;
int PWM_IN_MIN = 1000;
int PWM_IN_MIN_ADRESS = 2;
int PWM_IN_MAX_ADRESS = 7;
int MIN_PWM_TO_STORE = 0;
int MAX_PWM_TO_STORE = 0;
int pwm_set_counter = 0;
int beeping_PWM_VALUE = 100;

byte sequence_step = 0, motor_speed;
unsigned int i;
//We create variables for the time width value of the PWM input signal
unsigned long counter_1, current_count;
byte last_PWM_state;
//To store the 1000us to 2000us value we create variables
int PWM_INPUT;      //In my case PWM_IN pin is D8 of the Arduino
bool MOTOR_SPINNING = false;
bool ESC_MODE_ON = false;
int motor_off_counter = 0;
bool PWM_RANGE_SET = false;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

void setup() {
  pinMode(buzzer, OUTPUT);
  //This will only run once after you uplaod the code
  if ( EEPROM.read(1) != 1) {
    EEPROM_writeAnything(PWM_IN_MIN_ADRESS, PWM_IN_MIN);
    EEPROM_writeAnything(PWM_IN_MAX_ADRESS, PWM_IN_MAX);
    EEPROM.write(1, 1);
  }

  //#error first time you uplaod the code make sure the enxt lien is uncommented. Then, comment back the line and uplaod the code again and delete this entire error line
  //EEPROM.write(1, 0);
  //Our pins for the MNSFET drivers are 2,3,4 and 9,10,11
  DDRD  |= B00011100;           //Configure pins 2, 3 and 4 as outputs CL, BL and AL
  PORTD  = B00000000;           //Pins 0 to 7 set to LOW
  DDRB  |= B00001110;           //Configure pins 9, 10 and 11 as outputs
  PORTB  &= B00110001;          //D9, D10 and D11 to LOW
  // Timer1
  TCCR1A = 0;
  TCCR1B = 0x01;
  // Timer2
  TCCR2A = 0;
  TCCR2B = 0x01;
  // Comparator on pin D6
  ACSR   = 0x10;           // Clear flag comparator interrupt
  //Set D8 (PWM in) to trigger interrupt (we use this to read PWM input)
  PCICR |= (1 << PCIE0);    //enable PCMSK0 scan
  PCMSK0 |= (1 << PCINT0);  //Set pin D8 trigger an interrupt on state change.

  /*Now we detect the PWM input and if is higher than  we enter
    configuration mode and if not, we jump to the void loop*/
  delay(200);
  //Power on mode select
  if (PWM_INPUT > PWM_IN_MIN + 115) {
    ESC_MODE_ON = false;           //Motor rotation is OFF till the config mode is done
    while (!PWM_RANGE_SET) {
      currentMillis = millis();
      if (currentMillis - previousMillis >= 500) {
        OCR1A = beeping_PWM_VALUE;
        previousMillis += 500;
        digitalWrite(buzzer, HIGH);
        PORTD = B00010000;      //Set D4 to HIGH and the rest to LOW
        TCCR1A =  0x81;         //OC1A - D9 compare match noninverting mode, downcounting ,PWM 8-bit
        delay(100);
        digitalWrite(buzzer, LOW);
        PORTD = B00000000;      //Set D4 to HIGH and the rest to LOW
        TCCR1A =  0;            // OC1A and OC1B normal port
      }
      if (PWM_INPUT > MAX_PWM_TO_STORE) {
        MAX_PWM_TO_STORE = PWM_INPUT;
      }

      if (PWM_INPUT < 1200) {
        if (pwm_set_counter > 1000) {
          MIN_PWM_TO_STORE = PWM_INPUT;
          EEPROM_writeAnything(PWM_IN_MIN_ADRESS, MIN_PWM_TO_STORE);
          EEPROM_writeAnything(PWM_IN_MAX_ADRESS, MAX_PWM_TO_STORE);
          ESC_MODE_ON = true;
          PWM_RANGE_SET = true;
          int y = 0;
          digitalWrite(buzzer, HIGH);
          PORTD = B00010000;      //Set D4 to HIGH and the rest to LOW
          TCCR1A =  0x81;         //OC1A - D9 compare match noninverting mode, downcounting ,PWM 8-bit
          delay(500);
          digitalWrite(buzzer, LOW);
          PORTD = B00000000;      //Set D4 to HIGH and the rest to LOW
          TCCR1A =  0;         //OC1A - D9 compare match noninverting mode, downcounting ,PWM 8-bit
          delay(200);
          while (y < 3) {
            digitalWrite(buzzer, HIGH);
            PORTD = B00010000;      //Set D4 to HIGH and the rest to LOW
            TCCR1A =  0x81;         //OC1A - D9 compare match noninverting mode, downcounting ,PWM 8-bit
            delay(100);
            digitalWrite(buzzer, LOW);
            PORTD = B00000000;      //Set D4 to HIGH and the rest to LOW
            TCCR1A =  0;         //OC1A - D9 compare match noninverting mode, downcounting ,PWM 8-bit
            delay(100);
            y = y + 1;
          }
        }
        pwm_set_counter = pwm_set_counter + 1;
        delay(1);
      }
      else {
        pwm_set_counter = 0;
      }
    }
  }
  else { /*If the range is below PWM_IN_MIN+115us then we start the code*/
    OCR1A = beeping_PWM_VALUE;
    ESC_MODE_ON = true;
    int x = 0;
    digitalWrite(buzzer, HIGH);
    PORTD = B00010000;      //Set D4 to HIGH and the rest to LOW
    TCCR1A =  0x81;         //OC1A - D9 compare match noninverting mode, downcounting ,PWM 8-bit
    delay(500);
    digitalWrite(buzzer, LOW);
    PORTD = B00000000;      //Set D4 to HIGH and the rest to LOW
    TCCR1A =  0;         //OC1A - D9 compare match noninverting mode, downcounting ,PWM 8-bit
    delay(200);
    while (x < 3) {
      digitalWrite(buzzer, HIGH);
      PORTD = B00010000;      //Set D4 to HIGH and the rest to LOW
      TCCR1A =  0x81;         //OC1A - D9 compare match noninverting mode, downcounting ,PWM 8-bit
      delay(100);
      digitalWrite(buzzer, LOW);
      PORTD = B00000000;      //Set D4 to HIGH and the rest to LOW
      TCCR1A =  0;         //OC1A - D9 compare match noninverting mode, downcounting ,PWM 8-bit
      delay(100);
      x = x + 1;
    }
  }

  //Save new range to the EEPROM
  EEPROM_readAnything(PWM_IN_MIN_ADRESS, PWM_IN_MIN);
  EEPROM_readAnything(PWM_IN_MAX_ADRESS, PWM_IN_MAX);
}

void loop() {
  /*if PWM input is higher than PWM_IN_MIN + 115 we start the motor*/
  if (PWM_INPUT > (PWM_IN_MIN + 115) && ESC_MODE_ON) {
    MOTOR_SPINNING = true;
    motor_off_counter = 0;
    digitalWrite(buzzer, LOW);
  }

  if (MOTOR_SPINNING) {
    SET_PWM(PWM_value);     // Setup starting PWM with duty cycle = PWM_START_DUTY
    i = 2200;
    // Motor start
    while (i > 100) {
      delayMicroseconds(i);
      set_next_step();
      sequence_step++;
      sequence_step %= 6;
      i = i - 20;
    }
    motor_speed = PWM_value;
    ACSR |= 0x08;                    // Enable analog comparator interrupt
    while (MOTOR_SPINNING) {
      PWM_INPUT = constrain(PWM_INPUT, PWM_IN_MIN, PWM_IN_MAX);
      motor_speed = map(PWM_INPUT, PWM_IN_MIN, PWM_IN_MAX, PWM_min_value, PWM_max_value);
      SET_PWM(motor_speed);
      if (PWM_INPUT < (PWM_IN_MIN + 30)) {
        if (motor_off_counter > 1000) {
          MOTOR_SPINNING = false;
          motor_off_counter = 0;
          PORTD = B00000000;      //Set D4 to HIGH and the rest to LOW
          TCCR1A =  0;            //OC1A - D9 compare match noninverting mode, downcounting ,PWM 8-bit
        }
        motor_off_counter = motor_off_counter + 1;
      }
    }
  }

  if (!MOTOR_SPINNING) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 2000) {
      //previousMillis += 2000;
      digitalWrite(buzzer, HIGH);
      ACSR   = 0x10;            // Disable and clear (flag bit) analog comparator interrupt
      TCCR2A =  0;
      TCCR1A =  0;
      PORTD  = 0x00;            //pins 0 to 7 set to LOW //stop everything
      PORTB  &= 0x31;           //B00110001    D9, D10 and D11 to LOW
      OCR1A = beeping_PWM_VALUE;
      PORTD = B00010000;      //Set D4 to HIGH and the rest to LOW
      TCCR1A =  0x81;         //OC1A - D9 compare match noninverting mode, downcounting ,PWM 8-bit
    }
    if (currentMillis - previousMillis >= 2100) {
      previousMillis += 2000;
      digitalWrite(buzzer, LOW);
      PORTD = B00000000;      //All to LOW
      TCCR1A =  0;            //PWM disabled
    }
  }
}
