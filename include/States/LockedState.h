#include "Defines.h"
#include "TurretState.h"

#pragma once

class LockedState : public TurretState
{
        ~LockedState() override {};

    public:
        const char * GetStateName() override;    
        TurretState* HandleCommand(int command) override;
        void DoLoopWork(long loopCount) override;
        void DrawStateContent(U8G2* u8g2, int x, int y, int width) override;

    private:
        bool AddPasscodeDigit(char digit);
        bool checkPasscode();
        char TryConvertCommandToDigit(int command);
        // Buffer to store user input passcode
        char m_passcode[MAX_PASSCODE_LENGTH + 1] = "";
};