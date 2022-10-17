
/********************************************* 
File name: MEM458_Lab2A_PWM
by BC Chang, Drexel University,  Oct. 9, 2020
Control the motion of DC motor or the brigtness of LEDs by 
changing the duty cycle of PWM signals
**********************************************/
/********************************************* 
              INITIATION
**********************************************/
// #include <TimerOne.h>

// Use pinX and pinY for PWM outputs
const int pinX = 9;  // for PWM output 1
const int pinY = 10;  // for PWM output 2

// Variables to record the duty cycle parameters
int duty1 = 153;  //duty cycle 153/255 = 60%
int duty2 = 51;   //duty cycle  51/255 = 20%
unsigned long tms = 0;

/***********************************************
                  SETUP 
************************************************/
void setup() {
  // Select the baud rate for the serial monitor
  //Serial.begin(115200);
  // Set up pinX and pinY to provide PWM outputs to move the 
  // motor or turn on LEDs
  pinMode(pinX, OUTPUT);
  pinMode(pinY, OUTPUT);

//Serial.println("Start");
}

/***********************************************
              Main Loop  
************************************************/
int yes=1;

void loop() {

  while(yes)
{
// Generate PWM on pinX and pinY to control motor speed or turn on LEDs
  tms = millis();
  analogWrite(pinX, duty1);
  analogWrite(pinY, duty2);

// Turn off the LEDs and stop the program after 10 seconds
   if (tms >= 10000) {
      yes=0;
      duty1 = 0;
      duty2 = 0;
      analogWrite(pinX, duty1);
      analogWrite(pinY, duty2);
  }
}
}
