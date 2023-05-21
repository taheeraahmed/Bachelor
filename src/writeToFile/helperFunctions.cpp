#include "writeToFile/writeToFile.h"

/**
 * @brief Function which gets the experiment id
 * @details The function gets the experiment id from the SD card given the directories already existing
 * @return experiment_id: The experiment id to be used for the current experiment
 */
uint8_t getExperimentId(void)
{
    // Read experiment id from directory
    uint8_t experiment_id = 0;

    String directory_name = String(experiment_id);

    // Check if the folder already exists, and if so, increment the experiment ID and create a new folder name
    while (SD.exists(String(experiment_id)))
    {
        experiment_id++;
    }
    Serial.println("Experiment ID: " + String(experiment_id));
    return experiment_id;
};

/**
 * @brief Function which checks if a file exists
 * @details The function checks if a file exists on the SD card
 * @param filename: The name of the file to be checked
 * @return uint8_t: Returns 1 if the file exists, 0 if it doesn't
 */
uint8_t checkIfFileExists(char *filename)
{
    if (SD.exists(filename))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief Function which converts error data to char
 * @details The function converts the error data to char and returns it
 * @param error_code: The error code to be written to the file
 * @param error_message: The error message to be written to the file
 * @param timestamp: The timestamp to be written to the file
 * @return data: The data to be written to the file
 */
char *convertErrorToChar(uint8_t error_code, const char *error_message, const char *timestamp)
{
    char *data = new char[strlen(timestamp) + strlen(", ") + 1 + strlen("\n") + 1];
    strcpy(data, timestamp);
    strcat(data, ", ");
    strcat(data, String(error_code).c_str());
    strcat(data, ", ");
    strcat(data, String(error_message).c_str());
    return data;
}

/**
 * @brief Function which converts temperature data to char
 * @details The function converts the temperature data to char and returns it
 * @param temp_pcb: The temperature of the PCB
 * @param temp_air: The temperature of the air
 * @param temp_skin: The temperature of the skin
 * @param temp_led: The temperature of the LED
 * @param timestamp: The timestamp to be written to the file
 * @return data: The data to be written to the file
 */
char *convertDataToChar(uint8_t temp_pcb, uint8_t temp_air, uint8_t temp_skin, uint8_t temp_led, const char *timestamp)
{
    char *data = new char[strlen(timestamp) + strlen(", ") + 4 * 4 + strlen("\n") + 1];
    strcpy(data, timestamp);
    strcat(data, ", ");
    strcat(data, String(temp_pcb).c_str());
    strcat(data, ", ");
    strcat(data, String(temp_air).c_str());
    strcat(data, ", ");
    strcat(data, String(temp_skin).c_str());
    strcat(data, ", ");
    strcat(data, String(temp_led).c_str());
    return data;
}

const char *modeToString(Mode mode)
{
    switch (mode)
    {
    case PLACEBO:
        return "PLACEBO";
    case NOT_PLACEBO:
        return "NOT_PLACEBO";
    case DOUBLE_BLINDED:
        return "DOUBLE_BLINDED";
    default:
        return "UNKNOWN_MODE";
    }
}

const char *durationToString(Duration duration)
{
    switch (duration)
    {
    case DURATION_30_MIN:
        return "DURATION_30_MIN";
    case DURATION_45_MIN:
        return "DURATION_45_MIN";
    default:
        return "UNKNOWN_DURATION";
    }
}

const char *pvmFreqToString(PvmFreq pvmFreq)
{
    switch (pvmFreq)
    {
    case CONTINUOUS:
        return "CONTINUOUS";
    case LOW_FREQUENCY:
        return "LOW_FREQUENCY";
    case HIGH_FREQUENCY:
        return "HIGH_FREQUENCY";
    default:
        return "UNKNOWN_PVM_FREQ";
    }
}