#include <SPI.h>
#include <SD.h>

// Define the test choices

/*
  This function sets up the SD card and creates the CSV file.

  It takes the following parameters:
    CHIP_PIN: The chip select pin for the SD card
    startTime: The time the test started
    choices: The test choices made by the scientist/healthcare worker
*/

String setupReadCSV(MEMORY_EXTENSION_PINS memExtPins, unsigned long startTime, TestChoices choices) {
  // Create a string for assembling the data file name
  const String fileName = choices.mode + "_" + startTime; + "_sensor_data.csv";    

  // Open the CSV file for writing, filename must be char * 
  Serial.println("Opening and creating the CSV file.");
  File dataFile = SD.open(fileName.c_str(), FILE_WRITE);

  // Initialize the SD card
  if (!SD.begin(memExtPins.CS)) {
    Serial.println("Error initializing SD card.");
    return "Error initializing SD card.";
  }

  // Write the header row to the CSV file
  Serial.println("Writing the header row to the CSV file.");
  dataFile.println("Time, Temperature PCB, Temperature LED, Temperature Air, Temperature Skin");

  return fileName;
}

/*
  This function reads the sensor values and writes them to the CSV file.

  It takes the following parameters:
    tempPin: The pins the temperature sensors are connected to
    fileName: The name of the CSV file to write to
*/
void readSensorValues(TEMPERATURE_PINS temp_pins, const char *fileName) {
  // Read the sensor value
  int tempValue1 = analogRead(temp_pins.PCB);
  int tempValue2 = analogRead(temp_pins.LED);
  int tempValue3 = analogRead(temp_pins.AIR);
  int tempValue4 = analogRead(temp_pins.SKIN);
  
  // Get the current time
  unsigned long currentTime = millis();

  // Open the CSV file for writing
  File dataFile = SD.open(fileName, FILE_WRITE);

  // Write the sensor data to the CSV file
  dataFile.print(currentTime);
  dataFile.print(",");
  dataFile.print(tempValue1);
  dataFile.print(",");
  dataFile.print(tempValue2);
  dataFile.print(",");
  dataFile.print(tempValue3);
  dataFile.print(",");
  dataFile.println(tempValue4);

  // Wait a short period of time before taking another reading
  delay(1000);
}

/* 
  This function is called when the program is finished running.
  It closes the CSV file and prints a message to the serial monitor.

  It takes the following parameters:
    fileName: The name of the CSV file to write to
*/
void finishReadCSV(char *fileName) {
  // Close the CSV file
  File dataFile = SD.open(fileName, FILE_WRITE);
  dataFile.close();

  Serial.println("Finished writing to CSV file.");
}