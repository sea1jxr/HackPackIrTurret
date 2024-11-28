#include "Defines.h"
#include "TurretState.h"

#pragma once

class ComeCloserState : public TurretState
{
        ~ComeCloserState() {};

    public:
        const __FlashStringHelper * GetStateName() override;    
        TurretState* HandleCommand(int command) override;
        void DoLoopWork(long loopCount) override;
        void DrawStateContent(U8G2* u8g2, int x, int y, int width) override;

    private:
        long m_distanceInInches = 100;
};