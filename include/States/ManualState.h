#include "Defines.h"
#include "TurretState.h"

#pragma once

class ManualState : public TurretState
{
        ~ManualState() override {};

    public:
        const __FlashStringHelper * GetStateName() override;    
        TurretState* HandleCommand(int command) override;
        void DoLoopWork(long loopCount) override;
        void DrawStateContent(U8G2* u8g2, int x, int y, int width) override;
};