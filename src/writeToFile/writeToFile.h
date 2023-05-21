#include <SD.h>
#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <utils.h>
#include <SPI.h>

// Write to file
void initSD(int CS);
void createDirectory(uint8_t experiment_id);
char *createFileName(FileType type, TestChoices test_choices);
void createFile(char *headers, char *filename, TestChoices test_choices);
void writeInfoFile(TestChoices test, const char *start_timestamp, char *filename);
void writeToFile(char *filename, char *data);

// Helper functions
uint8_t getExperimentId(void);
uint8_t checkIfFileExists(char *filename);
const char *modeToString(Mode mode);
const char *durationToString(Duration duration);
const char *pvmFreqToString(PvmFreq pvmFreq);
char *convertDataToChar(uint8_t temp_pcb, uint8_t temp_air, uint8_t temp_skin, uint8_t temp_led, const char *timestamp);
char *convertErrorToChar(uint8_t error_code, const char *error_message, const char *timestamp);
