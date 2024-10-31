#include <string.h>

#include "Defines.h"
#include "States\LockedState.h"

char * LockedState::GetStateName()    
{
    return "Locked";
}

void LockedState::HandleCommand(int command)
{
    if (isIrRemoteRepeat())
    { // this checks to see if the command is a repeat
        Serial.println("DEBOUNCING REPEATED NUMBER - IGNORING INPUT");
        return; // discarding the repeated numbers prevent you from accidentally inputting a number twice
    }

    // switch (command)
    // {
    // case up:
    //     if (passcodeEntered)
    //     {
    //         // Handle up command
    //         upMove(1);
    //     }
    //     else
    //     {
    //         shakeHeadNo();
    //     }
    //     break;

    // case down:
    //     if (passcodeEntered)
    //     {
    //         // Handle down command
    //         downMove(1);
    //     }
    //     else
    //     {
    //         shakeHeadNo();
    //     }
    //     break;

    // case left:
    //     if (passcodeEntered)
    //     {
    //         // Handle left command
    //         leftMove(1);
    //     }
    //     else
    //     {
    //         shakeHeadNo();
    //     }
    //     break;

    // case right:
    //     if (passcodeEntered)
    //     {
    //         // Handle right command
    //         rightMove(1);
    //     }
    //     else
    //     {
    //         shakeHeadNo();
    //     }
    //     break;

    // case ok:
    //     if (passcodeEntered)
    //     {
    //         // Handle fire command
    //         fire();
    //         Serial.println("FIRE");
    //     }
    //     else
    //     {
    //         shakeHeadNo();
    //     }
    //     break;

    // case hashtag:
    //     Serial.println("LOCKING");
    //     // Return to locked mode
    //     passcodeEntered = false;
    //     clearPasscode();

    //     nodHeadYes(1);

    //     break;

    // case star: // toggle sentry mode
    //     inSentryMode = !inSentryMode;
    //     if (inSentryMode)
    //     {
    //         shakeHeadNo();
    //     }
    //     else
    //     {
    //         nodHeadYes(1);
    //     }
    //     break;

    // case cmd1: // Add digit 1 to passcode
    //     if (!passcodeEntered)
    //     {
    //         addPasscodeDigit('1');
    //     }
    //     break;

    // case cmd2: // Add digit 2 to passcode
    //     if (!passcodeEntered)
    //     {
    //         addPasscodeDigit('2');
    //     }
    //     break;

    // case cmd3: // Add digit 3 to passcode
    //     if (!passcodeEntered)
    //     {
    //         addPasscodeDigit('3');
    //     }
    //     break;

    // case cmd4: // Add digit 4 to passcode
    //     if (!passcodeEntered)
    //     {
    //         addPasscodeDigit('4');
    //     }
    //     break;

    // case cmd5: // Add digit 5 to passcode
    //     if (!passcodeEntered)
    //     {
    //         addPasscodeDigit('5');
    //     }
    //     break;

    // case cmd6: // Add digit 6 to passcode
    //     if (!passcodeEntered)
    //     {
    //         addPasscodeDigit('6');
    //     }
    //     break;

    // case cmd7: // Add digit 7 to passcode
    //     if (!passcodeEntered)
    //     {
    //         addPasscodeDigit('7');
    //     }
    //     break;

    // case cmd8: // Add digit 8 to passcode
    //     if (!passcodeEntered)
    //     {
    //         addPasscodeDigit('8');
    //     }
    //     break;

    // case cmd9: // Add digit 9 to passcode
    //     if (!passcodeEntered)
    //     {
    //         addPasscodeDigit('9');
    //     }
    //     break;

    // case cmd0: // Add digit 0 to passcode
    //     if (!passcodeEntered)
    //     {
    //         addPasscodeDigit('0');
    //     }
    //     break;

    // default:
    //     // Unknown command, do nothing
    //     Serial.print(command);
    //     Serial.println(" command unknown. Command Read Failed or Unknown, Try Again");
    //     break;
    // }

    // if (!passcodeEntered) 
    // {
    //     checkPasscode();
    // }
}

void LockedState::DoLoopWork()
{
    // Nothing to do
}

void LockedState::DrawStateContent(U8G2 u8g2, int x, int y, int width)
{
    int count = strlen(m_passcode);
    char passwordDisplay[MAX_PASSCODE_LENGTH + 1];
    for (int i = 0; i < count; i++)
    {
        passwordDisplay[i] = '*';
    }

    u8g2.drawStr(67, 31, "35.05 in");
}

void ManualState::AddPasscodeDigit(char digit)
{
    if (!passcodeEntered && digit >= '0' && digit <= '9' && strlen(m_passcode) < MAX_PASSCODE_LENGTH)
    {
        strncat(m_passcode, &digit, 1); // adds a digit to the passcode
        Serial.println(m_passcode);     // print the passcode to Serial
    }
    else if (strlen(m_passcode) > MAX_PASSCODE_LENGTH + 1)
    {
        clearPasscode();
        Serial.println(m_passcode);
    }
}

void ManualState::checkPasscode()
{
    if (strlen(m_passcode) != strlen(CORRECT_PASSCODE))
    {
        Serial.print("Current Passcode is '");
        Serial.print(m_passcode);
        Serial.println("'");
        return;
    }

    if (strcmp(m_passcode, CORRECT_PASSCODE) == 0)
    {
        // Correct passcode entered, shake head yes
        Serial.println("CORRECT PASSCODE");
        passcodeEntered = true;
        nodHeadYes();
    }
    else
    {
        // Incorrect passcode entered, shake head no
        passcodeEntered = false;
        shakeHeadNo();
        Serial.println("INCORRECT PASSCODE");
    }

    clearPasscode();
}

void ManualState::clearPasscode()
{
    m_passcode[0] = '\0';
}