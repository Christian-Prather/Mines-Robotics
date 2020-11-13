/**
   @file custom_lab_4.ino
   @author Christian Prather
   @brief A basic feedback controlled system for an Arduino based robot with ultrasonic 
          and IR distance sensors
   @version 0.1
   @date 2020-10-23

*/


/*! \mainpage Lab 4 Code Documentation
 *
 */

/// Libraries for interrupts and PID
#include <PinChangeInt.h>
#include <PID_v1.h>
#include <SR04.h>

/// Global Defines
/// Motor driver connections
#define IN1 5
#define IN2 6
#define IN3 7
#define IN4 8

/// Motor control
#define A 0
#define B 1
#define pwmA 3
#define dirA 9
#define pwmB 4
#define dirB 13

/// Start stop button
#define pushButton 2

/// Drive constants - dependent on robot configuration
#define EncoderCountsPerRev 12.0
#define DistancePerRev 51.0
#define DegreesPerRev 27.0

#define EncoderMotorLeft 7
#define EncoderMotorRight 8

/// Lab specific variables
double leftEncoderCount = 0;
double rightEncoderCount = 0;
int wallDist = 5; /// CM
#define DISTANCE_SEG 10

/// Enum defines
#define FORWARD 0
#define RIGHT 1
#define LEFT 2

/// IR sensors
int irSensor = A0;

/// Ultrasonic sensors
int trig = 12;
int echo = 11;
SR04 sideUS = SR04(trig, echo);

/// Default motor pwm values
int motorLeft_PWM = 180;
int motorRight_PWM = 200;

/// Time it takes to move 90 degrees
int milliSecondsPer90Deg = 900;

/// How many encoder counts for given distance
double desiredCount;

int movesCount = 0;
// Global array for tracking move order (move, distance) or (move, degree)
int moveList[50];

int optimizedMoves[50];

/**
   @brief PID values
   setpoints = desired counts, output = PWM, input = current counts
*/
double leftOutput, rightOutput;
PID leftPID(&leftEncoderCount, &leftOutput, &desiredCount, 2, 5, 2, DIRECT);
PID rightPID(&rightEncoderCount, &rightOutput, &desiredCount, 2, 5, 2, DIRECT);

/**
   @brief Helper function for setting the PWM back to default value
*/
void resetPWM()
{
    motorLeft_PWM = 180;
    motorRight_PWM = 200;
}

/**
   @brief Run the PID loop calculation and set out put to motors output in PWM

*/
void adjustPWM()
{
    // Compute the pid values
    leftPID.Compute();
    rightPID.Compute();

    // Set the pid values within range
    motorLeft_PWM = constrain(leftOutput, 150, 250);
    motorRight_PWM = constrain(rightOutput, 150, 235);
    Serial.print("Left PWM: ");
    Serial.print(motorLeft_PWM);
    Serial.print(" ");
    Serial.println(leftEncoderCount);
    Serial.print("Right PWM: ");
    Serial.print(motorRight_PWM);
    Serial.print(" ");
    Serial.println(rightEncoderCount);
}

/**
   @brief ISR for left encoder
*/
void indexLeftEncoderCount()
{
    leftEncoderCount++;
    //Serial.println("Left Encoder ++");
}

/**
   @brief ISR for incrementing right encoder
*/
void indexRightEncoderCount()
{
    rightEncoderCount++;
    //Serial.println("Right Encoder ++");
}

/**
   @brief Calculate how many encoder counts we expect given the distance provided
   based on the bot intrinsics

   @param distance
*/
void calculateDesiredCount(int distance)
{
    double revolutionsRequired = distance / DistancePerRev;

    desiredCount = revolutionsRequired * EncoderCountsPerRev;
    // Reset encoder counts
    leftEncoderCount = 0;
    rightEncoderCount = 0;
    Serial.print("Desired Count: ");
    Serial.println(desiredCount);
}

/**
 * @brief Calculate how many encoder counts we expect given the degrees provided
 * 
 * @param degrees 
 */
