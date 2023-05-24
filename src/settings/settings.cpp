#include "writeToFile/writeToFile.h"
#include "getError/getError.h"

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
        get_error[26] = 0;
        // Write mode
        file.print("mode:");
        file.println(test_choices.mode);

        // Write duration
        file.print("duration:");
        file.println(test_choices.duration);

        // Write pvm_freq
        file.print("pvm_freq:");
        file.println(test_choices.pvm_freq);

        // Write patient_id and experiment_id
        file.print("patient_id:");
        file.println(test_choices.patient_id);
        file.print("experiment_id:");
        file.println(test_choices.experiment_id);

        file.close();
    }
    else
    {
        get_error[26] = 1;
    }
}

/**
 * @brief Function which gets the settings from a file
 * @details The function gets the settings from a file on the SD card. Remember to initialize the SD card before calling this function.
 * @return test_choices: The struct containing the test choices
 */
TestChoices getSettingsFromFile()
{
    TestChoices test_choices;
    const char *filename = "settings.txt";
    File file = SD.open(filename, FILE_READ);
    if (file)
    {
        get_error[25] = 0;
        while (file.available())
        {
            String line = file.readStringUntil('\n');
            line.trim();
            if (line.startsWith("mode:"))
            {
                String value = line.substring(line.indexOf(":") + 1);
                test_choices.mode = intToMode(value.toInt());
            }
            else if (line.startsWith("duration:"))
            {
                String value = line.substring(line.indexOf(":") + 1);
                test_choices.duration = intToDuration(value.toInt());
            }
            else if (line.startsWith("pvm_freq:"))
            {
                String value = line.substring(line.indexOf(":") + 1);
                test_choices.pvm_freq = intToPvmFreq(value.toInt());
            }
            else if (line.startsWith("patient_id:"))
            {
                String value = line.substring(line.indexOf(":") + 1);
                test_choices.patient_id = value.toInt();
            }
            else if (line.startsWith("experiment_id:"))
            {
                String value = line.substring(line.indexOf(":") + 1);
                test_choices.experiment_id = value.toInt();
            }
        }
        file.close();
    }
    else
    {
        get_error[25] = 1;
    }
    
    return test_choices;
}
