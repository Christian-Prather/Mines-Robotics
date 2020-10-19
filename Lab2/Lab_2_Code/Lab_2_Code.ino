
/* Dead Reckoning
  20200117
  Program to get the ardbot to drive a predefined path
  jsteele, mshapiro, klarsen
*/

// Complete Tasks in Initial_Robot_Testing.ino first!!

/* Program TODO LIST
  1) Change the milliSecondsPerCM constant to the value you found in testing
  2) Change the milliSecondsPer90Deg constant to the value you found in testing
  3) Change the PWM of the forward function to the values you found in testing
  4) Write code for the button pause functionality
  5) Write your own turn function

  Note: type // to make a single line comment
        Comments are for the future you to understand how you wrote your code
*/

// Preprocessor Definitions

// If you have a kit with the moto shield, set this to true
// If you have the Dual H-Bridge controller w/o the shield, set to false
#define SHIELD false

// Defining these allows us to use letters in place of binary when
// controlling our motor(s)
#define A 0
#define B 1

//SHIELD Pin varables
#define motorApwm 3
#define motorAdir 12
#define motorBpwm 11
#define motorBdir 13

//Driver Pin variable
#define IN1 9
#define IN2 10
#define IN3 5
#define IN4 6

#define FORWARD 0
#define LEFT 1
#define RIGHT -1
#define pushButton 2
#define A 1
#define B 2
#define pwmA 3
#define dirA 12
#define pwmB 11
#define dirB 13

// PWM values for the motors 
#define motorA_PWM 185
#define motorB_PWM 200

#define SHIELD 0

// the following converts centimeters into milliseconds as long datatype
#define milliSecondsPerCM 54     //CHANGE THIS ACCORDING TO YOUR BOT
#define milliSecondsPer90Deg 900 //CHANGE THIS ACCORDNING TO YOUR BOT

// the itemized list of moves for the robot as a 1D array
// this setup assumes that all the turns are 90 degrees and that all motions are pairs of drives and turns.
int moves[] = {140, LEFT, 90, RIGHT, 60, RIGHT, 180, RIGHT, 100, LEFT, 60, RIGHT, 100, RIGHT, 150, RIGHT};

// RIGHT param t is delay time calculated from dist and speed ratio
void turnRight(int t)
{
  run_motor(A, -motorA_PWM); //set this to a number between -255 and 255
  run_motor(B, motorB_PWM);  //set this to a number between -255 and 255
  delay(t);                  //set this to a time in ms for the motors to run
  run_motor(A, 0);           //motors stop
  run_motor(B, 0);
}

// LEFT param t is delay time calculated from dist and speed ratio
void turnLeft(int t)
{
  run_motor(A, motorA_PWM);  //set this to a number between -255 and 255
  run_motor(B, -motorA_PWM); //set this to a number between -255 and 255
  delay(t);                  //set this to a time in ms for the motors to run
  run_motor(A, 0);           //motors stop
  run_motor(B, 0);
}

void setup()
{
  // set up the motor drive ports
  pinMode(pwmA, OUTPUT);
  pinMode(dirA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(dirB, OUTPUT);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT_PULLUP); //CHANGE TO INPUT_PULLUP
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop()
{
  int i, dist, dir;
  long time;
  while (digitalRead(pushButton) == 1)
    ;
  while (digitalRead(pushButton) == 0)
    ;
  //This for loop steps (or iterates) through the array 'moves'
  for (i = 0; i < sizeof(moves) / 2; i = i + 2)
  {

    while (digitalRead(pushButton))
    {
      // Do nothing but wait
      //Serial.println("Waiting");
    }

    delay(250);
    //Forward Leg of each step
    Serial.print("Step #:");
    Serial.println(i);
    dist = moves[i];
    Serial.print("Forward for");
    time = Forward(dist);
    Serial.print(time);
    Serial.println(" ms");
    delay(1000);

    //Turn Leg of each step
    Serial.print("Step #:");
    Serial.println(i + 1);
    dir = moves[i + 1];
    if (dir == LEFT)
    {
      time = Turn(90);
      Serial.print("turning LEFT ");
      Serial.print(time);
      Serial.println(" ms");
    }
    else
    {
      time = Turn(-90);
      Serial.println("turning RIGHT ");

      Serial.print(time);
      Serial.println(" ms");
    } // end of else motions conditional
    delay(1000);

  } // end of for loop
  Serial.println("That's All Folks!");
  delay(1000);
  exit(i);
} // the end

//////////////////////////////////////////////
unsigned long Forward(int distance)
{
  unsigned long t;
  t = distance * milliSecondsPerCM; //Time to keep motors on

  //To drive forward, motors go in the same direction
  run_motor(A, motorA_PWM); //change PWM to your calibrations
  run_motor(B, motorB_PWM); //change PWM to your calibrations
  delay(t);
  run_motor(A, 0);
  run_motor(B, 0);
  return (t);
}

//////////////////////////////////////////////
unsigned long Turn(int degrees)
{
  unsigned long t;
  int sign = degrees / abs(degrees);              //Find if left or right
  t = (abs(degrees) / 90) * milliSecondsPer90Deg; //Time to keep motors on

  if (sign == -1)
  {
    turnLeft(t);
  }
  else
  {
    turnRight(t);
  }

  return (t);
}
