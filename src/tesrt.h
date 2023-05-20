#include <avr/io.h>
#include <stdbool.h>

extern char PasientID[2];
extern uint8_t TestTime;
extern uint8_t NirSettings;
extern uint8_t TestMode;


void RunMenu(void);
void waitForPassword(void);
void setPatientID(void);
void setTime();
void showLed(uint8_t ledHead);
void chooseNIRsettings(void);
void chooseTestsettings(void);
void showSettings(void);
void SaveOrExit(void);