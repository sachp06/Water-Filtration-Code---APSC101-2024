#include <AFMotor.h>
#include <Servo.h>
#define Estop 21

// Create motor objects for M2 (pump) and SERVO1
AF_DCMotor motor(1);      // COnnect DC motor to M2
AF_DCMotor pump(4);       // Connect Perilstatic pump to M4
AF_DCMotor cfpump(2);     // Connect centrifugal pump to M2

Servo servoMotor;         // Servo motor connected to SERVO1

// Pin assignments
const int buttonPin = A2;       // Pushbutton pin on analog pin A2
const int capacitivePin = 52;   // Capacitive sensor pin on digital pin 52

// State variables
bool pumpRunning = false;       // Flag to indicate pump running state
bool buttonPressed = false;     // Flag to indicate butto press
bool motorRunning = false;      //Flag to indicate whether the motor is running
bool Level=LOW;                 //Stores value given from water level sensor
bool CPumpRunning = false;      //Flag to indicate whether centrifugal pump is running
bool didServoTurn = false;      //Flag to indicate whether servo motor has turned
int increment = 0;
bool motorRan = false; 
bool cPumpRan = false; 

void setup() {
  pinMode(Estop, INPUT_PULLUP); // define pin 21 as an input pin with a pullup resistor
  attachInterrupt(digitalPinToInterrupt(Estop), estop, FALLING);
  // this line tells the Arduino to call the function “estop” when the
  // “Estop” pin (21) sees a falling edge, i.e. the button is pushed. 


  Serial.begin(9600);           // Start serial communication for debugging

  // Set up pins
  pinMode(buttonPin, INPUT_PULLUP);  // Enable internal pull-up resistor on button pin
  pinMode(capacitivePin, INPUT_PULLUP);

  // Initialize the pump motor speed (0 to 255)
  pump.setSpeed(150);

  // Attach the servo motor to SERVO2 pin on pin 9
  servoMotor.attach(9);

  // Ensure the pump is off at the start
  stopPump();
  resetServo();
  stopCPump();
}

void loop() {
  int sensor1 = analogRead(A0);// read the input on analog pin 0
  float voltage1 = sensor1 * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
  int sensor2 = analogRead(A1);
  float voltage2 = sensor2 * (5.0 / 1024.0);

  Serial.println(buttonPressed);
  Level=digitalRead(capacitivePin);

  Serial.print("Initial voltage ");
  Serial.println(voltage1);
  Serial.print("Final voltage ");
  Serial.println(voltage2);

  if (Level==HIGH) Serial.print("No object near sensor");
  else if (Level==LOW) Serial.print("Object near sensor");


  // Check the button state (inverted logic due to pull-up resistor)
  if (digitalRead(buttonPin) == LOW && !buttonPressed) {   // Button is pressed when LOW
    buttonPressed = true;       // Update the flag
    Serial.println("Starting pump.");
    startCPump();
    cPumpRan = false;
  }

  // Check the capacitive sensor state
  if (digitalRead(capacitivePin) == HIGH && CPumpRunning) {
    Serial.println("Stopping pump.");
    stopCPump();
    cPumpRan = true;
  }

  // Control the servo based on pump status
  if (cPumpRan == true) {
    startServo();
    delay(500);
    resetServo();
    delay(2000);
    startMotor();
    delay(6000);
    stopMotor();
    cPumpRan = false; 
    didServoTurn = true; 
    increment++;
     // Start some action by moving servo to a new position
  } else if(cPumpRan == false && didServoTurn == false) {
    resetServo();
    cPumpRan = false; // Stop some action by moving servo to a new position
  }

  if(motorRan == true /*&& voltage1 <*/ ){
    int sensor1 = analogRead(A0);// read the input on analog pin 0
    float voltage1 = sensor1 * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
    int sensor2 = analogRead(A1);
    float voltage2 = sensor2 * (5.0 / 1024.0);
    delay(60000);
    startPump();
    delay(160000);
    //stopPump();
    motorRan = false; 
  }

  /*if(CPumpRunning == 0){
    startMotor();
    delay(6000);
    stopMotor();
  }*/
  // Reset button flag after release
  if (digitalRead(buttonPin) == HIGH) {  // Button is released when HIGH
    buttonPressed = false;
  }

  

  /*if(didServoTurn == true){
    stopCPump();
    delay(5000);
    startMotor();
    delay(6000);
    stopMotor();
  }*/

  delay(100);                   // Small delay for debouncing

  //Starts motor for 5 second(mixing assembly)
  
}

// Function to start the pump
void startPump() {
  pumpRunning = true;
  pump.setSpeed(150);
  Serial.println("Pump started");
}

// Function to stop the pump
void stopPump() {
  pumpRunning = false;
  pump.setSpeed(0);
  Serial.println("Pump stopped");
}

// Function to move the servo motor to new position
void startServo() {
  didServoTurn = true; 
  servoMotor.write(90);         // Move servo to 90 degrees (adjust as needed)
//  Serial.println("Servo motor started at 90 degrees");
}

// Function to stop the servo motor
void resetServo() {
  servoMotor.write(0);          // Move servo to 0 degrees (adjust as needed)
 // Serial.println("Servo motor stopped at 0 degrees");
}

/***NEWLY ADDED CODE***/

//Funtion to start DC motor
void startMotor(){ 
  Serial.print("Starting motor.");
  motor.setSpeed(100); //Set speed to 255
  motor.run(FORWARD);
}

void stopMotor(){
  motor.setSpeed(0);
  motorRan = true; 
  didServoTurn = false;
}

void startCPump(){
  CPumpRunning = true; 
  cfpump.setSpeed(255);
  cfpump.run(FORWARD);

}

void stopCPump(){
  CPumpRunning = false; 
  cfpump.setSpeed(0);
  cfpump.run(FORWARD);
}

void estop() // this is an interrupt subroutine, that will be called if pin 21 is LOW
// i.e. the button is pushed.
{
// add commands here that stop all the motors and pumps in your system
while(1){
  cfpump.setSpeed(0);
  motor.setSpeed(0);
  pump.setSpeed(0);


} // This will prevent the Arduino from returning to the main loop and doing
// anything after the button is pressed
}
