/*
MEM458 Lab4, Drexel University 11/07/2020
  In Labs 2 and 3, you have learned how to vary the differential of a pair 
  of PWM signals to drive an H-bridge amplifier and control the motion of 
  the DC motor in both CCW and CW directions. You also have learned how to 
  employ the rotary encoder and the hardware interrupt algorithm to measure 
  the angular displacement and the angular velocity of the DC motor in both 
  CCW and CW directions. In this lab, you will first conduct an experiment 
  to find the input-output relationship, and use it to identify the dynamics 
  model or the equation of motion for the DC motor system. The dynamics model 
  will be employed later to design a discrete-time controller that achieves 
  a desired position feedback control. 
  Filename:  MEM458_Lab4_Motor_Model.ino
  BC Chang, Drexel University,  11/07/2020
*/

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
volatile unsigned long LastTime = 0;
volatile unsigned long InrptTime = 0;

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
 InrptTime = millis();   //Note that millis() do not increment in isa
}


/***********************************************
              Main Loop  
************************************************/
int yes=1;

void loop() {

  while(yes)
{
// Generate PWM on pinX to control motor speed
if (InrptTime <= 4000){   //CW rotation for 4 seconds
  duty1 = 10; 
  duty2 = 50;
  }
       duty1=map(duty1,0,100,0,255);
       duty2=map(duty2,0,100,0,255);
       analogWrite(pinIN1, duty1);
       analogWrite(pinIN2, duty2);

// Serial print interrupt times and encoder counts

  if( counter != lastcount ) {
  Serial.print(InrptTime); 
  Serial.print("\t");         // prints a tab
  Serial.print(counter);
  Serial.print("\t");         // prints a tab
  velocity = (float)((counter-lastcount)/(float)(InrptTime-LastTime)); 
  Serial.println(velocity);  // counts/ms
  lastcount = counter;
  LastTime = InrptTime;
  }
  
// Terminate the loop and stop motor motion after four seconds
   if (InrptTime >= 4000) {   
      yes=0;    // to stop the loop
       duty1 = 50;   // to stop the motor
       duty2 = 50;   // to stop the motor
       duty1=map(duty1,0,100,0,255);
       duty2=map(duty2,0,100,0,255);
       analogWrite(pinIN1, duty1);
       analogWrite(pinIN2, duty2);
  }
}
noInterrupts();    // stop interrupts
}
