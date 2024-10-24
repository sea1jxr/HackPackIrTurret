#include <Arduino.h>

#include "TurretActions.h"
#include "IRremote.h"
#include "DistanceUtilities.h"

//////////////////////////////////////////////////
//  S E T U P  //
//////////////////////////////////////////////////
void setup()
{
    Serial.begin(9600); // initializes the Serial communication between the computer and the microcontroller

    initializeServos();

    initializeDistanceSensor();

    // Just to know which program is running on my microcontroller
    Serial.println(F("START " __FILE__ " from " __DATE__ " @ " __TIME__));

    InitializeIrReciever();

    homeServos(); // set servo motors to home position
}
