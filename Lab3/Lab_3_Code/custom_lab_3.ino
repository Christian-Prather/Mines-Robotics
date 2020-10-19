// Libraries
#include <PinChangeInt.h>

// Global Defines
#define IN1 9
#define IN2 10
#define IN3 5
#define IN4 6

#define A 0
#define B 1
#define pushButton 2

#define bump_forward 
#define bump_left
#define bump_right

// Drive constants - dependent on robot configuration
#define EncoderCountsPerRev 12.0
#define DistancePerRev 22.3
#define DegreesPerRev 22.3

// Lab specific variables
volatile unsigned int leftEncoderCount = 0;
volatile unsigned int rightEncoderCount = 0;
volatile unsigned int distanceTraveled = 0;

#define FORWARD 0
#define LEFT 1
#define RIGHT -1

#define BUMP_FORWARD 0
#define BUMP_LEFT 1
#define BUMP_RIGHT -1

int motorLeft_PWM = 180;
int motorRight_PWM = 200;

// Global array for tracking move order (move, distance) or (move, degree)
int moveList[] = {};

// Helper functions

void resetPWM()
{
    motorLeft_PWM = 180;
    motorRight_PWM = 200;
}

void indexLeftEncoderCount()
{
    leftEncoderCount++;
}
void indexRightEncoderCount()
{
    rightEncoderCount++;
}

int calculateRunTime(int degrees)
{
    return (abs(degrees) / 90) * milliSecondsPer90Deg; //Time to keep motors on
}

void turnRight(int degrees)
{
    resetPWM();
    // t = calculateRunTime(degrees) //Time to keep motors on
    while ((leftEncoderCount != desiredCount) || (rightEncoderCount != desiredCount))
    {
        adjustPWM();
        run_motor(A, -motorA_PWM); //set this to a number between -255 and 255
        run_motor(B, motorB_PWM);  //set this to a number between -255 and 255
    }

    run_motor(A, 0); //motors stop
    run_motor(B, 0);
}

// LEFT param t is delay time calculated from dist and speed ratio
void turnLeft(int degrees)
{
    resetPWM();
    // t = calculateRunTime(degrees);

    while ((leftEncoderCount != desiredCount) || (rightEncoderCount != desiredCount))
    {
        adjustPWM();
        run_motor(A, motorA_PWM);  //set this to a number between -255 and 255
        run_motor(B, -motorA_PWM); //set this to a number between -255 and 255
    }

    run_motor(A, 0); //motors stop
    run_motor(B, 0);
}

void driveForward(int distance)
{
    resetPWM();
    // unsigned long t;
    // t = distance * milliSecondsPerCM; //Time to keep motors on

    int desiredCount;
    unsigned long int revolutionsRequired = distance / DistancePerRev;

    // TODO: Need to add a buffer here or will never exit this loop
    desiredCount = revolutionsRequired * EncoderCountsPerRev;
    // Loop unitl the encoders read correct
    while ((leftEncoderCount != desiredCount) || (rightEncoderCount != desiredCount))
    {
        adjustPWM();

        // t = distance * milliSecondsPerCM; //Time to keep motors on

        //To drive forward, motors go in the same direction
        run_motor(A, motorA_PWM); //change PWM to your calibrations
        run_motor(B, motorB_PWM); //change PWM to your calibrations
        // delay(t);
        // run_motor(A, 0);
        // run_motor(B, 0);
    }
}

void driveBackward(int distance)
{
    resetPWM();
    // unsigned long t;
    // t = distance * milliSecondsPerCM; //Time to keep motors on

    int desiredCount;
    unsigned long int revolutionsRequired = distance / DistancePerRev;

    // TODO: Need to add a buffer here or will never exit this loop
    desiredCount = revolutionsRequired * EncoderCountsPerRev;
    // Loop unitl the encoders read correct
    while ((leftEncoderCount != desiredCount) || (rightEncoderCount != desiredCount))
    {
        adjustPWM();

        // t = distance * milliSecondsPerCM; //Time to keep motors on

        //To drive forward, motors go in the same direction
        run_motor(A, -motorA_PWM); //change PWM to your calibrations
        run_motor(B, -motorB_PWM); //change PWM to your calibrations
        // delay(t);
        // run_motor(A, 0);
        // run_motor(B, 0);
    }
}

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

    pinMode(bumpForward, INPUT_PULLUP);
    PCintPort::attachInterrupt(bumpForward, react_forward, CHANGE);

    pinMode(bumpLeft, INPUT_PULLUP);
    PCintPort::attachInterrupt(bumpLeft, react_left, CHANGE);

    pinMode(bumpRight, INPUT_PULLUP);
    PCintPort::attachInterrupt(bumpRight, react_forward, CHANGE);
}

void idle()
{
    while (digitalRead(pushButton) == 1)
        ; // wait for button push
    while (digitalRead(pushButton) == 0)
        ; // wait for button release
}

void adjustPWM()
{
    // Adjust the pwm values based on the encoders similarity
    if (leftEncoderCount > rightEncoderCount)
    {
        // The left wheel is spinning more than the right
        // Speed up the right wheel by ratio
        int delta = leftEncoderCount - rightEncoderCount;
        // Keep it from overshooting 255
        motorRight_PWM = min(motorRight_PWM + (deltat * 10), 255);
    }
    if (leftEncoderCount < rightEncoderCount)
    {
        int delta = rightEncoderCount - leftEncoderCount;
        motorLeft_PWM = min(motorLeft_PWM + (delta * 10), 255)
    }
}

void setup()
{
    Serial.Println("Setting up.....");
    configure();
}

/* Inrementally check that the bot is on track with the distance it should be traveling
*   Need to know what percent of distance we have taveled 
*   Take calculated distance and use it to determine the revolutions that should of been seen
*   Calculate the error offest and adjust to feed into pid loop
*/

/**
 * @brief This is the logic to execute if we hit a push button
 * ideally this is never executed as we shoudl never actually hit the walls
 * 
 */
void react_left()
{
    // Check which button was hit

    driveBackward(20);
    turnRight(30);
}
void react_right()
{
    // Check which button was hit

    driveBackward(20);
    turnLeft(30);
}
void react_forward()
{
    // Check which button was hit
    driveBackward(50);
}

void drive()
{
    idle();
    // Iterate over the list jumping by two each time
    for (int i = 0; i < sizeof(moveList); i += 2)
    {
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

void loop()
{
    drive();
}