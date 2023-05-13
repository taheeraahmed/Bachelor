#include "writeToFile/writeToFile.h"
/**
 * @brief Function which creates a file, with a given filename and header
 * (for either temperatures or errors)
 * @details The file is closed after the write is complete.
 * @param filename: Decieds which filename to create
 * @param headers: The headers to be written to the file
 * @return 1: If the code has run successfully
*/
uint8_t createFile(char* filename, char* headers){
	File file;
	file = SD.open(filename, FILE_WRITE);
	if (file) {
		file.println(headers);
		file.close();
	} else {
		return 0;
	}
    return 1;
}

/**
 * @brief Function which writes temperatures and date to csv
 * @details The file is closed after the write is complete.
 * @param filename: Decieds which filename to write to 
 * @param data: Could be both temperatures or errors to be logged 
 * @param datetime: The timestamp of when the temperatures where taken
 * @return 1: If the code has run successfully
*/
uint8_t writeToFile(char* filename, char* data, char* datetime){
	File file;
	file = SD.open(filename, FILE_WRITE);
    if (file) {
		file.println(data);
		file.close();
	} else {
		return 0;
	}
    return 1;
}