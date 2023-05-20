#include <SD.h>
#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <utils.h>

char *createFileName(FileType type, TestChoices test_choices);
void createFile(char *headers, char *filename, TestChoices test_choices);
void createDirectory(uint8_t experiment_id);
void writeInfoFile(TestChoices test, const char *start_timestamp, char *filename);
void writeToFile(char *filename, char *data);
void initSD(int CS);
uint8_t getExperimentId(void);
char *convertDataToChar(uint8_t temp_pcb, uint8_t temp_air, uint8_t temp_skin, uint8_t temp_led, const char *timestamp);
char *convertErrorToChar(uint8_t error_code, const char *error_message, const char *timestamp);
uint8_t checkIfFileExists(char *filename);