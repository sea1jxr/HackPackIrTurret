#include <Arduino.h>
#include <U8g2lib.h>

#include "EvvyMods.h"
#include "TurretActions.h"
#include "DistanceUtilities.h"
#include "IRremote.h"
#include "Screen.h"

int freeRam() {
  extern int __heap_start,*__brkval;
  int v;
  return (int)&v - (__brkval == 0  
    ? (int)&__heap_start : (int) __brkval);  
}

void display_freeram() {
  Serial.print(F("- SRAM left: "));
  Serial.println(freeRam());
}

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
        display_freeram();
    }

    if (loopCount % 10 == 0)
    {

        u8g2.clearBuffer();
        u8g2.setFontMode(1);
        u8g2.setBitmapMode(1);
        u8g2.setFont(u8g2_font_t0_17_tr);
        u8g2.drawStr(3, 12, String(turretState->GetStateName()).c_str());
        u8g2.setFont(u8g2_font_t0_11_tr);
        turretState->DrawStateContent(&u8g2, 13, 31, 128-31);
        u8g2.sendBuffer();
    }


    handleIrCommandIfAny();

    turretState->DoLoopWork(loopCount);

    loopCount++;

    delay(5); // delay for smoothness
}
