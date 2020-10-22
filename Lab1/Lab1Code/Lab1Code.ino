/* another version of Digital Read
*  mshapiro 0842020
*/

#define pushButton 2 // install a Pullup button with its output into Pin 2

// If you have a kit with the moto shield, set this to true
// If you have the Dual H-Bridge controller w/o the shield, set to false
#define SHIELD false 

// Defining these allows us to use letters in place of binary when
// controlling our motor(s)
#define A 0
#define B 1

//SHIELD Pin varables - cannot be changed
#define motorApwm 3
#define motorAdir 12
#define motorBpwm 11
#define motorBdir 13

//Driver Pin variable - any 4 analog pins (marked with ~ on your board)
#define IN1 5
#define IN2 6
#define IN3 9
#define IN4 10
  
#define ledPin 13 //LED is connected to Pin 13

boolean buttonPushed = false; // set initial button variable to 0/false/Off

//variables used in loop
int buttonState = 0;

// time is being measured in milliseconds, which makes the numbers large
// the long variable type allows us to store/use big numbers
long starttime, stoptime, deltatime; 



// the setup routine runs once when you press reset:
void setup() {
    
  // set the pushbutton's pin as a pull-up input:
  pinMode(pushButton, INPUT_PULLUP);
  
  //set the LED pin as an output
  pinMode(ledPin, OUTPUT);
  
  //use pre-built functions for motor setup (found in 2nd tab above)
  motor_setup();
   
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);  // set the serial comm to 9600 BAUD
}

// the loop routine runs over and over again forever (or until reset button/loss of power):
void loop() {
  
  // read the input pin:
  buttonState = digitalRead(pushButton);
  
  if(buttonState == 0){ // If button is pushed
    run_motor(B, 255 * 1.0); // motor A is on at full speed (pwm = 0-255)
    digitalWrite(ledPin, HIGH); //turn LED on
    if (buttonPushed == false){ // we are coming out of the "OFF" state
      buttonPushed = true; // set new "ON" state
      starttime = millis(); // start timer
      Serial.print(starttime); // print start time
    }
  }
  else { // if button is not pushed
    run_motor(B, 0); //t urn motor off
    digitalWrite(ledPin, LOW); // turn LED off
    if (buttonPushed ==true) { // we are coming out of the "ON" state
      stoptime = millis(); //stop timer
      Serial.print(" ");
      Serial.print(stoptime); //print stop time
      buttonPushed = false; // set new "OFF" state
      deltatime = stoptime - starttime; // find time differnce
      //print results
      Serial.print("\t");
      Serial.println(deltatime);
    }
  }
  // Useful to debug button hardware:
  // print out the state of the button:
  //Serial.println(buttonState);
  delay(10);        // delay 10 ms in between reads for stability
}
