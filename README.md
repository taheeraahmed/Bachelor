# Bachelor thesis

## Description

This code belongs to the bachelor thesis "Implementation of control unit and user interface for system with near infrared light". The 
work is based on the master thesis "Device for improved insulin absorption in diabetes type 1" by Patrick C. Bösch. The code is used to
control the prototype that is designed in the master thesis. The prototype is to be used in diabetes research. 
The remaining work consists of programming of the prototype,
with all the desired functionallities. In addition we want to a screen and a keypad
to the existing prototype. 
## Structure
The code is divided into different parts. Each part has its own folder and header file. The header files are located in the src folder. The header files are included in the main code and the functions are used in the main code.

```
├── README.md
├── src
│   ├── NIR
│   │   ├── NIR.c
│   │   └── NIR.h
│   ├── PWM
│   │   ├── PWM.c
│   │   └── PWM.h
│   ├── Screen
│   │   ├── README.md
│   │   ├── Screen.cpp
│   │   ├── Screen.h
│   │   └── logoGray.h
│   ├── TWI
│   │   ├── TWI.c
│   │   └── TWI.h
│   ├── Temp
│   │   ├── Temp.c
│   │   └── Temp.h
│   ├── getError
│   │   ├── README.md
│   │   ├── getError.c
│   │   └── getError.h
│   ├── getTime
│   │   ├── getTime.c
│   │   └── getTime.h
│   ├── ledControls
│   │   ├── ledControls.c
│   │   └── ledControls.h
│   ├── main.cpp
│   ├── mainFunctions
│   │   ├── mainFunctions.cpp
│   │   └── mainFunctions.h
│   ├── menu
│   │   ├── menu.cpp
│   │   └── menu.h
│   ├── settings
│   │   ├── README.md
│   │   ├── settings.cpp
│   │   └── settings.h
│   ├── utils
│   │   ├── pins.h
│   │   ├── utils.cpp
│   │   └── utils.h
│   └── writeToFile
│       ├── README.md
│       ├── helper.cpp
│       ├── writeToFile.cpp
│       └── writeToFile.h
```
### fan
This part of the code consists of functions that are used to control the fan.

### main
This part of the code consists of the main code. It is used to run the program.

### getTime
This part of the code consists of functions that are used to get the current time and date.

### PWM
This part of the code consists of functions that are used to control the PWM signal.

### Temp
This part of the code consists of functions that are used to read the temperature sensors.

### TWI
This part of the code consists of functions that are used to communicate with the temperature sensors and other I2C devices.

### writeToFile
This part of the code consists of functions that are used to write data to the SD card. 

It logs the data in two files, one for the temperature data and one for the error data. The temperature data is logged every 30 seconds and the error data is logged when an error occurs.

## Example code for getting started with the prototype

This is a simple function for testing if the red and green LEDs works. By putting the code in the main function, the LEDs will blink when the button is pressed.

```c
#include <avr/io.h>
// Enkel funksjon som får Rød og grønn led til å lyse ved knappetrykk.
// Skal kun brukes som referanse for koding av leds og knapp.

void BlinkeLed(){
  DDRG |= (1 << PIN1) | (1 << PIN0);
  DDRL |= (1 << PIN7);
  DDRH &= ~(1 << PIN6);

  while(1){
    if (PINH & (1 << PIN6)){
      PORTG |= (1 << PIN0);
      PORTL &= ~(1 << PIN7);
    }
    else {
      PORTL |= (1 << PIN7);
      PORTG &= ~(1 << PIN0);
    }
  }
}
```
