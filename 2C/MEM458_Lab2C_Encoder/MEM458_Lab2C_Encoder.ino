/********************************************* 
File name: MEM458_Lab2C_Encoder
by BC Chang, Drexel University,  Oct. 10, 2020
The objective of this experiment is to observe a step response 
of a DC motor dynamic system. A PWM signal with a constant duty 
cycle is applied to the motor circuit to move the motor. As the 
motor moves, the encoder will send the square waves of both 
channels A and B to pinA and pinB, which can be employed to initiate
interrups to measure the displacement of the motor. We will use the 
rise edge of Channel A waveform to initiate interrupts and determine 
the rotation direction based on the value of pinB right after the 
interrupt. The interrupt count number can be positive (CW) or 
negative (CCW). The count number will increase (or decrease) if the 
motor is moving CW (or CCW). The interrupt count number is closely
related to the displacement of the motor. By a careful calibration
the displac+ement can be measured via the interupt counts. Together 
with the timing information, the angular velocity of tghe motor also 
can be obtained.  
**********************************************/
/********************************************* 
              INITIATION
**********************************************/
// Use pinX for PWM output to control the motion of the motor
const int pinX = 10;  // for PWM output 

// Use pinA as the interrupt pin for Encoder Channel A
const int pinA = 2;  // Yellow(Channel A) in oscilloscope graph
// Use pinB as the interrupt pin for Encoder Channel B
const int pinB = 3;  // Blue(Channel B) in oscilloscope graph

// Variables to record the number of interrupts
volatile long countA = 0;
volatile long lastcountA = 0;
unsigned long lastInrptTimeA = 0;
volatile unsigned long InrptTimeA = 0;

int duty;  //duty cycle 153/255 = 60%
float velocity;
/*************************************************
           Interrupt Service Routine A
**************************************************/
void isrA ()  {
  // isrA is activated if pinA changes from LOW to HIGH
  // Check pinB to determine the rotation direction
  if(digitalRead(pinB)==LOW) {
     countA++;
  } else {
     countA--;
 }  
   InrptTimeA = millis();   //Note that millis() do not increment in isa
}

/***********************************************
                  SETUP 
************************************************/
void setup() {
  // Select the baud rate for the serial monitor
  Serial.begin(115200);
  // Set up pinX to provide PWM output to move the motor
  pinMode(pinX, OUTPUT);
  // Generate PWM on pinX to control motor speed
  duty = 142; //60% duty cycle
  analogWrite(pinX, duty);
  //pinMode(pinY, OUTPUT);
  // Set up pinA and pinB to read the A, B pulses from the encoder
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

  // Attach the interrupt service routines
  attachInterrupt(digitalPinToInterrupt(pinA),isrA,RISING);
 
  Serial.println("Start");
}

/***********************************************
              Main Loop  
************************************************/
int yes=1;

void loop() {
  
  while(yes)
{
// Serial print interrupt times and encoder counts

if( countA != lastcountA ) {   
  Serial.print(InrptTimeA);
  Serial.print("\t");         // prints a tab
  Serial.print(countA);
  Serial.print("\t");         // prints a tab
  velocity = (float)((countA-lastcountA)/(float)(InrptTimeA-lastInrptTimeA)); 
  Serial.println(velocity);  // counts/ms
  lastcountA = countA;
  lastInrptTimeA = InrptTimeA;
}

//if (InrptTimeA >= 3000) {
//  duty = 167;
//	analogWrite(pinX, duty);
//}

if (InrptTimeA >= 10000) {   
  yes=0;
  duty = 0;
  analogWrite(pinX, duty);
  }
}
noInterrupts();
Serial.flush();
}
