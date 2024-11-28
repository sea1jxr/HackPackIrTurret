#include <U8g2lib.h>

#pragma once

class TurretState
{
    public:
        virtual ~TurretState() = 0;
        virtual const __FlashStringHelper * GetStateName() = 0;    
        virtual TurretState* HandleCommand(int command) = 0;
        virtual void DoLoopWork(long loopCount) = 0;
        virtual void DrawStateContent(U8G2* u8g2, int x, int y, int width) = 0;
        virtual bool IsLocked() { return false; }
};
