#include "Defines.h"
#include "TurretState.h"

class ManualState : TurretState
{
    public:
        char * GetStateName() override;    
        void HandleCommand(int command) override;
        void DoLoopWork() override;
        void DrawStateContent(U8G2 u8g2, int x, int y, int width) override;
}