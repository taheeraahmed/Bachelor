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

├── src
│   ├── BlinkeLed.h
│   ├── PWM
│   │   ├── PWM.cpp
│   │   └── PWM.h
│   ├── TWI
│   │   ├── TWI.cpp
│   │   └── TWI.h
│   ├── Temp
│   │   ├── Temp.cpp
│   │   └── Temp.h
│   ├── fan
│   │   ├── fan.cpp
│   │   └── fan.h
│   ├── getTime
│   │   ├── getTime.cpp
│   │   └── getTime.h
│   ├── main.cpp
│   ├── utils.h
│   └── writeToFile
│       ├── README.md
│       ├── writeToFile.cpp
│       └── writeToFile.h

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