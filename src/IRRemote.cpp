#define DECODE_NEC // defines the type of IR transmission to decode based on the remote. See IRremote library for examples on how to decode other types of remote

#include <IRremote.hpp>

#include "Defines.h"
#include "EvvyMods.h"


void InitializeIrReciever() {
    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(irPin, ENABLE_LED_FEEDBACK);

    Serial.println(F("Using IRRemote library version " VERSION_IRREMOTE));
    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    Serial.println(F("at pin " STRING(irPin)));
}

void handleIrCommandIfAny() {
    if (IrReceiver.decode())
    {                                                   // if we have recieved a command this loop...
        int command = IrReceiver.decodedIRData.command; // store it in a variable
        IrReceiver.resume();                            // Enable receiving of the next value
        if (command == 0)
        {
            // we recieve the non command of 0 at random times with no button pushes
            // so eat them
            Serial.println(F("Zero command received, eating it..."));
            return;
        }

        handleCommand(command);                         // Handle the received command through switch statements
    }
}

bool isIrRemoteRepeat() {
    return IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT;
}