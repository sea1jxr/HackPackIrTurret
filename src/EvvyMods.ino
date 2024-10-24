#define STRING_HELPER(s) #s
#define STRING(s) STRING_HELPER(s)

#define PASSCODE_LENGTH 4
#define CORRECT_PASSCODE "1234" // Change this to your desired passcode

char passcode[PASSCODE_LENGTH + 1] = ""; // Buffer to store user input passcode
bool passcodeEntered = false; // Flag to indicate if passcode has been entered correctly
bool inSentryMode = false;

//////////////////////////////////////////////////
                //  LIBRARIES  //
//////////////////////////////////////////////////
#include <Arduino.h>
#include <Servo.h>
#include <IRremote.hpp>

#define DECODE_NEC  //defines the type of IR transmission to decode based on the remote. See IRremote library for examples on how to decode other types of remote

/*
** if you want to add other remotes (as long as they're on the same protocol above):
** press the desired button and look for a hex code similar to those below (ex: 0x11)
** then add a new line to #define newCmdName 0x11,
** and add a case to the switch statement like case newCmdName: 
** this will let you add new functions to buttons on other remotes!
** the best remotes to try are cheap LED remotes, some TV remotes, and some garage door openers
*/

//defines the specific command code for each button on the remote
#define left 0x8
#define right 0x5A
#define up 0x52
#define down 0x18
#define ok 0x1C
#define cmd1 0x45
#define cmd2 0x46
#define cmd3 0x47
#define cmd4 0x44
#define cmd5 0x40
#define cmd6 0x43
#define cmd7 0x7
#define cmd8 0x15
#define cmd9 0x9
#define cmd0 0x19
#define star 0x16
#define hashtag 0xD

#define echoPin 7
#define trigPin 8
#define irPin 9
#define yawPin 10
#define pitchPin 11
#define rollPin 12

//////////////////////////////////////////////////
          //  PINS AND PARAMETERS  //
//////////////////////////////////////////////////
Servo yawServo; //names the servo responsible for YAW rotation, 360 spin around the base
Servo pitchServo; //names the servo responsible for PITCH rotation, up and down tilt
Servo rollServo; //names the servo responsible for ROLL rotation, spins the barrel to fire darts


 //initialize variables to store the current value of each servo
int yawServoVal = 90;
int pitchServoVal = 100;
int rollServoVal = 90;

//initialize variables to store the last value of each servo
int lastYawServoVal = 90; 
int lastPitchServoVal = 90; 
int lastRollServoVal = 90;

int pitchMoveSpeed = 3; //this variable is the angle added to the pitch servo to control how quickly the PITCH servo moves - try values between 3 and 10
int yawMoveSpeed = 50; //this variable is the speed controller for the continuous movement of the YAW servo motor. It is added or subtracted from the yawStopSpeed, so 0 would mean full speed rotation in one direction, and 180 means full rotation in the other. Try values between 10 and 90;
int yawStopSpeed = 90; //value to stop the yaw motor - keep this at 90
int rollMoveSpeed = 90; //this variable is the speed controller for the continuous movement of the ROLL servo motor. It is added or subtracted from the rollStopSpeed, so 0 would mean full speed rotation in one direction, and 180 means full rotation in the other. Keep this at 90 for best performance / highest torque from the roll motor when firing.
int rollStopSpeed = 90; //value to stop the roll motor - keep this at 90

int yawPrecision = 150; // this variable represents the time in milliseconds that the YAW motor will remain at it's set movement speed. Try values between 50 and 500 to start (500 milliseconds = 1/2 second)
int rollPrecision = 158; // this variable represents the time in milliseconds that the ROLL motor with remain at it's set movement speed. If this ROLL motor is spinning more or less than 1/6th of a rotation when firing a single dart (one call of the fire(); command) you can try adjusting this value down or up slightly, but it should remain around the stock value (160ish) for best results.

int pitchMax = 175; // this sets the maximum angle of the pitch servo to prevent it from crashing, it should remain below 180, and be greater than the pitchMin
int pitchMin = 10; // this sets the minimum angle of the pitch servo to prevent it from crashing, it should remain above 0, and be less than the pitchMax

//////////////////////////////////////////////////
                //  S E T U P  //
//////////////////////////////////////////////////
void setup() {
    Serial.begin(9600); // initializes the Serial communication between the computer and the microcontroller

    yawServo.attach(yawPin);
    pitchServo.attach(pitchPin);
    rollServo.attach(rollPin);

    //Define inputs and outputs
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Just to know which program is running on my microcontroller
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(irPin, ENABLE_LED_FEEDBACK);

    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    Serial.println(F("at pin " STRING(irPin)));

    homeServos(); //set servo motors to home position
}

