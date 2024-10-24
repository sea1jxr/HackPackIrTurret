#include <Arduino.h>

#include "Defines.h"

float getDistanceInInches()
{
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

    if (durationInMicroseconds == 0)
    {
        Serial.print("durationInMicroseconds == 0");
        return 1000;
    }

    // Convert the time into a distance
    const float speedOfSoundIninchesPerMicrosecond = 0.0135;
    inches = (durationInMicroseconds * speedOfSoundIninchesPerMicrosecond) / 2.0; 

    Serial.print(inches);
    Serial.print("in ");
    Serial.println();

    return inches;
}