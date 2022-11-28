/*
  MEM458 Lab4 Drexel University 11/08/2020
  The objective of this experiment is to implement a real-time proportional feedback 
  controller to achieve position tracking/regulation control for the DC motor.
  The circuit connections of the motor, encorder, L298N, and Arduino Mega 
  are identical to what we did in Lab 3. The computer programs regarding
  the PWM and the encoder are basically the same. The controller is designed to 
  automatically adjusting the input voltage (the PWM duty cycle) to the DC motor 
  so that the motor position will follow the refernce position input. In this experiment, 
  we will try to employ a proportional feedback control to move the motor to a desired position.
  Filename:  MEM458_Lab4_RT_PosFk.ino
  BC Chang, Drexel University,  11/08/2020
*/

#include <TimerOne.h>
//#include <TimerThree.h>
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
volatile unsigned long InrptTimeS = 0;
volatile unsigned long LastTimeS = 0;

volatile float deg = 0;
volatile int countS = 0;   // number of sampling instant counts
float Ts=0.01;   // sampling period = 10 ms
float err=0, mk=0, xk=0;
//float kp=0.55;
//float kp=0.4;
float kp=1;

float ref_deg=0;

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

  Timer1.initialize(10000); // initialize ISR timer based on this sampling period 10ms
  Timer1.attachInterrupt(isrS); // attach named ISR to timer
}

/*************************************************
           Interrupt Service Routine S
**************************************************/
void isrS ()
// isrS is activated once every 10 ms at sampling instants
{
 deg = (counter)*0.892 ;  // covert encoder interrupt count number to deg
 InrptTimeS = micros();
 lastcount = counter;
 countS++;   
}

/*************************************************
           Interrupt Service Routine A
**************************************************/
void isrA (){
// isrA is activated if pinA changes from LOW to HIGH
// Check pinB to determine the rotation direction
 if(digitalRead(pinB)==LOW) {
 counter++;   // increment counter count by one if motor rotates CW
 } else {
 counter--;
 }
 InrptTime = micros();   
}


/***********************************************
              Main Loop  
************************************************/
int yes=1;

void loop() {

  while(yes)     // program will stop if yes is not 1
{ 
  if( InrptTimeS != LastTimeS )
  {
   Serial.print(InrptTimeS);
   Serial.print("\t");
   Serial.print(counter);
   Serial.print("\t");
   Serial.print(mk);
   Serial.print("\t");
   Serial.println(deg);
    LastTimeS = InrptTimeS;
  }

 if(InrptTimeS < 2000000)
  {
    ref_deg = 180;
  } 
  
   err = ref_deg - deg;

// proportional control
   mk= kp*err;
  if (abs(mk) < 15)       // to address the dead-zone issue
   {mk *= 3;}
   
   if(mk>100)
   {mk=100;}
   if(mk<-100)
   {mk=-100;} 

   if (abs(err)<2)    // if error is within 2 deg, stop the motor
    {mk=0;}

   duty2 = 50 + mk/2; 
   duty1 = 50 - mk/2;

       duty1=map(duty1,0,100,0,255);
       duty2=map(duty2,0,100,0,255);
       analogWrite(pinIN1, duty1);
       analogWrite(pinIN2, duty2);

 
// Terminate the loop and stop motor motion after two seconds  
   if (InrptTimeS >= 2000000) {  
      yes=0;    // to stop the loop
       duty1 = 50;   // to stop the motor
       duty2 = 50;   // to stop the motor
       duty1=map(duty1,0,100,0,255);
       duty2=map(duty2,0,100,0,255);
       analogWrite(pinIN1, duty1);
       analogWrite(pinIN2, duty2);
    }
 }
}
