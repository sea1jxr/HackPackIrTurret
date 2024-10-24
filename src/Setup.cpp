#include <Arduino.h>

#include "Defines.h"
#include "EvvyMods.h"
#include "TurretActions.h"

//////////////////////////////////////////////////
//  S E T U P  //
//////////////////////////////////////////////////
void setup()
{
    Serial.begin(9600); // initializes the Serial communication between the computer and the microcontroller

    initializeServos();

    // Define inputs and outputs
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Just to know which program is running on my microcontroller
    Serial.println(F("START " __FILE__ " from " __DATE__ ));

    InitializeIrReciever();

    homeServos(); // set servo motors to home position
}
