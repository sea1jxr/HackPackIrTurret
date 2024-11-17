#include <Arduino.h>
#include <Servo.h>

#include "EvvyMods.h"
#include "Defines.h"

Servo yawServo;
Servo pitchServo;
Servo rollServo;

// initialize variables to store the current value of each servo
int yawServoVal = 90;
int pitchServoVal = 100;
int rollServoVal = 90;

// initialize variables to store the last value of each servo
int lastYawServoVal = 90;
int lastPitchServoVal = 90;
int lastRollServoVal = 90;

int pitchMoveSpeed = 3; // this variable is the angle added to the pitch servo to control how quickly the PITCH servo moves - try values between 3 and 10
int yawMoveSpeed = 50;  // this variable is the speed controller for the continuous movement of the YAW servo motor. It is added or subtracted from the yawStopSpeed, so 0 would mean full speed rotation in one direction, and 180 means full rotation in the other. Try values between 10 and 90;
int yawStopSpeed = 90;  // value to stop the yaw motor - keep this at 90
int rollMoveSpeed = 90; // this variable is the speed controller for the continuous movement of the ROLL servo motor. It is added or subtracted from the rollStopSpeed, so 0 would mean full speed rotation in one direction, and 180 means full rotation in the other. Keep this at 90 for best performance / highest torque from the roll motor when firing.
int rollStopSpeed = 90; // value to stop the roll motor - keep this at 90

int yawPrecision = 150;  // this variable represents the time in milliseconds that the YAW motor will remain at it's set movement speed. Try values between 50 and 500 to start (500 milliseconds = 1/2 second)
int rollPrecision = 158; // this variable represents the time in milliseconds that the ROLL motor with remain at it's set movement speed. If this ROLL motor is spinning more or less than 1/6th of a rotation when firing a single dart (one call of the fire(); command) you can try adjusting this value down or up slightly, but it should remain around the stock value (160ish) for best results.

int pitchMax = 175; // this sets the maximum angle of the pitch servo to prevent it from crashing, it should remain below 180, and be greater than the pitchMin
int pitchMin = 10;  // this sets the minimum angle of the pitch servo to prevent it from crashing, it should remain above 0, and be less than the pitchMax

void initializeServos()
{
    yawServo.attach(yawPin);
    pitchServo.attach(pitchPin);
    rollServo.attach(rollPin);
}

void homeServos()
{
    yawServo.write(yawStopSpeed); // setup YAW servo to be STOPPED (90)
    delay(20);
    rollServo.write(rollStopSpeed); // setup ROLL servo to be STOPPED (90)
    delay(100);
    pitchServo.write(100); // set PITCH servo to 100 degree position
    delay(100);
    pitchServoVal = 100; // store the pitch servo value
    Serial.println("HOMING");
}

void nodHeadYes(int moves = 3)
{
    Serial.println("YES");
    int startAngle = pitchServoVal; // Current position of the pitch servo
    int nodAngle = startAngle + 20; // Angle for nodding motion

    for (int i = 0; i < moves; i++)
    { // Repeat nodding motion three times
        // Nod up
        for (int angle = startAngle; angle <= nodAngle; angle++)
        {
            pitchServo.write(angle);
            delay(7); // Adjust delay for smoother motion
        }
        delay(50); // Pause at nodding position
        // Nod down
        for (int angle = nodAngle; angle >= startAngle; angle--)
        {
            pitchServo.write(angle);
            delay(7); // Adjust delay for smoother motion
        }
        delay(50); // Pause at starting position
    }
}

void shakeHeadNo(int moves = 3)
{
    Serial.println("NO");

    for (int i = 0; i < moves; i++)
    { // Repeat nodding motion three times
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

void leftMove(int moves)
{
    for (int i = 0; i < moves; i++)
    {
        yawServo.write(yawStopSpeed + yawMoveSpeed); // adding the servo speed = 180 (full counterclockwise rotation speed)
        delay(yawPrecision);                         // stay rotating for a certain number of milliseconds
        yawServo.write(yawStopSpeed);                // stop rotating
        delay(5);                                    // delay for smoothness
        Serial.println("LEFT");
    }
}

void rightMove(int moves)
{ // function to move right
    for (int i = 0; i < moves; i++)
    {
        yawServo.write(yawStopSpeed - yawMoveSpeed); // subtracting the servo speed = 0 (full clockwise rotation speed)
        delay(yawPrecision);
        yawServo.write(yawStopSpeed);
        delay(5);
        Serial.println("RIGHT");
    }
}

void upMove(int moves)
{
    for (int i = 0; i < moves; i++)
    {
        if (pitchServoVal > pitchMin)
        {                                                   // make sure the servo is within rotation limits (greater than 10 degrees by default)
            pitchServoVal = pitchServoVal - pitchMoveSpeed; // decrement the current angle and update
            pitchServo.write(pitchServoVal);
            delay(50);
            Serial.println("UP");
        }
    }
}

void downMove(int moves)
{
    for (int i = 0; i < moves; i++)
    {
        if (pitchServoVal < pitchMax)
        {                                                   // make sure the servo is within rotation limits (less than 175 degrees by default)
            pitchServoVal = pitchServoVal + pitchMoveSpeed; // increment the current angle and update
            pitchServo.write(pitchServoVal);
            delay(50);
            Serial.println("DOWN");
        }
    }
}

void fire()
{                                                   // function for firing a single dart
    rollServo.write(rollStopSpeed + rollMoveSpeed); // start rotating the servo
    delay(rollPrecision);                           // time for approximately 60 degrees of rotation
    rollServo.write(rollStopSpeed);                 // stop rotating the servo
    delay(5);                                       // delay for smoothness
    Serial.println("FIRING");
}

void fireAll()
{                                                   // function to fire all 6 darts at once
    rollServo.write(rollStopSpeed + rollMoveSpeed); // start rotating the servo
    delay(rollPrecision * 6);                       // time for 360 degrees of rotation
    rollServo.write(rollStopSpeed);                 // stop rotating the servo
    delay(5);                                       // delay for smoothness
    Serial.println("FIRING ALL");
}

bool HandleIfMovementCommand(int command)
{
    switch (command)
    {
    case up:
        // Handle up command
        upMove(1);
        break;

    case down:
        // Handle down command
        downMove(1);
        break;

    case left:
        // Handle left command
        leftMove(1);
        break;

    case right:
        // Handle right command
        rightMove(1);
        break;

    case ok:
        // Handle fire command
        fire();
        Serial.println("FIRE");
        break;

    default:
        return false;
    }

    return true;
}
