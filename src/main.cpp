#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <stdint.h>
#include <SD.h>
/**
 * [] Finn ut om man kan få tilgang til minnebrikken uten å åpne opp undersiden
 * [] Finn ut om minnebrikken er formatert
 * [] Finn ut om man kan liste filer på minnebrikken
*/

#define SPI_SS   PB0   // Slave Select pin
#define SPI_MOSI PB2   // Master Out Slave In pin
#define SPI_MISO PB3   // Master In Slave Out pin
#define SPI_SCK  PB1   // Serial Clock pin

void spi_init(void)
{
    // Set SPI SS, MOSI, and SCK pins as outputs
    DDRB |= (1 << SPI_SS) | (1 << SPI_MOSI) | (1 << SPI_SCK);

    // Set SPI MISO pin as input
    DDRB &= ~(1 << SPI_MISO);

    // Enable SPI as master with clock rate fck/16
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);

    // Set SS pin high (disable slave)
    PORTB |= (1 << SPI_SS);
}

uint8_t spi_transfer(uint8_t data)
{
    // Start the SPI transaction by pulling SS pin low
    PORTB &= ~(1 << SPI_SS);

    // Send the data byte over SPI
    SPDR = data;

    // Wait for SPI transmission to complete
    while (!(SPSR & (1 << SPIF)));

    // End the SPI transaction by pulling SS pin high
    PORTB |= (1 << SPI_SS);

    // Return the received data byte
    return SPDR;
}


/**
 * [] Finn ut om man kan få tilgang til minnebrikken uten å åpne opp undersiden
 * [] Finn ut om minnebrikken er formatert
 * [] Finn ut om man kan liste filer på minnebrikken
*/
char filename[] = "text.txt";
File myFile;

void setup(){
	Serial.begin(9600);
	Serial.print("Initializing SD card...");
	// On the Ethernet Shield, CS is pin 4. It's set as an output by default.
	// Note that even if it's not used as the CS pin, the hardware SS pin
	// (10 on most Arduino boards, 53 on the Mega) must be left as an output
	// or the SD library functions will not work.
	//SD.mkdir(test);
	if (!SD.begin(53)) {
		Serial.println("initialization failed!");
		return;
	}
	Serial.println("initialization done.");
	// open the file. note that only one file can be open at a time,
	// so you have to close this one before opening another.
	myFile = SD.open(filename, FILE_WRITE);
	// if the file opened okay, write to it:
	if (myFile) {
		Serial.print("Writing to test.txt...");
		myFile.println("testing 1, 2, 3.");
		// close the file:
		myFile.close();
		Serial.println("done.");
	} else {
		// if the file didn't open, print an error:
		Serial.println("error opening test.txt");
	}
}
void loop() {
	// nothing happens after setup
	if(SD.exists(filename)){
		Serial.print("ja");
	}
}