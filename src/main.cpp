#include "settings/settings.h"
#include <Adafruit_I2CDevice.h>
#include "writeToFile/writeToFile.h"
#include "utils/utils.h"
TestChoices test2;
Sd2Card card;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Initializing SD card...");
  initSD(53);
  Serial.println("SD card initialized.");
  initCard(53, card);
  TestChoices test;
  test.mode = NIR_LIGHT;
  test.duration = DURATION_30_MIN;
  test.pvm_freq = LOW_FREQ;
  test.patient_id = 123;
  test.experiment_id = getExperimentId();
  Serial.println("BEFORE:");
  Serial.println(modeToString(test.mode));
  Serial.println(durationToString(test.duration));
  Serial.println(pvmFreqToString(test.pvm_freq));
  Serial.println(test.patient_id);
  Serial.println(test.experiment_id);
  Serial.println("--------------------");
  saveSettingsToFile(test);

  test2 = getSettingsFromFile();

  Serial.println("AFTER:");
  Serial.println(modeToString(test2.mode));
  Serial.println(durationToString(test2.duration));
  Serial.println(pvmFreqToString(test2.pvm_freq));
  Serial.println(test2.patient_id);
  Serial.println(test2.experiment_id);

  Serial.println("--------------------");
}

void loop()
{

  delay(50000);
}
