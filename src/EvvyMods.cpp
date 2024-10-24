//////////////////////////////////////////////////
//  LIBRARIES  //
//////////////////////////////////////////////////
#include <Arduino.h>

#include "Defines.h"
#include "EvvyMods.h"
#include "IRRemote.h"
#include "TurretActions.h"
#include "Passcode.h"

void handleCommand(int command)
{
    if (isIrRemoteRepeat() && !passcodeEntered)
    { // this checks to see if the command is a repeat
        Serial.println("DEBOUNCING REPEATED NUMBER - IGNORING INPUT");
        return; // discarding the repeated numbers prevent you from accidentally inputting a number twice
    }

    switch (command)
    {
    case up:
        if (passcodeEntered)
        {
            // Handle up command
            upMove(1);
        }
        else
        {
            shakeHeadNo();
        }
        break;

    case down:
        if (passcodeEntered)
        {
            // Handle down command
            downMove(1);
        }
        else
        {
            shakeHeadNo();
        }
        break;

    case left:
        if (passcodeEntered)
        {
            // Handle left command
            leftMove(1);
        }
        else
        {
            shakeHeadNo();
        }
        break;

    case right:
        if (passcodeEntered)
        {
            // Handle right command
            rightMove(1);
        }
        else
        {
            shakeHeadNo();
        }
        break;

    case ok:
        if (passcodeEntered)
        {
            // Handle fire command
            fire();
            Serial.println("FIRE");
        }
        else
        {
            shakeHeadNo();
        }
        break;

    case hashtag:
        Serial.println("LOCKING");
        // Return to locked mode
        passcodeEntered = false;
        clearPasscode();

        nodHeadYes(1);

        break;

    case star: // toggle sentry mode
        inSentryMode = !inSentryMode;
        if (inSentryMode)
        {
            shakeHeadNo();
        }
        else
        {
            nodHeadYes(1);
        }
        break;

    case cmd1: // Add digit 1 to passcode
        if (!passcodeEntered)
        {
            addPasscodeDigit('1');
        }
        break;

    case cmd2: // Add digit 2 to passcode
        if (!passcodeEntered)
        {
            addPasscodeDigit('2');
        }
        break;

    case cmd3: // Add digit 3 to passcode
        if (!passcodeEntered)
        {
            addPasscodeDigit('3');
        }
        break;

    case cmd4: // Add digit 4 to passcode
        if (!passcodeEntered)
        {
            addPasscodeDigit('4');
        }
        break;

    case cmd5: // Add digit 5 to passcode
        if (!passcodeEntered)
        {
            addPasscodeDigit('5');
        }
        break;

    case cmd6: // Add digit 6 to passcode
        if (!passcodeEntered)
        {
            addPasscodeDigit('6');
        }
        break;

    case cmd7: // Add digit 7 to passcode
        if (!passcodeEntered)
        {
            addPasscodeDigit('7');
        }
        break;

    case cmd8: // Add digit 8 to passcode
        if (!passcodeEntered)
        {
            addPasscodeDigit('8');
        }
        break;

    case cmd9: // Add digit 9 to passcode
        if (!passcodeEntered)
        {
            addPasscodeDigit('9');
        }
        break;

    case cmd0: // Add digit 0 to passcode
        if (!passcodeEntered)
        {
            addPasscodeDigit('0');
        }
        break;

    default:
        // Unknown command, do nothing
        Serial.print(command);
        Serial.println(" command unknown. Command Read Failed or Unknown, Try Again");
        break;
    }

}