void calculateDesiredCountTurn(int degrees)
{
    double revolutionsRequired = degrees / DegreesPerRev;
    desiredCount = revolutionsRequired * EncoderCountsPerRev;
    leftEncoderCount = 0;
    rightEncoderCount = 0;
    Serial.print("Desired Count: ");
    Serial.println(desiredCount);
}

/**
   @brief Turn bot to given degrees

   @param degrees
*/
void turnRight(int degrees)
{
    resetPWM(); // Reset pwm
    calculateDesiredCountTurn(degrees);
    // While the encoders are not correct adjust PWM with PID loop
    // Loop unitl the encoders read correct

    while ((desiredCount - rightEncoderCount) > 3)
    {
        adjustPWM();
        //To drive forward, motors go in the same direction

        if ((desiredCount - leftEncoderCount) > 3)
        {
            run_motor(A, -motorLeft_PWM); //change PWM to your calibrations
        }
        if ((desiredCount - rightEncoderCount) > 3)
        {
            run_motor(B, motorRight_PWM); //change PWM to your calibrations
        }
    }

    // motors stop
    run_motor(A, 0);
    run_motor(B, 0);
    Serial.println("Done driving Right");
    Serial.print("L: ");
    Serial.println(leftEncoderCount);
    Serial.print("R: ");
    Serial.println(rightEncoderCount);
}

/**
   @brief Turn bot right to given degrees

   @param degrees
*/
void turnLeft(int degrees)
{
    resetPWM();
    calculateDesiredCountTurn(degrees);

    // Loop unitl the encoders read correct

    while ((desiredCount - leftEncoderCount) > 3)
    {
        adjustPWM();
        //To drive forward, motors go in the same direction

        if ((desiredCount - leftEncoderCount) > 3)
        {
            run_motor(A, motorLeft_PWM); //change PWM to your calibrations
        }
        if ((desiredCount - rightEncoderCount) > 3)
        {
            run_motor(B, -motorRight_PWM); //change PWM to your calibrations
        }
    }

    // motors stop
    run_motor(A, 0);
    run_motor(B, 0);
    Serial.println("Done driving Left");
    Serial.print("L: ");
    Serial.println(leftEncoderCount);
    Serial.print("R: ");
    Serial.println(rightEncoderCount);
}

/**
   @brief Function to drive bot forward until encoders are within range

   @param distance
*/
void driveForward(int distance)
{
    Serial.println("Driving Forward...");
    resetPWM();
    calculateDesiredCount(distance);

    // Loop unitl the encoders read correct

    while ((desiredCount - leftEncoderCount) > 3 || (desiredCount - rightEncoderCount) > 3)
    {
        adjustPWM();
        //To drive forward, motors go in the same direction

        if ((desiredCount - leftEncoderCount) > 3)
        {
            run_motor(A, -motorLeft_PWM); //change PWM to your calibrations
        }
        if ((desiredCount - rightEncoderCount) > 3)
        {
            run_motor(B, -motorRight_PWM); //change PWM to your calibrations
        }
    }

    // motors stop
    run_motor(A, 0);
    run_motor(B, 0);
    Serial.println("Done driving forward");
    Serial.print("L: ");
    Serial.println(leftEncoderCount);
    Serial.print("R: ");
    Serial.println(rightEncoderCount);
}

/**
   @brief Drive the bot backwards

   @param distance
*/
void driveBackward(int distance)
{
    resetPWM();
    calculateDesiredCount(distance);

    // Loop unitl the encoders read correct

    while ((desiredCount - leftEncoderCount) > 3 || (desiredCount - rightEncoderCount) > 3)
    {
        adjustPWM();
        //To drive backward, motors go in the same direction

        if ((desiredCount - leftEncoderCount) > 3)
        {
            run_motor(A, motorLeft_PWM); //change PWM to your calibrations
        }
        if ((desiredCount - rightEncoderCount) > 3)
        {
            run_motor(B, motorRight_PWM); //change PWM to your calibrations
        }
    }

    // motors stop
    run_motor(A, 0);
    run_motor(B, 0);
    Serial.println("Done driving backwards");
    Serial.print("L: ");
    Serial.println(leftEncoderCount);
    Serial.print("R: ");
    Serial.println(rightEncoderCount);
}

