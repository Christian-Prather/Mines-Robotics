/* a closed loop proportional control
   ms 20200926
*/
// Include Libraries
#include <PinChangeInt.h>

// Driver definitions

// If you have a kit with the moto shield, set this to true
// If you have the Dual H-Bridge controller w/o the shield, set to false
#define SHIELD false

//SHIELD Pin varables - cannot be changed
#define motorApwm 3
#define motorAdir 12
#define motorBpwm 11
#define motorBdir 13

//Driver Pin variable - any 4 analog pins (marked with ~ on your board)
#define IN1 9
#define IN2 10
#define IN3 5
#define IN4 6

// Lab Specific definitions

// Defining these allows us to use letters in place of binary when
// controlling our motors
#define A 0
#define B 1
#define pushButton 2 // install a Pullup button with its output into Pin 2
/* If you'd like to use additional buttons as bump sensors, define their pins 
 *  as descriptive names, such as bumperLeft etc. 
 */

// Drive constants - dependent on robot configuration
#define EncoderCountsPerRev 12.0
#define DistancePerRev 22.3
#define DegreesPerRev 22.3

//These are to build your moves array, a la Lab 2
#define FORWARD 0
#define LEFT 1
#define RIGHT -1

// these next two are the digital pins we'll use for the encoders
// You may change these as you see fit.
#define EncoderMotorLeft 7
#define EncoderMotorRight 8

// Proportional Control constants
// what are your ratios of PWM:Encoder Count error?
#define GAIN_A 5
#define GAIN_B 5
// how many encoder counts from your goal are accepteable?
#define distTolerance 3

// minimum power settings
// Equal to the min PWM for your robot's wheels to move
// May be different per motor
#define deadband_A 20
#define deadband_B 20

// Lab specific variables
volatile unsigned int leftEncoderCount = 0;
volatile unsigned int rightEncoderCount = 0;
int moves[] = {}; // Fill in this array will forward distances and turn directions in the maze (a la Lab 2)
// RIGHT param t is delay time calculated from dist and speed ratio
int calculateRunTime(int degrees)
{
  return (abs(degrees) / 90) * milliSecondsPer90Deg; //Time to keep motors on
}

void turnRight(int degrees)
{
  t = calculateRunTime(degrees) //Time to keep motors on

      run_motor(A, -motorA_PWM); //set this to a number between -255 and 255
  run_motor(B, motorB_PWM);      //set this to a number between -255 and 255
  delay(t);                      //set this to a time in ms for the motors to run
  run_motor(A, 0);               //motors stop
  run_motor(B, 0);
}

// LEFT param t is delay time calculated from dist and speed ratio
void turnLeft(int degrees)
{
  t = calculateRunTime(degrees);
  run_motor(A, motorA_PWM);  //set this to a number between -255 and 255
  run_motor(B, -motorA_PWM); //set this to a number between -255 and 255
  delay(t);                  //set this to a time in ms for the motors to run
  run_motor(A, 0);           //motors stop
  run_motor(B, 0);
}

void driveForward(int distance)
{
  unsigned long t;
  t = distance * milliSecondsPerCM; //Time to keep motors on

  //To drive forward, motors go in the same direction
  run_motor(A, motorA_PWM); //change PWM to your calibrations
  run_motor(B, motorB_PWM); //change PWM to your calibrations
  delay(t);
  run_motor(A, 0);
  run_motor(B, 0);
}

