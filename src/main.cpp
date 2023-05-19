#include "writeToFile/writeToFile.h"
#include "getTime/getTime.h"
#include <stdio.h>
#include <Arduino.h>

char temp_headers[50] = "datetime,temp_pcb,temp_air,temp_skin,temp_led";
char error_headers[50] = "datetime,error_code,error_msg";
uint8_t patient_id = 123;
uint8_t experiment_id = getExperimentId();

char *file_temp = createFileName("temp", patient_id, experiment_id);
char *file_error = createFileName("error", patient_id, experiment_id);
char *file_info = createFileName("info", patient_id, experiment_id);

void setup()
{
  Serial.begin(9600);
  uint8_t test = getExperimentId();
  Serial.print("experiment_id: in main ");
  Serial.println(test);
  Serial.println("Starting program..");
  initSD();
  createFile(temp_headers, file_temp, false, patient_id, experiment_id);
  createFile(error_headers, file_error, true, patient_id, experiment_id);
}
void loop()
{
  char *data = convertDataToChar(1, 2, 3, 4, "2021-05-12 12:12:12");
  writeToFile(file_temp, data);
  char *error = convertErrorToChar(1, "Error message", "2021-05-12 12:12:12");
  writeToFile(file_error, error);
  delay(2000);
}