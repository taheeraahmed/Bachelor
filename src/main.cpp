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

  createDirectory(test.experiment_id);
  char *file_temp = createFileName(TEMP, test);
  char *file_error = createFileName(ERROR, test);
  char *file_info = createFileName(INFO, test);

  char temp_headers[50] = "datetime,temp_pcb,temp_air,temp_skin,temp_led";
  char error_headers[50] = "datetime,error_code,error_msg";
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