#define TIMER_CONV (long)(16e6/64)
/********************************************* 
              INITIALIZATION
**********************************************/
// Use pinIN1 & pinIN2 as PWM outputs to control the motion of the motor
const int pinIN1 = 5;  // for PWM output to IN1 of L298N
const int pinIN2 = 6;  // for PWM output to IN2 of L298N

// Use pinA as the interrupt pin dictated by Encoder Channel A
const int pinA = 2;  // Yellow wire(Channel A) 
// Use pinB as the interrupt pin dictated by Encoder Channel B
const int pinB = 3;  // White wire (Channel B) 

// Variables to record the number of interrupts
volatile long counter = 0;
volatile long lastcount = 0;
volatile unsigned long timer = 0;
volatile unsigned long rolloverCounter = 0;

int duty1 = 50;  // duty cycle between 0 and 100
int duty2 = 50;  // duty cycle between 0 and 100

float velocity = 0;

/***********************************************
                  SETUP 
************************************************/
void setup() {
  // Select the baud rate for the serial monitor
  Serial.begin(2000000);
  // Set up pinIN1, pin IN2 to provide PWM outputs to move the motor
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  // Set up pinA and pinB to read the A, B pulses from the encoder
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

  // Attach the interrupt service routines
  attachInterrupt(digitalPinToInterrupt(pinA),isrA,RISING);
  //attachInterrupt(digitalPinToInterrupt(pinB),isrB,RISING);
  Serial.println("Start");

  // Timer 1 Registers Setup
  cli();
  TIMSK1 |= 1<<5; // Enable input caputure;
  TIMSK1 |= 1; // Enable overflow interrupt
  TCCR1A = 0;
  TCCR1B &= ~0b111;
  TCCR1B |= 0b011;
  TCCR1B |= 1<<6; // Rising edge capture
  TCNT1 = 0; // Reset counter
  rolloverCounter = 0;
  Serial.print(TIMSK1,BIN);
  Serial.println();
  Serial.print(TCCR1A,BIN);
  Serial.println();
  Serial.print(TCCR1B,BIN);
  Serial.println();
  Serial.print(TCCR1C,BIN);
  Serial.println();
  sei();
}


/*************************************************
           Interrupt Service Routine A
**************************************************/
void isrA (){
// isrA is activated if pinA changes from LOW to HIGH
// Check pinB to determine the rotation direction
 if(digitalRead(pinB)==LOW) {
 counter++;
 } else {
 counter--;
 }
}

ISR(TIMER1_CAPT_vect) {
  timer = ICR1 + 0xFFFF*rolloverCounter;
}

ISR(TIMER1_OVF_vect) {
  rolloverCounter++;
}


/***********************************************
              Main Loop  
************************************************/
int yes=1;

void loop() {

  while(yes)
{
// Generate PWM on pinX to control motor speed
  if (timer <= 3*TIMER_CONV) {     //CCW rotation for 3 second
    duty1 = 64;
    duty2 = 37;
  } else {   //CW rotation for 4 seconds
    duty1 = 31;
    duty2 = 69;
  }
       duty1=map(duty1,0,100,0,255);
       duty2=map(duty2,0,100,0,255);
       analogWrite(pinIN1, duty1);
       analogWrite(pinIN2, duty2);

// Serial print interrupt times and encoder counts

  if( counter != lastcount ) {
  Serial.print(timer); 
  Serial.print("\t");         // prints a tab
  Serial.println(counter);
  lastcount = counter;
  }
  
// Terminate the loop and stop motor motion after four seconds
   if (timer >= 7*TIMER_CONV) {   
       yes=0;    // to stop the loop
       duty1 = 50;   // to stop the motor
       duty2 = 50;   // to stop the motor
       duty1=map(duty1,0,100,0,255);
       duty2=map(duty2,0,100,0,255);
       analogWrite(pinIN1, duty1);
       analogWrite(pinIN2, duty2);
  }
}
noInterrupts();
Serial.flush();
}
