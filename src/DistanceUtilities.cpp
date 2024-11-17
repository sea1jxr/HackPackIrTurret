#include <Arduino.h>

#include "Defines.h"

void initializeDistanceSensor()
{
    // Define inputs and outputs
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

// for some reason doing prints in this function causes memory issues.
// It might be just longer strings... not sure.
long getDistanceInInches()
{
    //return 34;

    long durationInMicroseconds;
    long inches;

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
    //durationInMicroseconds = 33 * 74 * 2;

    // Serial.print(durationInMicroseconds);
    // Serial.println("micro seconds ");
    // //return 31;
    
    if (durationInMicroseconds == 0)
    {
        //Serial.print("durationInMicroseconds == 0");
        return 1000;
    }
    
    // According to Parallax's datasheet for the PING))), there are
    // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
    // second).  This gives the distance travelled by the ping, outbound
    // and return, so we divide by 2 to get the distance of the obstacle.
    // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
    inches = durationInMicroseconds / 74 / 2;
    // Convert the time into a distance
    // const double speedOfSoundIninchesPerMicrosecond = 0.0135;
    // inches = (durationInMicroseconds * speedOfSoundIninchesPerMicrosecond) / 2.0; 

    // Serial.print("getDistanceInches ");
    // Serial.print(inches);
    // Serial.println("in ");

    return inches;
}