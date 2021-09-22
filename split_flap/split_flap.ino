#include <AccelStepper.h>
// Motor pin definitions:
#define motorPin1  8      // IN1 on the ULN2003 driver
#define motorPin2  9      // IN2 on the ULN2003 driver
#define motorPin3  10     // IN3 on the ULN2003 driver
#define motorPin4  11     // IN4 on the ULN2003 driver
// Define the AccelStepper interface type; 4 wire motor in half step mode:
#define MotorInterfaceType 4
// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper library with 28BYJ-48 stepper motor:
AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);

int SENSOR = 7 ; // define the Hall magnetic sensor interface
int val, starting, lastpos = 0, degfix = 0 ; // define numeric variables val
int moveto ();
 
void setup ()
{
  pinMode (SENSOR, INPUT) ;  // define the Hall magnetic sensor line as input
  // Set the maximum steps per second:
  stepper.setMaxSpeed(1000);
  val = digitalRead (SENSOR) ; // read sensor line
  while (val == HIGH) 
  {
    stepper.move(-1);
    stepper.setSpeed(-500);
    val = digitalRead (SENSOR) ; // read sensor line
    stepper.runToPosition();
  }
  if (val == LOW)
  {
    //moveto(70, 500, 1000);
    //delay(1000);
    stepper.setCurrentPosition(0);
    delay(1000);
  }
  Serial.begin(9600);
  
}
 
void loop ()
{
  /*
   * A = 170 degrees
   * 0 = 70 degrees
   */

   /*
    *  A | B | C | D | E | F | G | H | I | J | K | L | M |
    * 170 180 190 200 210 220 230 240 250 260 270 280 290
    *  N | O | P | Q | R | S | T | U | V | W | X | Y | Z |
    * 300 310 320 330 340 350  0  10  20  30  40  50  60 
    *  0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
    *  70 80  90  100 110 120 130 140 150 160 
    */

    
   /*LABAS
  moveto(280, 1000, 1000);
  moveto(170, 1000, 1000); 
  moveto(180, 1000, 1000);
  moveto(170, 1000, 1000); 
  moveto(350, 1000, 1000);
    */
  //HELLO WORLD
  moveto(240, 1000, 1000);
  moveto(210, 1000, 1000);
  moveto(280, 1000, 1000);
  moveto(280, 1000, 1000);
  moveto(310, 1000, 2000);
  moveto(30, 1000, 1000);
  moveto(310, 1000, 1000);
  moveto(340, 1000, 1000);
  moveto(280, 1000, 1000);
  moveto(200, 1000, 2000);
 //  moveto(0, 1000, 5000);
 //  moveto(10, 1000, 5000);
 //  moveto(20, 1000, 5000);
 //  moveto(30, 1000, 5000);
  
  val = digitalRead (SENSOR) ; // read sensor line
  while (val == HIGH) 
  {
    stepper.move(-1);
    stepper.setSpeed(-500);
    val = digitalRead (SENSOR) ; // read sensor line
    stepper.runToPosition();
  }
  if (val == LOW)
  {
    //moveto(70, 500, 1000);
    delay(1000);
    stepper.setCurrentPosition(0);
    delay(1000);
  }
  

}

int moveto (int deg, int rotspeed, int deltime)
{
  degfix = deg - lastpos;
  if (degfix < 0)
  {
    degfix = degfix + 360;
  }
  lastpos = deg;
  if (lastpos >= 360)
  {
    lastpos = lastpos - 360;
  }
  Serial.println(degfix); 
  int pos = map( degfix, 0, 360, 0, 2048);
    // Set target position:
  stepper.move(-pos);
   stepper.setSpeed(-rotspeed);
  // Run to position with set speed and acceleration:
  stepper.runToPosition();
   delay(deltime);
}
