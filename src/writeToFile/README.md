# Writing to SD card

## Description

This part of the code consists of functions that are used to write data to the SD card. 

It logs the data in two files, one for the temperature data and one for the error data. The temperature data is logged every 30 seconds and the error data is logged when an error occurs.

## Functions

### createFileName

`char *createFileName` creates the file name for the file that is going to be created. It takes in three parameters, the first one is a boolean that is used to determine if the file is for the temperature data or the error data. The second parameter is the patient id and the third parameter is the start time of the measurement.

### initSD

`void initSD` initializes the SD card.

### createFile

`void createFile` creates the file that is going to be used to log the data. It takes in five parameters, the first one is the headers that are going to be written to the file. The second parameter is the file name that is going to be used. The third parameter is a boolean that is used to determine if the file is for the temperature data or the error data. The fourth parameter is the patient id and the fifth parameter is the start time of the measurement.

### convertDataToChar

`char *convertDataToChar` converts the data to a char array. It takes in five parameters, the first one is the temperature of the PCB, the second parameter is the temperature of the air, the third parameter is the temperature of the skin, the fourth parameter is the temperature of the LED and the fifth parameter is the date and time.

### convertErrorToChar

`char *convertErrorToChar` converts the error data to a char array. It takes in three parameters, the first one is the error code, the second parameter is the error message and the third parameter is the date and time.

## Usage

This is only example usage of the functions. The functions can be used in the main code like the example below.

```cpp
#include "writeToFile/writeToFile.h"
#include <stdio.h>
#include <Arduino.h>


char temp_headers[50] = "datetime,temp_pcb,temp_air,temp_skin,temp_led";
char error_headers[50] = "datetime,error_code,error_msg";

char *file_temp;
char *file_error;
char *file_info;

const char *mode = "Placebo";
const char *pvm_freq = "10";
const char *start_timestamp = "2021-05-12T12:12:12";
const char *duration = "45 min";

const char *timestamp = "2021-05-12T12:12:12";

void setup()
{
  Serial.begin(9600);
  Serial.println("Setup started");
  initSD();
  int experiment_id = getExperimentId();
  int patient_id = 123;

  createDirectory(experiment_id);
  file_temp = createFileName("temp", patient_id, experiment_id);
  file_error = createFileName("error", patient_id, experiment_id);
  file_info = createFileName("info", patient_id, experiment_id);

  createFile(temp_headers, file_temp, patient_id, experiment_id);
  createFile(error_headers, file_error, patient_id, experiment_id);
  createFile("Information about experiment", file_info, patient_id, experiment_id);
  writeInfoFile(mode, pvm_freq, start_timestamp, duration, file_info, experiment_id, patient_id);
  Serial.println("Setup complete");
  while(1){
    Serial.println("Looping");
    delay(10);
    char *data = convertDataToChar(1, 2, 3, 4, timestamp);
    writeToFile(file_temp, data);
    char *error = convertErrorToChar(1, "Error message", timestamp);
    writeToFile(file_error, error);
    delay(1000); // Add a delay of 1 second (1000 milliseconds) between iterations
  }
}
```