#include "writeToFile/writeToFile.h"

/**
 * @brief Function which saves the settings to a file
 * @details The function saves the settings to a file on the SD card. Remember to initialize the SD card before calling this function.
 * @param test_choices: The struct containing the test choices
 * @return void
 */

void saveSettingsToFile(TestChoices test_choices)
{
    const char *filename = "settings.txt";

    if (checkIfFileExists(filename))
    {
        SD.remove(filename);
    }

    File file = SD.open(filename, FILE_WRITE);
    if (file)
    {
        // Write mode
        file.print("mode:");
        file.println(modeToString(test_choices.mode));

        // Write duration
        file.print("duration:");
        file.println(durationToString(test_choices.duration));

        // Write pvm_freq
        file.print("pvm_freq:");
        file.println(pvmFreqToString(test_choices.pvm_freq));

        // Write patient_id and experiment_id
        file.print("patient_id:");
        file.println(test_choices.patient_id);
        file.print("experiment_id:");
        file.println(test_choices.experiment_id);

        file.close();
        Serial.println("Settings saved to file.");
    }
    else
    {
        Serial.print("Error opening file: ");
        Serial.println(filename);
    }
}

/**
 * @brief Function which gets the settings from a file
 * @details The function gets the settings from a file on the SD card. Remember to initialize the SD card before calling this function.
 * @return test_choices: The struct containing the test choices
 */
TestChoices getSettingsFromFile()
{
    const char *filename = "settings.txt";
    TestChoices test_choices;

    File file = SD.open(filename, FILE_READ);
    if (file)
    {
        while (file.available())
        {
            String line = file.readStringUntil('\n');
            if (line.startsWith("mode:"))
            {
                String value = line.substring(5);
                test_choices.mode = stringToMode(value);
            }
            else if (line.startsWith("duration:"))
            {
                String value = line.substring(9);
                test_choices.duration = stringToDuration(value);
            }
            else if (line.startsWith("pvm_freq:"))
            {
                String value = line.substring(9);
                test_choices.pvm_freq = stringToPvmFreq(value);
            }
            else if (line.startsWith("patient_id:"))
            {
                String value = line.substring(11);
                test_choices.patient_id = value.toInt();
            }
            else if (line.startsWith("experiment_id:"))
            {
                String value = line.substring(14);
                test_choices.experiment_id = value.toInt();
            }
        }

        file.close();
        Serial.println("Settings loaded from file.");
    }
    else
    {
        Serial.print("Error opening file: ");
        Serial.println(filename);
    }

    return test_choices;
}