

/* a closed loop proportional control
   ms 20200926
*/
// Include Libraries
#include <PinChangeInt.h>
// If using any Ultrasonic Distance Sensors
#include <SR04.h>

////////////////////////////////////////////////////
// Copy constants and definitions from Lab 3
////////////////////////////////////////////////////

// Define IR Distance sensor Pins
#define frontIR A0
#define sideIR  A1

// If using any Ultrasonic - change pins for your needs
#define trig 4
#define echo 5
// if side dist is Ultrasonic
SR04 sideUS = SR04(trig, echo);
// if front dist is Ultrasonic
//SR04 frontUS = SR04(trig, echo);

// Define the distance tolerance that indicates a wall is present
#define wallTol 5 //cm

int moves[50]; // Empty array of 50 moves, probably more than needed, just in case

void setup() {
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
  pinMode(EncoderMotorRight, INPUT_PULLUP);     //set the pin to input
  PCintPort::attachInterrupt(EncoderMotorRight, indexRightEncoderCount, CHANGE);
} /////////////// end of setup ////////////////////////////////////

/////////////////////// loop() ////////////////////////////////////
void loop()
{

  while (digitalRead(pushButton) == 1); // wait for button push
  while (digitalRead(pushButton) == 0); // wait for button release
  explore();
  run_motor(A, 0);
  run_motor(B, 0);
  solve();
  while (1) { //Inifnite number of runs, so you don't have to re-explore everytime a mistake happens
    while (digitalRead(pushButton) == 1); // wait for button push
    while (digitalRead(pushButton) == 0); // wait for button release
    runMaze();
    run_motor(A, 0);
    run_motor(B, 0);
  }
}
////////////////////////////////////////////////////////////////////////////////
float readFrontDist() { 
  // If IR distance sensor
  int reading = analogRead(frontIR);
  float dist = // Equation from your calibration;

  // if Ultrasonic
  // float dist = frontUS.Distance(); //(returns in cm)

  return dist;
}
////////////////////////////////////////////////////////////////////////////////
float readSideDist() {
  // If IR distance sensor
  int reading = analogRead(sideIR);
  float dist = // Equation from your calibration;

  // IF Ultrasonic
  // float dist = sideUS.Distance(); //(returns in cm)
  
  return dist;
}
//////////////////////////////// end of loop() /////////////////////////////////
void explore() {
  while (digitalRead(pushButton) == 1) { //while maze is not solved
    // Read distances
    float side = readSideDist();
    float front = readFrontDist();
    if (side > wallTol) {// If side is not a wall
      // turn and drive forward
      // Record actions
    }
    else if (front > wallTol) {// else if front is not a wall
      // drive forward
      // Record action
    } else {
      // turn away from side
      // Record action
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
void solve() {
  // Write your own algorithm to solve the maze using the list of moves from explore
}
////////////////////////////////////////////////////////////////////////////////
void runMaze() {
  for(int i = 0; i < sizeof(maze)/2; i++){
    // copy for loop from Lab 3 to run through finished maze path
  }
}
////////////////////////////////////////////////////////////////////////////////
// Copy your drive function from Lab 3
////////////////////////////////////////////////////////////////////////////////
// Copy your turn function from Lab 3
//////////////////////////////////////////////////////////
// Copy your reactive functions from Lab 3
//////////////////////////////////////////////////////////
// Copy your computeCommand function from Lab 3
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
