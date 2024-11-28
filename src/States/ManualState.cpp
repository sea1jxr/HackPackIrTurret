#include <string.h>

#include "Defines.h"
#include "TurretActions.h"
#include "States\ManualState.h"
    
const __FlashStringHelper * ManualState::GetStateName()    
{
    return F("Manual");
}

TurretState* ManualState::HandleCommand(int command)
{
    HandleIfMovementCommand(command);
    return nullptr;
}

void ManualState::DoLoopWork(long loopCount)
{
    // Nothing to do
}

void ManualState::DrawStateContent(U8G2* u8g2, int x, int y, int width)
{
    // Nothing to do
}