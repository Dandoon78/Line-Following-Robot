/*
  Line Following Robot
  
  This program will use two motors and two sensors to follow a black line on a white board. At intersections
  the robot will make a noticable stop. Once it reaches the end of the first lap, it will make a 180 degree 
  turn and make its way back. Once it reaches the end of the second lap, the robot will stop. 
  
  Made by : Daniel Roufail
  
  June 17, 2022
  
  Version 2
*/

// Setting up variables/constants

// An array called "motorPins" is declared to hold all the motor pins
// It uses the data type "byte" because all the values fall between 0 and 255
byte motorPins[] = {5, 6, 9, 10};

// A variable called "counter" is declared for the array index
// This will be used to cycle through all the pins in the array
// It uses the data type "byte" because all the possible values fall between 0 and 255
byte counter;

// A constant called "rightSens" is set for the right sensor pin
// It uses the data type "byte" because the value falls between 0 and 255
byte rightSens = A3;

// a constant called "leftSens" is set for the left sensor pin
// It uses the data type "byte" because the value falls between 0 and 255
byte leftSens = A5;

// The variable "senseReadL" is declared to store the left sensor's value
// It uses the data type "int" because all its possible values fall between -32768 and 32767
int senseReadL;

// The variable "senseReadR" is declared to store the right sensor's value
// It uses the data type "int" because all its possible values fall between -32768 and 32767
int senseReadR;

// A constant for the number of laps the robot will do
// It uses the data type "byte" because the value falls between 0 and 255
byte rounds = 1;


// Setting up the pins
// Runs code only once
void setup() {
  
  // Sets the right and left sensors' pins as input pins
  // This means the pins will be recieving values from the sensor
  pinMode(rightSens, INPUT);
  pinMode(leftSens, INPUT);

  // Setting up motor pins as output pins
  // This means there will be power sent out from these pins to the motor controller
  for (counter = 0; counter < 4; counter++) {
    pinMode(motorPins[counter], OUTPUT);
  } 

}

// Runs code infinitly
void loop() {
  
  // Getting sensor values 
  // The left sensor values are stored in the variable "senseReadL"
  // The right sensor values are stored in the variable "senseReadR"
  senseReadL = analogRead(leftSens);
  senseReadR = analogRead(rightSens);
  
  // With the resistor added the value of white for both sensors is 30
  // The value for black for both sensors is 145
  // This means when checking to see if the sensors are white, the value is < 88 and for black it is > 88
  
  // If both sensors sense white the robot will move straight move straight
  if (senseReadR < 88 and senseReadL < 88) {
    
    // Sends power to the pins 6 and 9 while pins 5 and 10 do not receive any
    digitalWrite(motorPins[0], LOW);
    digitalWrite(motorPins[3], LOW);
    digitalWrite(motorPins[1], HIGH);
    digitalWrite(motorPins[2], HIGH);
    
    // A delay is added for .02 seconds to give the motors and sensors time to react
    delay(20);
  }

  // If both sensors sense black, it will stop for 2 seconds then move straight for 0.5 seconds
  else if (senseReadR > 88 and senseReadL > 88) {
    
    // Turns the pins 6 and 9 off
    digitalWrite(motorPins[1], LOW);
    digitalWrite(motorPins[2], LOW);
    
    // Adds a delay for 2 seconds so that the robot stops for that amount of time
    delay(2000);
    
    // Sends power to the pins 6 and 9
    digitalWrite(motorPins[1], HIGH);
    digitalWrite(motorPins[2], HIGH);
    
    // Adds a delay of 0.5 seconds to allow the robot to get off the black before sensing again
    delay(500);
    
    // Reads the values of the sensors again and stores them in the same variables
    senseReadL = analogRead(leftSens);
    senseReadR = analogRead(rightSens);
    
    // If both sensors sense black again during round 1, make a 180 degree turn
    // This means it has reached the end of the first lap
    if (senseReadR > 88 and senseReadL > 88 and rounds == 1) {
      
      // The robot will make a tank turn
      // This is done by sending power to pins 5 and 9 while cutting the power from pin 6
      digitalWrite(motorPins[1], LOW);
      digitalWrite(motorPins[0], HIGH);
      digitalWrite(motorPins[2], HIGH);
      
      // Adds a 2.5 second delay to show how long the pins need to be on to complete the turn
      delay(2500);
      
      // The robot will then move straight for .1 seconds to realign itself
      // This is done by turning pin 5 off and by sending power to pins 6 and 9
      digitalWrite(motorPins[0], LOW);
      digitalWrite(motorPins[1], HIGH);
      digitalWrite(motorPins[2], HIGH);
      
      // There is a delay added for .1 seconds
      delay(100);
      
      // This shows the counter for the end of the first lap
      rounds += 1;
    }
    
    // if it is both black again but round 2, make a stop for 10 seconds
    else if (senseReadR > 88 and senseReadL > 88 and rounds > 1) {
      
      // Turns both pins 6 and 9 off
      digitalWrite(motorPins[1], LOW);
      digitalWrite(motorPins[2], LOW);
      
      // Adds a delay for 10 seconds
      delay(10000);
      
      // Represents the end of the second lap
      rounds = 1;
    }
  }
  
  // if the right sensor senses black, the left motor is turned on
  // This is used to align the robot when it makes turns
  else if (senseReadR > 88){
    
    // Turns on pin 6 and turns off pin 9
    digitalWrite(motorPins[2], LOW);
    digitalWrite(motorPins[1], HIGH);
    
    // Adds a delay for 0.02 seconds to give time for the sensors and motors to react
    delay(20);
  }
  
  // if the left sensor senses black, the right motor is turned on 
  // This is used to align the robot when it makes turns
  else if (senseReadL > 88){
    
    // Turns on pin 9 and turns off pin 6
    digitalWrite(motorPins[1], LOW);
    digitalWrite(motorPins[2], HIGH);
    
    // Adds a delay for 0.02 seconds to give time for the sensors and motors to react
    delay(20);
  }
  
}

