#include <SD.h>
#include <Arduino.h>
#include <utils/utils.h>
#include <SPI.h>

// Used for getting and saving settings
void saveSettingsToFile(TestChoices test_choices, char *filename);
TestChoices getSettingsFromFile(char *filename);