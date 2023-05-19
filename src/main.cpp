#include "writeToFile/writeToFile.h"
#include <stdio.h>
#include <Arduino.h>


char temp_headers[50] = "datetime,temp_pcb,temp_air,temp_skin,temp_led";
char error_headers[50] = "datetime,error_code,error_msg";

char *file_temp;
char *file_error;
char *file_info;

char *mode = "Placebo";
char *pvm_freq = "10";
char *start_timestamp = "2021-05-12T12:12:12";
char *duration = "45 min";

const char *timestamp = "2021-05-12T12:12:12";

void setup()
{
  Serial.begin(9600);
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

  while(1){
    Serial.println("Writing to file");
    char *data = convertDataToChar(1, 2, 3, 4, timestamp);
    writeToFile(file_temp, data);
    char *error = convertErrorToChar(1, "Error message", timestamp);
    writeToFile(file_error, error);
    delay(1000); // Add a delay of 1 second (1000 milliseconds) between iterations
  }
}