#include <SD.h>

File myFile;

/* 
- MOSI (Master Out Slave In): connect to Arduino Mega pin 51
- MISO (Master In Slave Out): connect to Arduino Mega pin 50
- SCK (Serial Clock): connect to Arduino Mega pin 52
- CS (Chip Select): you can use any available digital pin on the Arduino Mega, but for this example, let's use pin 53. Connect CS to Arduino Mega pin 53.
 */
void setup() {
  Serial.begin(9600);
  pinMode(53, OUTPUT); // Set CS pin as an output
  digitalWrite(53, HIGH); // Deselect the SD card
  
  //Initialize SD card
  if (!SD.begin(53)) { // Use pin 53 as the CS pin
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialization successful.");
  
  //Open file
  myFile = SD.open("test.txt", FILE_WRITE);
  
  //Write to file
  myFile.println("Hello world!");
  
  //Close file
  myFile.close();
}

void loop() {
}