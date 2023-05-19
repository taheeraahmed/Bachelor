#include "writeToFile/writeToFile.h"
#include "getTime/getTime.h"
#include <stdio.h>
#include <Arduino.h>

char temp_headers[50] = "datetime,temp_pcb,temp_air,temp_skin,temp_led";
char error_headers[50] = "datetime,error_code,error_msg";

uint8_t patient_id = 123;
uint8_t experiment_id = getExperimentId();

const char *timestamp = "2021-05-12T12:12:12";

char *file_temp = createFileName("temp", patient_id, experiment_id);
char *file_error = createFileName("error", patient_id, experiment_id);
char *file_info = createFileName("info", patient_id, experiment_id);

void setup()
{
  Serial.begin(9600);
  initSD();
  createFile(temp_headers, file_temp, patient_id, experiment_id);
  createFile(error_headers, file_error, patient_id, experiment_id);
  createFile("Information about experiment", file_info, patient_id, experiment_id);
}
void loop()
{
  char *data = convertDataToChar(1, 2, 3, 4, "2021-05-12 12:12:12");
  writeToFile(file_temp, data);
  char *error = convertErrorToChar(1, "Error message", "2021-05-12 12:12:12");
  writeToFile(file_error, error);
  delay(2000);
}