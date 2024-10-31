#include <Arduino.h>
#include <U8g2lib.h>

#include "EvvyMods.h"
#include "TurretActions.h"
#include "DistanceUtilities.h"
#include "IRremote.h"
#include "Screen.h"

////////////////////////////////////////////////
//  L O O P  //
////////////////////////////////////////////////
static const unsigned char image_crosshairs_bits[] = {0x00,0x00,0x00,0x00,0x20,0x00,0x20,0x00,0x70,0x00,0xa8,0x00,0x24,0x01,0xdf,0x07,0x24,0x01,0xa8,0x00,0x70,0x00,0x20,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


int loopCount = 0;
void loop()
{
    u8g2.clearBuffer();
    u8g2.setFontMode(1);
    u8g2.setBitmapMode(1);
    u8g2.setFont(u8g2_font_t0_11_tr);
    turretState.DrawStateContent(u8g2, 50, 31, 128-31);
    u8g2.setFont(u8g2_font_t0_17_tr);
    u8g2.drawStr(3, 21, "Come Closer");
    u8g2.setFont(u8g2_font_4x6_tr);
    u8g2.drawStr(5, 6, "1");
    u8g2.sendBuffer();

    loopCount++;
    handleIrCommandIfAny();

    TurretState.DoLoopWork();


    delay(5); // delay for smoothness
}