////////////////////////////////////////////////
                //  L O O P  //
////////////////////////////////////////////////

int loopCount = 0;
void loop() {
    loopCount++;

    if (IrReceiver.decode()) { //if we have recieved a comman this loop...
        int command = IrReceiver.decodedIRData.command; //store it in a variable
        IrReceiver.resume(); // Enable receiving of the next value
        handleCommand(command); // Handle the received command through switch statements
    }

    if (inSentryMode && loopCount % 50 == 0) {
      long inchesToTarget = getDistanceInInches();

      if (inchesToTarget < 30) {
          fire();
      }
    }



    delay(5); //delay for smoothness
}

float getDistanceInInches() {

    long durationInMicroseconds;
    float inches;

    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    delayMicroseconds(60);
    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    durationInMicroseconds = pulseIn(echoPin, HIGH);

    if (durationInMicroseconds == 0) {
        Serial.print("durationInMicroseconds == 0");
        return 1000;
    }
    
    // Convert the time into a distance
    //cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
    const float speedOfSoundIninchesPerMicrosecond = 0.0135;
    inches = (durationInMicroseconds * speedOfSoundIninchesPerMicrosecond) / 2.0;   // Divide by 74 or multiply by 0.0135
    
    Serial.print(inches);
    Serial.print("in ");
    //Serial.print(cm);
    //Serial.print("cm");
    Serial.println();

    return inches;
}

void addPasscodeDigit(char digit) {
    if (!passcodeEntered && digit >= '0' && digit <= '9' && strlen(passcode) < PASSCODE_LENGTH) {
        strncat(passcode, &digit, 1); //adds a digit to the passcode
        Serial.println(passcode); //print the passcode to Serial
    } else if (strlen(passcode) > PASSCODE_LENGTH+1){
      passcode[0] = '\0'; // Reset passcode buffer
      Serial.println(passcode);
    }
}

void nodHeadYes(int moves = 3) {
      Serial.println("YES");
    int startAngle = pitchServoVal; // Current position of the pitch servo
    int nodAngle = startAngle + 20; // Angle for nodding motion

    for (int i = 0; i < moves; i++) { // Repeat nodding motion three times
        // Nod up
        for (int angle = startAngle; angle <= nodAngle; angle++) {
            pitchServo.write(angle);
            delay(7); // Adjust delay for smoother motion
        }
        delay(50); // Pause at nodding position
        // Nod down
        for (int angle = nodAngle; angle >= startAngle; angle--) {
            pitchServo.write(angle);
            delay(7); // Adjust delay for smoother motion
        }
        delay(50); // Pause at starting position
    }
}

void shakeHeadNo(int moves = 3) {
    Serial.println("NO");

    for (int i = 0; i < moves; i++) { // Repeat nodding motion three times
        // rotate right, stop, then rotate left, stop
        yawServo.write(140);
        delay(190); // Adjust delay for smoother motion
        yawServo.write(yawStopSpeed);
        delay(50);
        yawServo.write(40);
        delay(190); // Adjust delay for smoother motion
        yawServo.write(yawStopSpeed);
        delay(50); // Pause at starting position
    }
}

void leftMove(int moves){
    for (int i = 0; i < moves; i++){
        yawServo.write(yawStopSpeed + yawMoveSpeed); // adding the servo speed = 180 (full counterclockwise rotation speed)
        delay(yawPrecision); // stay rotating for a certain number of milliseconds
        yawServo.write(yawStopSpeed); // stop rotating
        delay(5); //delay for smoothness
        Serial.println("LEFT");
  }

}

void rightMove(int moves){ // function to move right
  for (int i = 0; i < moves; i++){
      yawServo.write(yawStopSpeed - yawMoveSpeed); //subtracting the servo speed = 0 (full clockwise rotation speed)
      delay(yawPrecision);
      yawServo.write(yawStopSpeed);
      delay(5);
      Serial.println("RIGHT");
  }
}

void upMove(int moves){
  for (int i = 0; i < moves; i++){
      if(pitchServoVal > pitchMin){//make sure the servo is within rotation limits (greater than 10 degrees by default)
        pitchServoVal = pitchServoVal - pitchMoveSpeed; //decrement the current angle and update
        pitchServo.write(pitchServoVal);
        delay(50);
        Serial.println("UP");
      }
  }
}

void downMove (int moves){
  for (int i = 0; i < moves; i++){
        if(pitchServoVal < pitchMax){ //make sure the servo is within rotation limits (less than 175 degrees by default)
        pitchServoVal = pitchServoVal + pitchMoveSpeed;//increment the current angle and update
        pitchServo.write(pitchServoVal);
        delay(50);
        Serial.println("DOWN");
      }
  }
}

