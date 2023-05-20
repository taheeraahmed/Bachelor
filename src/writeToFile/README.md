# Writing to SD card

## Description

This part of the code consists of functions that are used to write data to the SD card. 

It logs the data in two files, one for the temperature data and one for the error data. The temperature data is logged every 30 seconds and the error data is logged when an error occurs.

## Functions

### createFileName

`char *createFileName` creates the file name for the file that is going to be created. It takes in three parameters, the first one is a boolean that is used to determine if the file is for the temperature data or the error data. The second parameter is the patient id and the third parameter is the start time of the measurement.

### initSD

`void initSD` initializes the SD card, and takes in one parameter, the chip select pin.

### createFile

`void createFile` creates the file that is going to be used to log the data. It takes in five parameters, the first one is the headers that are going to be written to the file. The second parameter is the file name that is going to be used. The third parameter is a boolean that is used to determine if the file is for the temperature data or the error data. The fourth parameter is the patient id and the fifth parameter is the start time of the measurement.

### convertDataToChar

`char *convertDataToChar` converts the data to a char array. It takes in five parameters, the first one is the temperature of the PCB, the second parameter is the temperature of the air, the third parameter is the temperature of the skin, the fourth parameter is the temperature of the LED and the fifth parameter is the date and time.

### convertErrorToChar

`char *convertErrorToChar` converts the error data to a char array. It takes in three parameters, the first one is the error code, the second parameter is the error message and the third parameter is the date and time.

### getExperimentId
`void getExperimentId` gets the experiment id from the SD card. It takes no parameters. It uses the folders already existing on the SD-card and increments the highest by one. If there is no previous experiment id it sets the experiment id to 0.

### writeInfoFile
`void writeInfoFile` writes the information about the experiment to the info file. It takes in five parameters, the first one is the test choices, the second parameter is the start time of the measurement, the third parameter is the file name, the fourth parameter is the experiment id and the fifth parameter is the patient id.


## Usage

This is only example usage of the functions. The functions can be used in the main code like the example below.

```cpp
#include "writeToFile/writeToFile.h"
#include <stdio.h>
#include <Arduino.h>
#include "utils.h"


char temp_headers[50] = "datetime,temp_pcb,temp_air,temp_skin,temp_led";
char error_headers[50] = "datetime,error_code,error_msg";


void setup()
{
  MEMORY_EXTENSION_PINS mem_ext_pins; 

  Serial.begin(9600);
  initSD(mem_ext_pins.CS);

  TestChoices test;
  test.mode = PLACEBO;
  test.duration = DURATION_30_MIN;
  test.pvm_freq = LOW_FREQUENCY;
  test.patient_id = 123;
  test.experiment_id = getExperimentId();
  const char *start_timestamp = "2021-05-12T12:12:12";
  const char *timestamp = "2021-05-12T12:12:12";


  delay(10);

  createDirectory(test.experiment_id);
  char *file_temp = createFileName(TEMP, test);
  char *file_error = createFileName(ERROR, test);
  char *file_info = createFileName(INFO, test);

  delay(10);

  createFile(temp_headers, file_temp, test);
  createFile(error_headers, file_error, test);
  createFile("Information about experiment", file_info, test);
  writeInfoFile(test, start_timestamp, file_info);
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