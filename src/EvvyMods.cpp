//////////////////////////////////////////////////
//  LIBRARIES  //
//////////////////////////////////////////////////
#include <Arduino.h>

#include "Defines.h"
#include "EvvyMods.h"
#include "IRRemote.h"
#include "TurretActions.h"

bool previousInputWasHashTag = false;
bool switchModes = false;

void handleCommand(int command)
{
    turretState.HandleCommand(command);

    switch (command)
    {
        case star:
            turretState = LockedState();
            break;

        case hashtag:
            if (previousInputWasHashTag)
            {
               switchModes = true; 
            }
            break;
        
        case cmd1:
            if (switchModes)
            {
                turretState = ManualState();
            }
            break;

        case cmd2:
            if (switchModes)
            {
                turretState = ComeCloser();
            }
            break;
    }

    trr
}