void fire() { //function for firing a single dart
    rollServo.write(rollStopSpeed + rollMoveSpeed);//start rotating the servo
    delay(rollPrecision);//time for approximately 60 degrees of rotation
    rollServo.write(rollStopSpeed);//stop rotating the servo
    delay(5); //delay for smoothness
    Serial.println("FIRING");
}

void fireAll() { //function to fire all 6 darts at once
    rollServo.write(rollStopSpeed + rollMoveSpeed);//start rotating the servo
    delay(rollPrecision * 6); //time for 360 degrees of rotation
    rollServo.write(rollStopSpeed);//stop rotating the servo
    delay(5); // delay for smoothness
    Serial.println("FIRING ALL");
}

void homeServos(){
    yawServo.write(yawStopSpeed); //setup YAW servo to be STOPPED (90)
    delay(20);
    rollServo.write(rollStopSpeed); //setup ROLL servo to be STOPPED (90)
    delay(100);
    pitchServo.write(100); //set PITCH servo to 100 degree position
    delay(100);
    pitchServoVal = 100; // store the pitch servo value
    Serial.println("HOMING");
}

void checkPasscode() {
    if (strcmp(passcode, CORRECT_PASSCODE) == 0) {
        // Correct passcode entered, shake head yes
        Serial.println("CORRECT PASSCODE");
        passcodeEntered = true;
        nodHeadYes();
    } else {
        // Incorrect passcode entered, shake head no
        passcodeEntered = false;
        shakeHeadNo();
        Serial.println("INCORRECT PASSCODE");
    }
    passcode[0] = '\0'; // Reset passcode buffer
}

void handleCommand(int command) {
    if((IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) && !passcodeEntered){ // this checks to see if the command is a repeat
        Serial.println("DEBOUNCING REPEATED NUMBER - IGNORING INPUT");
        return; //discarding the repeated numbers prevent you from accidentally inputting a number twice
    }

    switch (command) {
        case up:
            if (passcodeEntered) {
                // Handle up command
                upMove(1);
            } else {
                shakeHeadNo();
            }
            break;

        case down:
            if (passcodeEntered) {
                // Handle down command
                downMove(1);
            } else {
                shakeHeadNo();
            }
            break;

        case left:
            if (passcodeEntered) {
                // Handle left command
                leftMove(1);
            } else {
                shakeHeadNo();
            }
            break;

        case right:
            if (passcodeEntered) {
              // Handle right command
              rightMove(1);
            } else {
                shakeHeadNo();
            }
            break;

        case ok:
            if (passcodeEntered) {
                // Handle fire command
                fire();
                Serial.println("FIRE");
            } else {
                shakeHeadNo();
            }
            break;

        case hashtag:
            Serial.println("LOCKING");
            // Return to locked mode
            passcodeEntered = false;
            passcode[0] = '\0'; // Reset passcode buffer

            nodHeadYes(1);

            break;

        case star: //toggle sentry mode
            inSentryMode = !inSentryMode;
            if (inSentryMode) {
              shakeHeadNo();
            } else {
              nodHeadYes(1);
            }
            break;
            
        case cmd1: // Add digit 1 to passcode
            if (!passcodeEntered) {
                addPasscodeDigit('1');
            }
            break;

        case cmd2: // Add digit 2 to passcode
            if (!passcodeEntered) {
                addPasscodeDigit('2');
            }
            break;

        case cmd3: // Add digit 3 to passcode
            if (!passcodeEntered) {
                addPasscodeDigit('3');
            }
            break;

        case cmd4: // Add digit 4 to passcode
            if (!passcodeEntered) {
                addPasscodeDigit('4');
            }
            break;

        case cmd5: // Add digit 5 to passcode
            if (!passcodeEntered) {
                addPasscodeDigit('5');
            }
            break;

        case cmd6: // Add digit 6 to passcode
            if (!passcodeEntered) {
                addPasscodeDigit('6');
            }
            break;

        case cmd7: // Add digit 7 to passcode
            if (!passcodeEntered) {
                addPasscodeDigit('7');
            }
            break;

        case cmd8: // Add digit 8 to passcode
            if (!passcodeEntered) {
                addPasscodeDigit('8');
            }
            break;

        case cmd9: // Add digit 9 to passcode
            if (!passcodeEntered) {
                addPasscodeDigit('9');
            }
            break;

        case cmd0: // Add digit 0 to passcode
            if (!passcodeEntered) {
                addPasscodeDigit('0');
            }
            break;

        default:
            // Unknown command, do nothing
            Serial.print(command);
            Serial.println(" command unknown. Command Read Failed or Unknown, Try Again");
            break;
    }

    if (strlen(passcode) == PASSCODE_LENGTH){
        checkPasscode();
    }
}


  