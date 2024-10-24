#include <Arduino.h>

#include "Defines.h"
#include "TurretActions.h"


char passcode[PASSCODE_LENGTH + 1] = ""; // Buffer to store user input passcode
bool passcodeEntered = false;            // Flag to indicate if passcode has been entered correctly

void addPasscodeDigit(char digit)
{
    if (!passcodeEntered && digit >= '0' && digit <= '9' && strlen(passcode) < PASSCODE_LENGTH)
    {
        strncat(passcode, &digit, 1); // adds a digit to the passcode
        Serial.println(passcode);     // print the passcode to Serial
    }
    else if (strlen(passcode) > PASSCODE_LENGTH + 1)
    {
        passcode[0] = '\0'; // Reset passcode buffer
        Serial.println(passcode);
    }
}

void checkPasscode()
{
    if (strlen(passcode) != PASSCODE_LENGTH)
    {
        return;
    }

    if (strcmp(passcode, CORRECT_PASSCODE) == 0)
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
    passcode[0] = '\0'; // Reset passcode buffer
}

void clearPasscode()
{
    passcode[0] = '\0';
}