#include "writeToFile/writeToFile.h"
#include "getTime/getTime.h"
#include <stdio.h>
#include <Arduino.h>

char temp_headers[50] = "datetime, temp_pcb, temp_air, temp_skin, temp_led";
char error_headers[50] = "datetime, error, error_msg";

void setup(){
	Serial.begin(9600);
	char filename[] = "temp.csv";
	uint8_t create_file = createFile(filename, temp_headers);
	if (create_file == 1){
		fprintf(stderr, "File created successfully\n");
	} else {
		fprintf(stderr, "File creation failed\n");
	}
}
void loop() {
	const char* string1 = "Hello, ";
	const char* string2 = "world";

	const char* concatenatedString = createFileName(string1, string2);

	delay(30000);
}