#include "writeToFile/writeToFile.h"

/**
 * @brief Function which initializes the SD card
 * @details The SD card is initialized on pin 53. This is the standard for Arduino Mega.
 * @param CS: Chip select pin
 * @return void
 */
void initSD(int CS)
{
	// Initialize SD card
	if (!SD.begin(CS))
	{
		Serial.println("SD card initialization failed!");
	}
	else
	{
		Serial.println("SD card initialized successfully!");
	}
}

/**
 * @brief Function which initializes the SD card
 * @details The SD card is initialized on pin 53. This is the standard for Arduino Mega.
 * @param CS: Chip select pin
 * @param card: SD card
 * @return void
 */
void initCard(int CS, Sd2Card card)
{
	if (!card.init(SPI_HALF_SPEED, CS))
	{

		Serial.println("initialization failed. Things to check:");
		Serial.println("* is a card inserted?");
		Serial.println("* is your wiring correct?");
		Serial.println("* did you change the chipSelect pin to match your shield or module?");
		while (1)
			;
	}
	else
	{
		Serial.println("Wiring is correct and a card is present.");
	}
}

/**
 * @brief Function which creates a directory
 * @details The directory is created on the SD card
 * @param experiment_id: Used for creation of directory
 * @return void
 */
void createDirectory(uint8_t experiment_id)
{
	// Convert experiment_id to char for directory name
	String experiment_id_str = String(experiment_id);
	const char *experiment_id_char = experiment_id_str.c_str();
	char experiment_id_buffer[20];
	strcpy(experiment_id_buffer, experiment_id_char);

	// Create directory if it doesn't exist
	uint8_t dir_exists = SD.exists(experiment_id_buffer);
	if (dir_exists)
	{
		Serial.print("Directory already exists: ");
		Serial.println(experiment_id_buffer);
	}
	else
	{
		if (!SD.mkdir(experiment_id_buffer))
		{
			Serial.println("Error creating directory!");
		}
		else
		{
			Serial.print("Directory created successfully: ");
			Serial.println(experiment_id_buffer);
		}
	}
}

/**
 * @brief Function which creates a file
 * @details The file is closed after the write is complete.
 * @param headers: The headers to be written to the file
 * @param filename: The filename to be created
 * @param test_choices: The test choices struct 
 * @return void
 */
void createFile(char *headers, char *filename, TestChoices test_choices)
{
	// Convert experiment_id to char for directory name
	String experiment_id_str = String(test_choices.experiment_id);
	const char *experiment_id_char = experiment_id_str.c_str();
	char experiment_id_buffer[20];
	strcpy(experiment_id_buffer, experiment_id_char);

	uint8_t file_exists = checkIfFileExists(filename);

	if (file_exists)
	{
		return;
	}
	else
	{
		// Creating a file with the name
		File file = SD.open(filename, FILE_WRITE);

		// If file is created successfully, write headers to file
		if (file)
		{
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
 * @param type: The type of file to be created either temp, error or info
 * @param test_choices: The test choices struct
 * @return void
 */
char *createFileName(FileType type, TestChoices test_choices)
{
	// Convert experiment_id to char for directory name
	String experiment_id_str = String(test_choices.experiment_id);
	const char *experiment_id_char = experiment_id_str.c_str();
	char experiment_id_buffer[20];
	strcpy(experiment_id_buffer, experiment_id_char);

	char *filename = new char[50];

	if (type == TEMP)
	{
		strcpy(filename, experiment_id_buffer);
		strcat(filename, "/log_");
		strcat(filename, String(test_choices.patient_id).c_str());
		strcat(filename, ".csv");
	}
	else if (type == ERROR)
	{
		strcpy(filename, experiment_id_buffer);
		strcat(filename, "/err_");
		strcat(filename, String(test_choices.patient_id).c_str());
		strcat(filename, ".csv");
	}
	else if (type == INFO)
	{
		strcpy(filename, experiment_id_buffer);
		strcat(filename, "/info_");
		strcat(filename, String(test_choices.patient_id).c_str());
		strcat(filename, ".txt");
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
		if (file.write(data, strlen(data)))
		{
			// Data write successful
			file.close();
		}
		else
		{
			// Error writing data
			file.close();
			Serial.print("Error writing to file: ");
			Serial.println(filename);
		}
	}
	else
	{
		Serial.print("Failed to open file: ");
		Serial.println(filename);
	}
}

/**
 * @brief Function which writes info to csv
 * @details The file is closed after the write is complete.
 * @param mode: The mode to be written to the file
 * @param pvm_freq: The PVM frequency to be written to the file
 * @param start_timestamp: The start timestamp to be written to the file
 * @param duration: The duration to be written to the file
 * @param filename: The filename to be written to the file
 * @param experiment_id: The experiment ID to be written to the file
 * @param patient_id: The patient ID to be written to the file
 */
void writeInfoFile(TestChoices test_choices, const char *start_timestamp, char *filename)
{
	File file;

	file = SD.open(filename, FILE_WRITE);

	if (file)
	{
		file.print("Experiment ID: ");
		file.println(test_choices.experiment_id);
		file.print("Patient ID: ");
		file.println(test_choices.patient_id);
		file.print("Mode: ");
		file.println(modeToString(test_choices.mode));
		file.print("PVM Frequency: ");
		file.println(pvmFreqToString(test_choices.pvm_freq));
		file.print("Start timestamp: ");
		file.println(start_timestamp);
		file.print("Duration: ");
		file.println(durationToString(test_choices.duration));
		file.close();
	}
	else
	{
		Serial.println("File not found! writeToFile");
	}
}