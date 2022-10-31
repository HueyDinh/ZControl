
/********************************************* 
File name: MEM458_Lab2B_PWM_motor
by BC Chang, Drexel University,  Oct. 9, 2020
Control the motion of DC motor by 
varying the duty cycle of the PWM signal
**********************************************/
/********************************************* 
              INITIATION
**********************************************/
// Use pinX for PWM outputs
const int pinX = 10;  // for PWM output 

// Variables to record the duty cycle parameters
int duty = 153;  //duty cycle 153/255 = 60%
//int duty = 51;   //duty cycle  51/255 = 20%
unsigned long tms = 0;

/***********************************************
                  SETUP 
************************************************/
void setup() {
  // Set up pinX to provide PWM output to move the motor
  pinMode(pinX, OUTPUT);
}

/***********************************************
              Main Loop  
************************************************/
int yes=1;

void loop() {

  while(yes)
{
// Generate PWM on pinX to control the motor speed
  tms = millis();
  analogWrite(pinX, duty);

// Turn off the PWM and stop the motor after 10 seconds
   if (tms >= 10000) {
      yes=0;
      duty = 0;
      analogWrite(pinX, duty);
  }
}
}
