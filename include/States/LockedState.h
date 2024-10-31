#include "Defines.h"
#include "TurretState.h"

class LockedState : TurretState
{
    public:
        char * GetStateName() override;    
        void HandleCommand(int command) override;
        void DoLoopWork() override;
        void DrawStateContent(U8G2 u8g2, int x, int y, int width) override;

    private:
        void AddPasscodeDigit(char digit);
        void clearPasscode();
        void checkPasscode();

        // Buffer to store user input passcode
        char m_passcode[MAX_PASSCODE_LENGTH + 1] = "";
}