#include <string.h>

#include "Defines.h"
#include "IRremote.h"
#include "TurretActions.h"
#include "States\LockedState.h"
#include "States\ManualState.h"

const __FlashStringHelper * LockedState::GetStateName()    
{
    return F("Locked");
}

TurretState* LockedState::HandleCommand(int command)
{
    char digit = TryConvertCommandToDigit(command);
    bool isDigit = digit != '\0';

    if (isIrRemoteRepeat())
    { // this checks to see if the command is a repeat
        Serial.println(F("DEBOUNCING REPEATED NUMBER - IGNORING INPUT"));
        // discarding the repeated numbers prevent you from accidentally inputting a number twice
        return nullptr; 
    }

    if (isDigit && this->AddPasscodeDigit(digit))
    {
        if (checkPasscode())
        {
            nodHeadYes();

            return new ManualState();
        }

        return nullptr;
    }

    Serial.print(command);
    Serial.println(F(" command unknown. Command Read Failed or Unknown, Try Again"));
    shakeHeadNo();

    return nullptr;
}   

char LockedState::TryConvertCommandToDigit(int command)
{
    switch (command)
    {
    case cmd1:
        return '1';

    case cmd2:
        return '2';

    case cmd3:
        return '3';

    case cmd4:
        return '4';

    case cmd5:
        return '5';

    case cmd6:
        return '6';

    case cmd7:
        return '7';

    case cmd8:
        return '8';

    case cmd9:
        return '9';

    case cmd0:
        return '0';
    }

    return '\0';
}


void LockedState::DoLoopWork(long loopCount)
{
    // Nothing to do
}

void LockedState::DrawStateContent(U8G2* u8g2, int x, int y, int width)
{
    int count = strlen(m_passcode);
    char passwordDisplay[count + 1];
    for (int i = 0; i < count; i++)
    {
        passwordDisplay[i] = '*';
    }
    passwordDisplay[count] = '\0';

    u8g2->drawStr(x, y, passwordDisplay);
}

bool LockedState::AddPasscodeDigit(char digit)
{
    if (digit >= '0' && digit <= '9' && strlen(m_passcode) < MAX_PASSCODE_LENGTH)
    {
        strncat(m_passcode, &digit, 1); // adds a digit to the passcode
        Serial.println(m_passcode);     // print the passcode to Serial
        return true;
    }

    return false;
}

bool LockedState::checkPasscode()
{
    if (strlen(m_passcode) != strlen(String(CORRECT_PASSCODE).c_str()))
    {
        Serial.print(F("Current Passcode is '"));
        Serial.print(m_passcode);
        Serial.println(F("'"));
        return false;
    }

    if (strcmp(m_passcode, String(CORRECT_PASSCODE).c_str()) == 0)
    {
        // Correct passcode entered, shake head yes
        Serial.println(F("CORRECT PASSCODE"));
        return true;
    }

    Serial.println(F("INCORRECT PASSCODE"));
    return false;
}