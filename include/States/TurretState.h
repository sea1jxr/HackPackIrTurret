#include <U8g2lib.h>

class TurretState
{
    public:
        virtual char * GetStateName() = 0;    
        virtual void HandleCommand(int command) = 0;
        virtual void DoLoopWork() = 0;
        virtual void DrawStateContent(U8G2 u8g2, int x, int y, int width) = 0;
}