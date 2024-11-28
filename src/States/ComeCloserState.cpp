#include <string.h>

#include "Defines.h"
#include "DistanceUtilities.h"
#include "States\ComeCloserState.h"
#include "TurretActions.h"

////////////////////////////////////////////////
//  L O O P  //
////////////////////////////////////////////////
//const PROGMEM unsigned char image_crosshairs_bits[] = {0x00,0x00,0x00,0x00,0x20,0x00,0x20,0x00,0x70,0x00,0xa8,0x00,0x24,0x01,0xdf,0x07,0x24,0x01,0xa8,0x00,0x70,0x00,0x20,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char image_crosshairs_bits[] = {0x00,0x00,0x00,0x00,0x20,0x00,0x20,0x00,0x70,0x00,0xa8,0x00,0x24,0x01,0xdf,0x07,0x24,0x01,0xa8,0x00,0x70,0x00,0x20,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

const __FlashStringHelper * ComeCloserState::GetStateName()    
{
    return F("Come Closer\0");
}

TurretState* ComeCloserState::HandleCommand(int command)
{
    HandleIfMovementCommand(command);
    return nullptr;
}

void ComeCloserState::DoLoopWork(long loopCount)
{
    if (loopCount % 50 == 0)
    {
        m_distanceInInches = getDistanceInInches();
        if (m_distanceInInches < 30)
        {
            fire();
        }
    }
}

void ComeCloserState::DrawStateContent(U8G2* u8g2, int x, int y, int width)
{
    u8g2->drawXBM(x, y - 12, 16, 16, image_crosshairs_bits);
    char stateText[20];
    snprintf(stateText, 20, String(F("%ldin")).c_str(), m_distanceInInches);
    //Serial.print(m_distanceInInches);
    Serial.println(stateText);
    u8g2->drawStr(x + 13, y, stateText);
}