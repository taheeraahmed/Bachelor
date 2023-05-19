#include "writeToFile/writeToFile.h"

uint8_t checkIfFileExists(char *filename)
{
	if (SD.exists(filename))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
 * @brief Function which initializes the SD card
 * @details The SD card is initialized on pin 53. This is the standard for Arduino Mega.
 * @return void
 */
void initSD()
{
	// Initialize SD card
	if (!SD.begin(53))
	{
		Serial.println("SD card initialization failed!");
	}
	else
	{
		Serial.println("SD card initialized successfully!");
	}
}

/**
 * @brief Function which creates a file
 * @details The file is closed after the write is complete.
 * @param headers: The headers to be written to the file
 * @param experiment_id: Used for creation of directory
 * @param is_error: Decides whether to create a file for errors or temperatures
 * @param patient_id: The patient id to be written to the filename
 * @return void
 */
void createFile(char *headers, char *filename, uint8_t patient_id, uint8_t experiment_id)
{
	// Convert experiment_id to char for directory name
	String experiment_id_str = String(experiment_id);
	const char *experiment_id_char = experiment_id_str.c_str();
	char experiment_id_buffer[20];
	strcpy(experiment_id_buffer, experiment_id_char);

	uint8_t file_exists = checkIfFileExists(filename);

	if (file_exists)
	{
		Serial.println("File already exists");
		return;
	}
	else
	{
		// Create directory
		if (!SD.mkdir(experiment_id_buffer))
		{
			Serial.println("Error creating directory!");
		}
		else
		{
			Serial.print("Directory created successfully: ");
			Serial.println(experiment_id_buffer);
		}

		// Creating a file with the name
		File file = SD.open(filename, FILE_WRITE);

		// If file is created successfully, write headers to file
		if (file)
		{
			Serial.print("File created successfully: ");
			Serial.println(filename);
			file.println(headers);
			file.close();
		}
		else
		{
			Serial.println("File not created");
			delete[] filename;
		};
	}
}

/**
 * @brief Function which creates a filename
 * @details The file is closed after the write is complete.
 * @param is_error: Decides whether to create a file for errors or temperatures
 * @param patient_id: The patient id to be written to the filename
 * @param experiment_id: Used for creation of directory
 * @return void
 */
char *createFileName(char *type, uint8_t patient_id, uint8_t experiment_id)
{
	// Convert experiment_id to char for directory name
	String experiment_id_str = String(experiment_id);
	const char *experiment_id_char = experiment_id_str.c_str();
	char experiment_id_buffer[20];
	strcpy(experiment_id_buffer, experiment_id_char);

	char *filename = new char[50];
	String type_str = String(type);

	if (type_str == "temp")
	{
		strcpy(filename, experiment_id_buffer);
		strcat(filename, "/log_");
		strcat(filename, String(patient_id).c_str());
		strcat(filename, ".csv");
	}
	else if (type_str == "error")
	{
		strcpy(filename, experiment_id_buffer);
		strcat(filename, "/err_");
		strcat(filename, String(patient_id).c_str());
		strcat(filename, ".csv");
	}
	else if (type_str == "info")
	{
		strcpy(filename, experiment_id_buffer);
		strcat(filename, "/info_");
		strcat(filename, String(patient_id).c_str());
		strcat(filename, ".csv");
	}
	return filename;
}

/**
 * @brief Function which writes temperatures and date to csv
 * @details The file is closed after the write is complete.
 * @param filename: Decieds which filename to write to
 * @param data: Could be both temperatures or errors to be logged
 */
void writeToFile(char *filename, char *data)
{
	File file;

	file = SD.open(filename, FILE_WRITE);

	if (file)
	{
		file.println(data);
		Serial.print("File written to successfully: ");
		Serial.println(filename);
		file.close();
		Serial.print("File closed successfully: ");
		Serial.println(filename);
	}
	else
	{
		Serial.println("File not found! writeToFile");
	}
	Serial.print("Write to file done: ");
	Serial.println(filename);
}
/**
 * @brief Function which converts temperature data to char
 * @details The function converts the temperature data to char and returns it
 * @param temp_pcb: The temperature of the PCB
 * @param temp_air: The temperature of the air
 * @param temp_skin: The temperature of the skin
 * @param temp_led: The temperature of the LED
 * @param timestamp: The timestamp to be written to the file
 * @return data: The data to be written to the file
 */

char *convertDataToChar(uint8_t temp_pcb, uint8_t temp_air, uint8_t temp_skin, uint8_t temp_led, const char *timestamp)
{
	char *data = new char[strlen(timestamp) + strlen(", ") + 4 * 4 + strlen("\n") + 1];
	strcpy(data, timestamp);
	strcat(data, ", ");
	strcat(data, String(temp_pcb).c_str());
	strcat(data, ", ");
	strcat(data, String(temp_air).c_str());
	strcat(data, ", ");
	strcat(data, String(temp_skin).c_str());
	strcat(data, ", ");
	strcat(data, String(temp_led).c_str());
	return data;
}

/**
 * @brief Function which converts error data to char
 * @details The function converts the error data to char and returns it
 * @param error_code: The error code to be written to the file
 * @param error_message: The error message to be written to the file
 * @param timestamp: The timestamp to be written to the file
 * @return data: The data to be written to the file
 */
char *convertErrorToChar(uint8_t error_code, const char *error_message, const char *timestamp)
{
	char *data = new char[strlen(timestamp) + strlen(", ") + 1 + strlen("\n") + 1];
	strcpy(data, timestamp);
	strcat(data, ", ");
	strcat(data, String(error_code).c_str());
	strcat(data, ", ");
	strcat(data, String(error_message).c_str());
	return data;
}

uint8_t getExperimentId(void)
{
	// Read experiment id from directory
	uint8_t experiment_id = 0;

	String directory_name = String(experiment_id);

	// Check if the folder already exists, and if so, increment the experiment ID and create a new folder name
	while (SD.exists(String(experiment_id)))
	{
		experiment_id++;
	}
	Serial.println("Experiment ID: " + String(experiment_id));
	return experiment_id;
};

void writeInfoFile(char *mode, char *pvm_freq, char *start_timestamp, char *duration, char *filename, uint8_t experiment_id, uint8_t patient_id)
{
	File file;

	file = SD.open(filename, FILE_WRITE);

	if (file)
	{
		file.print("Experiment ID: ");
		file.println(experiment_id);
		file.print("Patient ID: ");
		file.println(patient_id);
		file.print("Mode: ");
		file.println(mode);
		file.print("PVM Frequency: ");
		file.println(pvm_freq);
		file.print("Start timestamp: ");
		file.println(start_timestamp);
		file.print("Duration: ");
		file.println(duration);
		file.close();
	}
	else
	{
		Serial.println("File not found! writeToFile");
	}
	Serial.println("Write to file done");
}