#include "Defines.h"
#include "States\ComeCloserState.h"
#include "States\ManualState.h"
#include "States\SwitchModeState.h"
    
const char * SwitchModeState::GetStateName()    
{
    return "Switch";
}

TurretState* SwitchModeState::HandleCommand(int command)
{
    switch (command)
    {
        case cmd1:
            return new ManualState();
            break;

        case cmd2:
            return new ComeCloserState();
            break;
    }

    return nullptr;
}

void SwitchModeState::DoLoopWork(long loopCount)
{
    // Nothing to do
}

void SwitchModeState::DrawStateContent(U8G2* u8g2, int x, int y, int width)
{
    // Nothing to do
}