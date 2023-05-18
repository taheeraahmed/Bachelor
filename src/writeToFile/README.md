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
#include "getTime/getTime.h"
#include <stdio.h>
#include <Arduino.h>

char temp_headers[50] = "datetime,temp_pcb,temp_air,temp_skin,temp_led";
char error_headers[50] = "datetime,error_code,error_msg";
uint8_t patient_id = 123;
uint8_t start_time = 0;

char *file_temp = createFileName(false, patient_id, start_time);
char *file_error = createFileName(true, patient_id, start_time);

void setup()
{
	Serial.begin(9600);
	Serial.println("Starting program..");
	initSD();
	createFile(temp_headers, file_temp, false, patient_id, start_time);
	createFile(error_headers, file_error, true, patient_id, start_time);
}
void loop()
{
	char *data = convertDataToChar(1, 2, 3, 4, "2021-05-12 12:12:12");
	writeToFile(file_temp, data);
	char *error = convertErrorToChar(1, "Error message", "2021-05-12 12:12:12");
	writeToFile(file_error, error);
	delay(6000);
}
```