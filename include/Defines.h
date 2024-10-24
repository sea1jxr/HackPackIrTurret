#define STRING_HELPER(s) #s
#define STRING(s) STRING_HELPER(s)

#define PASSCODE_LENGTH 4
#define CORRECT_PASSCODE "1234" // Change this to your desired passcode

/*
** if you want to add other remotes (as long as they're on the same protocol above):
** press the desired button and look for a hex code similar to those below (ex: 0x11)
** then add a new line to #define newCmdName 0x11,
** and add a case to the switch statement like case newCmdName:
** this will let you add new functions to buttons on other remotes!
** the best remotes to try are cheap LED remotes, some TV remotes, and some garage door openers
*/

// defines the specific command code for each button on the remote
#define left 0x8
#define right 0x5A
#define up 0x52
#define down 0x18
#define ok 0x1C
#define cmd1 0x45
#define cmd2 0x46
#define cmd3 0x47
#define cmd4 0x44
#define cmd5 0x40
#define cmd6 0x43
#define cmd7 0x7
#define cmd8 0x15
#define cmd9 0x9
#define cmd0 0x19
#define star 0x16
#define hashtag 0xD

#define echoPin 7
#define trigPin 8
#define irPin 9
#define yawPin 10
#define pitchPin 11
#define rollPin 12