/**
 * @brief Function for reading the distance sensors 
 * 
 * @param sensor 0 = IR, 1 = Ultrasonic
 * @return float distance (cm)
 */
float readDistance(int sensor)
{
    float distance = 0.0;
    switch (sensor)
    {
    case 0:
        int reading = analogRead(irSensor);
        distance = ((0.00031) * reading) + 0.002;
        break;
    case 1:
        distance = sideUS.Distance();
        break;

    default:
        break;
    }
    return distance;
}

/**
 * @brief The exploritory function to allow the system to navigate unseen envioronment
 * Using left hand rule
 */
void explore()
{
    while (digitalRead(pushButton) == 1)
    {
        float front = readDistance(0);
        float side = readDistance(1);

        /// There is no wall to left of bot
        if (side > wallDist)
        {
            turnLeft(90);
            /// Not recording degrees as the assumption is every turn on 90 degrees
            moveList[movesCount] = "LEFT";
            movesCount++;
        }
        /// Can drive forward
        else if (front > wallDist)
        {
            driveForward(DISTANCE_SEG);
            moveList[movesCount] = "FORWARD";
            movesCount++;
        }
        /// Trapped turn Right
        else
        {
            turnRight(90);
            moveList[movesCount] = "RIGHT";
            movesCount++;
        }
    }
}

/**
 * @brief This is what youve all been waiting for one darn good looking 
 * solution to maze optimation. Iterates over the movesList looking for 
 * specific patterns it can reduce into simpler sequences
 * Key assumption: Explored using Left hand rule
 */
void optimize()
{
    /// Key patterns 0 = F, 1 = R, 2 = L, 3 = DELETE
    int keyPatterns_6[2][6] = {{0, 0, 1, 1, 0, 0}, {2, 0, 1, 1, 0, 2}};
    int keyPatterns_5[2][5] = {{2, 0, 1, 1, 0}, {0, 1, 1, 0, 2}};
    int keyPatterns_4[1][4] = {{0, 1, 1, 0}};

    int optimizedPattern_6[1][8] = {{FORWARD, 2 * DISTANCE_SEG, RIGHT, 90, RIGHT, 90, FORWARD, DISTANCE_SEG}};
    int optimizedPattern_5[2][2] = {{RIGHT, 90}, {RIGHT, 90}};
    int optimizedPatter_4[1][4] = {{LEFT, 90, LEFT, 90}};
    /** This is going to be checking in a priority tree fashion given highest priority
    * given highest priority patterns are 6 long then 5 long then 4 I can batch this
    */
    for (int i = 0; i < movesCount; i++)
    {
        /// Get next move in explored list
        // int move = moveList[i];
        /// Get next 6 moves if enough in list

        // Check 6 out first
        int future[6];
        for (int j = 0; j < 6; j++)
        {
            if ((j + i) < movesCount)
            {
                future[j] = moveList[j + i];
            }
        }
        int tracker = 0;
        for (auto potential : keyPatterns_6)
        {
            bool match = true;
            for (int m = 0; m < 6; m++)
            {
                if (future[m] != potential[m])
                {
                    match = false;
                }
            }
            if (match)
            {
                int keyPatternLength = (sizeof(potential) / sizeof(potential[0]));
                // Insert optimized move
                for (int x = 0; x < (sizeof(optimizedPattern_6[tracker]) / sizeof(optimizedPattern_6[tracker][0])); x++)
                {
                    if (optimizedPattern_6[tracker][x] != 3)
                    {
                        optimizedMoves[x] = optimizedPattern_6[tracker][x];
                    }
                }
                i = i + 6;
                break;
            }
            tracker = tracker + 1;
        }

        //////////////////////////////////////////////////////////////////////////////
        // Check 5 out first
        int future_5[5];
        for (int j = 0; j < 5; j++)
        {
            if ((j + i) < movesCount)
            {
                future_5[j] = moveList[j + i];
            }
        }
        tracker = 0;
        for (auto potential : keyPatterns_6)
        {
            bool match = true;
            for (int m = 0; m < 5; m++)
            {
                if (future_5[m] != potential[m])
                {
                    match = false;
                }
            }
            if (match)
            {
                int keyPatternLength = (sizeof(potential) / sizeof(potential[0]));
                // Insert optimized move
                for (int x = 0; x < (sizeof(optimizedPattern_6[tracker]) / sizeof(optimizedPattern_6[tracker][0])); x++)
                {
                    if (optimizedPattern_6[tracker][x] != 3)
                    {
                        optimizedMoves[x] = optimizedPattern_6[tracker][x];
                    }
                }
                i = i + 5;
                break;
            }
            tracker = tracker + 1;
        }

        //////////////////////////////////////////////////////////////////////////////
        // Check 4 out first
        int future_4[4];
        for (int j = 0; j < 4; j++)
        {
            if ((j + i) < movesCount)
            {
                future_4[j] = moveList[j + i];
            }
        }
        tracker = 0;
        for (auto potential : keyPatterns_6)
        {
            bool match = true;
            for (int m = 0; m < 4; m++)
            {
                if (future_4[m] != potential[m])
                {
                    match = false;
                }
            }
            if (match)
            {
                int keyPatternLength = (sizeof(potential) / sizeof(potential[0]));
                // Insert optimized move
                for (int x = 0; x < (sizeof(optimizedPattern_6[tracker]) / sizeof(optimizedPattern_6[tracker][0])); x++)
                {
                    if (optimizedPattern_6[tracker][x] != 3)
                    {
                        optimizedMoves[x] = optimizedPattern_6[tracker][x];
                    }
                }
                i = i + 4;
                break;
            }
            tracker = tracker + 1;
        }
    }
}


