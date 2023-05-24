#include <SD.h>
#include <Arduino.h>
#include <utils/utils.h>
#include <SPI.h>

// General 
void initSD(int CS);
void initCard(int CS, Sd2Card card);

// Used for logging
void createDirectory(uint8_t experiment_id);
char *createFileName(FileType type, TestChoices test_choices);
void createFile(char *headers, char *filename, TestChoices test_choices);
void writeInfoFile(TestChoices test, const char *start_timestamp, char *filename);
void writeToFile(char *filename, char *data);



// Helper functions
uint8_t getExperimentId(void);
uint8_t checkIfFileExists(const char *filename);
char *convertDataToChar(float temp_pcb, float temp_air, float temp_skin, float temp_led, const char *timestamp);
char *convertErrorToChar(uint8_t error_code, const char *error_message, const char *timestamp);
