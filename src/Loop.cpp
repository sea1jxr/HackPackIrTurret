#include <Arduino.h>

#include "EvvyMods.h"
#include "TurretActions.h"
#include "DistanceUtilities.h"
////////////////////////////////////////////////
//  L O O P  //
////////////////////////////////////////////////

int loopCount = 0;
void loop()
{
    loopCount++;
    handleIrCommandIfAny();

    if (inSentryMode && loopCount % 50 == 0)
    {
        long inchesToTarget = getDistanceInInches();

        if (inchesToTarget < 30)
        {
            fire();
        }
    }

    delay(5); // delay for smoothness
}