/**
   @brief Function for configuration of pin states and interrupts
*/
void configure()
{
    // set up the motor drive ports
    pinMode(pwmA, OUTPUT);
    pinMode(dirA, OUTPUT);
    pinMode(pwmB, OUTPUT);
    pinMode(dirB, OUTPUT);

    pinMode(pushButton, INPUT_PULLUP);

    pinMode(EncoderMotorLeft, INPUT_PULLUP); //set the pin to input
    PCintPort::attachInterrupt(EncoderMotorLeft, indexLeftEncoderCount, CHANGE);

    pinMode(EncoderMotorRight, INPUT_PULLUP); //set the pin to input
    PCintPort::attachInterrupt(EncoderMotorRight, indexRightEncoderCount, CHANGE);
}

/**
   @brief Default behavior when not driving, waits for the pushButton to
   be pressed so it can execute next command
   Blocking function
*/
void idle()
{
    Serial.println("Idle..");
    while (digitalRead(pushButton) == 1)
        ; // wait for button push
    while (digitalRead(pushButton) == 0)
        ;        // wait for button release
    delay(2000); // Give time to move hand
}

/**
   @brief Entry point of program handles serial setup and PID config
*/
void setup()
{
    Serial.begin(9600);
    Serial.println("Setting up.....");
    configure();
    leftPID.SetMode(AUTOMATIC);
    rightPID.SetMode(AUTOMATIC);
}

/**
   @brief This is the logic to execute if we hit a push button
   ideally this is never executed as we shoudl never actually hit the walls
*/
void react_left()
{
    // TODO: Check which button was hit

    driveBackward(20);
    turnRight(30);
}
void react_right()
{
    // TODO: Check which button was hit

    driveBackward(20);
    turnLeft(30);
}
void react_forward()
{
    // TODO: Check which button was hit
    driveBackward(50);
}

/**
   @brief Main drive execution of program, iterates through moves list executing
   next move with corresponding distance or degrees
*/
void drive()
{
    // Iterate over the list jumping by two each time
    for (int i = 0; i < sizeof(optimizedMoves); i += 2)
    {
        idle();
        switch (moveList[i])
        {
        case LEFT:
            turnLeft(moveList[i + 1]);
            break;
        case RIGHT:
            turnRight(moveList[i + 1]);
            break;
        case FORWARD:
            driveForward(moveList[i + 1]);
            break;
        default:
            break;
        }
    }
    
}

/**
   @brief Loop execution of the program
*/
void loop()
{
    explore();
    optimize();
    drive();
}
