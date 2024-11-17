#include <Arduino.h>
#include <U8g2lib.h>

#include "EvvyMods.h"
#include "TurretActions.h"
#include "DistanceUtilities.h"
#include "IRremote.h"
#include "Screen.h"



long loopCount = 0;
void loop()
{
    if (turretState == nullptr)
    {
        Serial.println(F("turretState == nulptr"));
        return;
    }
    else if (loopCount % 50 == 0)
    {
        Serial.println(turretState->GetStateName());
    }

    if (loopCount % 10 == 0)
    {
        u8g2.clearBuffer();
        u8g2.setFontMode(1);
        u8g2.setBitmapMode(1);
        u8g2.setFont(u8g2_font_t0_11_tr);
        turretState->DrawStateContent(&u8g2, 50, 31, 128-31);
        u8g2.setFont(u8g2_font_t0_17_tr);
        u8g2.drawStr(3, 21, turretState->GetStateName());
        u8g2.setFont(u8g2_font_4x6_tr);
        u8g2.drawStr(5, 6, "1");
        u8g2.sendBuffer();
    }


    handleIrCommandIfAny();

    turretState->DoLoopWork(loopCount);

    loopCount++;

    delay(5); // delay for smoothness
}
