#include <Arduino.h>

#include "TurretActions.h"
#include "IRremote.h"
#include "DistanceUtilities.h"
#include "Screen.h"

//////////////////////////////////////////////////
//  S E T U P  //
//////////////////////////////////////////////////
void setup()
{
    Serial.begin(9600); // initializes the Serial communication between the computer and the microcontroller

    u8g2.begin();
    
    initializeServos();

    initializeDistanceSensor();

    // Just to know which program is running on my microcontroller
    Serial.println(String(F("START ")) + __FILE__  + String(F(" from ")) + __DATE__ + String(F(" @ ")) + __TIME__);

    InitializeIrReciever();

    // set servo motors to home position
    homeServos();
}
