//////////////////////////////////////////////////
//  LIBRARIES  //
//////////////////////////////////////////////////
#include <Arduino.h>

#include "Defines.h"
#include "EvvyMods.h"
#include "States/ComeCloserState.h"
#include "States/LockedState.h"
#include "States/ManualState.h"
#include "States/SwitchModeState.h"

TurretState* turretState = new LockedState();

void handleCommand(int command)
{
    Serial.print(command);

    TurretState* newState = nullptr;

    // Handle System wide commands
    switch (command)
    {
        case star:
            newState = new LockedState();
        break;

        case hashtag:
            newState = new SwitchModeState();
        break;

        default:
            newState = nullptr;
            break;
    }

    if (newState == nullptr)
    {
        newState = turretState->HandleCommand(command);
    }

    if (newState != nullptr)
    {
        delete turretState;
        turretState = newState;
    }
}