void motor_setup()
{
  // set up the motor drive ports
  pinMode(pwmA, OUTPUT);
  pinMode(dirA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(dirB, OUTPUT);
}

void setup()
{
  // set stuff up
  Serial.begin(9600);
  motor_setup();
  pinMode(pushButton, INPUT_PULLUP);

  // add additional pinMode statements for any bump sensors

  // Attaching Wheel Encoder Interrupts
  Serial.print("Encoder Testing Program ");
  Serial.print("Now setting up the Left Encoder: Pin ");
  Serial.print(EncoderMotorLeft);
  Serial.println();
  pinMode(EncoderMotorLeft, INPUT_PULLUP); //set the pin to input
  // this next line setup the PinChange Interrupt
  PCintPort::attachInterrupt(EncoderMotorLeft, indexLeftEncoderCount, CHANGE);
  // if you "really" want to know what's going on read the PinChange.h file :)
  /////////////////////////////////////////////////
  Serial.print("Now setting up the Right Encoder: Pin ");
  Serial.print(EncoderMotorRight);
  Serial.println();
  pinMode(EncoderMotorRight, INPUT_PULLUP); //set the pin to input
  PCintPort::attachInterrupt(EncoderMotorRight, indexRightEncoderCount, CHANGE);
} /////////////// end of setup ////////////////////////////////////

/////////////////////// loop() ////////////////////////////////////
void loop()
{

  while (digitalRead(pushButton) == 1)
    ; // wait for button push
  while (digitalRead(pushButton) == 0)
    ; // wait for button release
  for (int i = 0; i < sizeof(moves) / 2; i++)
  { // Loop through entire moves list
    if (moves[i] == LEFT)
    {
      // Temp degrees need to dynamically calc
      int degrees = 90;
      // Fill with code to turn left
      turnLeft(degrees);
    }
    else if (moves[i] == RIGHT)
    {
      // Temp degrees need to dynamically calc
      int degrees = 90;
      // Fill with code to turn right
      turnRight(degrees);
    }
    else
    {
      // Temp distance
      int distance = 100;

      driveForward(distance);
    }
    run_motor(A, 0);
    run_motor(B, 0);
    delay(1000);
  }
}
//////////////////////////////// end of loop() /////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
int drive(float distance)
{
  // create variables needed for this function
  int countsDesired, cmdLeft, cmdRight, errorLeft, errorRight;

  // Find the number of encoder counts based on the distance given, and the
  // configuration of your encoders and wheels

  // Revoulutoins needed for distance
  unsigned long int revolutionsRequired = distance / DistancePerRev;

  countsDesired = revolutionsRequired * EncoderCountsPerRev;

  // reset the current encoder counts
  leftEncoderCount = 0;
  rightEncoderCount = 0;

  // we make the errors greater than our tolerance so our first test gets us into the loop
  errorLeft = distTolerance + 1;
  errorRight = distTolerance + 1;

  // Begin PID control until move is complete
  while (errorLeft > distTolerance || errorRight > distTolerance)
  {
    // according to the PID formula, what should the current PWMs be?
    cmdLeft = ;
    cmdRight = ;

    // Set new PWMs
    run_motor(A, cmdLeft);
    run_motor(B, cmdRight);

    // Update encoder error
    errorLeft = ;
    errorRight = ;

    // If using bump sensors, check here for collisions
    // and call correction function

    /* Some print statements, for debugging
    Serial.print(errorLeft);
    Serial.print(" ");
    Serial.print(cmdLeft);
    Serial.print("\t");
    Serial.print(errorRight);
    Serial.print(" ");
    Serial.println(cmdRight);*/
  }
}
////////////////////////////////////////////////////////////////////////////////

// Write a function for turning with PID control, similar to the drive function

//////////////////////////////////////////////////////////

// If you want, write a function to correct your path due
// to an active bump sensor. You will want to compensate somehow
// for any wheel encoder counts that happend during this manuever

//////////////////////////////////////////////////////////
int computeCommand(int gain, int deadband, int error)
//  gain, deadband, and error, both are integer values
{
  if (error <= distTolerance)
  { // if error is acceptable, PWM = 0
    return (0);
  }

  int cmdDir = (gain * error);               // Proportional control
  cmdDir = constrain(cmdDir, deadband, 255); // Bind value between motor's min and max
}

//////////////////////////////////////////////////////////

// These are the encoder interupt funcitons, they should NOT be edited

void indexLeftEncoderCount()
{
  leftEncoderCount++;
}
//////////////////////////////////////////////////////////
void indexRightEncoderCount()
{
  rightEncoderCount++;
}
