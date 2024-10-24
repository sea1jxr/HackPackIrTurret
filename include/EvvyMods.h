#include <Servo.h>

extern bool inSentryMode;
extern Servo yawServo;
extern Servo pitchServo;
extern Servo rollServo;

void fire();
float getDistanceInInches();
void handleCommand(int command);
void handleIrCommandIfAny();
void homeServos();
void InitializeIrReciever();

