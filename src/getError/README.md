# Error handling

## Introduction
Here we create a global array which is has the size of number of errors. All through the code the index corresponding to the error will be set to one if an error occurs. If an error occurs the error will be logged to the SD card. The error handling is done in the `main()` function.

## Error messages

| Nummer i array | Varsling:            | Kategori         | Feilmeldingtekst                                      | Del av systemet som har feilet |
| -------------- | -------------------- | ---------------- | ----------------------------------------------------- | ------------------------------ |
| 0              |                      | Ingen feil       | Alt fungerer som det skal!                            | Hele                           |
| 1              | Status: Mindre feil  | Lavt batteri     | Lavt batteri, bør lades ved neste mulighet            | Batteri, BB                    |
| 2              | Status: Kritisk feil | SD Card          | SD Card initialization failed                         | initSD()                       |
| 3              | Status: Kritisk feil | SD Card          | SD Card not found                                     | initCard()                     |
| 4              | Status: Kritisk feil | Create directory | Creation of directory failed                          | createDirectory()              |
| 5              | Status: Kritisk feil | Create directory | Directory already exists                              | createDirectory()              |
| 6              | Status: Kritisk feil | Create file      | File already exists                                   | createFile()                   |
| 7              | Status: Kritisk feil | Create file      | File wasn't created                                   | createFile()                   |
| 8              | Status: Kritisk feil | Write to file    | Error with writing to file                            | writeFile()                    |
| 9              | Status: Kritisk feil | Write to file    | Error opening file                                    | writeFile()                    |
| 10             | Status: Kritisk feil | Write info-fille | Error opening file                                    | writeInfoFile()                |
| 11             | Status: Kritisk feil | Ubrukt           |                                                       |                                |
| 12             | Status: Mindre feil  | RTC Dato         | Henting av dagens dato fra RTC feilet.                | TWI, RTC                       |
| 13             | Status: Mindre feil  | RTC Tidsstempel  | Henting av klokkeslett fra RTC feilet.                | TWI, RTC                       |
| 14             | Status: Kritisk feil | DAC              | Kritisk feil: DAC                                     | TWI, DAC, LED-hodet, NIR-lys   |
| 15             | Status: Mindre feil  | Batterivakt      | Batteri % er ikke tilgjengelig                        | TWI, BB                        |
| 16             | Status: Mindre feil  | Batterivakt      | Batteriets helse er begynt å bli dårlig               | TWI, BB                        |
| 17             | Status: Kritisk feil | Temperatursensor | Kretskort i LED-hodet over 85 grader i ett minutt     | Overopphetning, LED-hode       |
| 18             | Status: Kritisk feil | Temperatursensor | Kretskort i styringsenhet over 70 grader i ett minutt | Overopphetning, styringsenhet  |
| 19             | Status: Kritisk feil | Temperatursensor | Hudtemperatur over 43 grader i et halvt minutt        | Overopphetning, hud            |
| 20             | Status: Kritisk feil | Temperatursensor | Lufttemperatur over 43 grader i ett minutt            | Overopphetning, luft           |