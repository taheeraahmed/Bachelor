#ifndef STRUCTS_H
#define STRUCTS_H
#include <Arduino.h>

/**
 * @brief This struct is used to store the information about the file type
 * @details
 * The info file contains the information about the test.
 * The temp file contains the temperature data.
 * The error file contains the error data.
 * @returns A struct containing the file type with the following values: info, temp and error
 */
typedef enum
{
  INFO = 1,
  TEMP,
  ERROR
} FileType;

/**
 * @brief This enum is used to store the information about the test mode
 * @details The test mode can be either placebo, not placebo or double blinded
 * @returns A struct containing the test mode with one of the following values: placebo, not placebo and double blinded
 */

typedef enum
{
  PLACEBO = 1,
  NOT_PLACEBO,
  DOUBLE_BLINDED
} Mode;

/**
 * @brief This enum is used to store the information about the test duration
 * @details The test duration can be either 30 min or 45 min
 * @returns A struct containing the test duration with one of the following values: 30 min and 45 min
 */
typedef enum
{
  DURATION_30_MIN = 1,
  DURATION_45_MIN
} Duration;

/**
 * @brief This enum is used to store the information about the PVM frequency
 * @details The PVM frequency can be either continuous, low frequency or high frequency
 * @returns A struct containing the PVM frequency with one of the following values: continuous, low frequency and high frequency
 */
typedef enum
{
  CONTINUOUS = 1,
  LOW_FREQUENCY,
  HIGH_FREQUENCY
} PvmFreq;

/**
 * @brief This struct is used to store the information about the settings of the test
 * @details
 * The mode should be either placebo, not placebo or PWM.
 * The duration should be either 30 min or 45 min.
 * The pvm_freq should be either continous, low frequency or high frequency.
 * @returns A struct containing the test settings with the following values: mode, duration and pvm_freq
 */
typedef struct
{
  Mode mode;
  Duration duration;
  PvmFreq pvm_freq;
  uint8_t patient_id;
  uint8_t experiment_id;
} TestChoices;
/**
 * @brief This struct is used to store the information about the pins belonging to the memory extension
 * @details
 * The CS pin is the SPI chip select pin.
 * The DO pin is the SPI data out pin.
 * The DI pin is the SPI data in pin.
 * The CLK pin is the SPI clock pin.
 * The CD pin is the card detect pin I/O
 * @returns  A struct containing the memory extension pins with the following values: CS, DO, DI, CLK and CD
 */
typedef struct
{
  const int CS = 53;  // SPI chip select pin
  const int DO = 50;  // SPI data out pin
  const int DI = 51;  // SPI data in pin
  const int CLK = 52; // SPI clock pin
  const int CD = 49;  // Card detect pin I/O
} MEMORY_EXTENSION_PINS;

/**
 * @brief This struct is used to store the information about the pins belonging to the temperature sensors
 * @details
 * The PCB pin is the pin the PCB temperature sensor is connected to.
 * The LED pin is the pin the LED temperature sensor is connected to.
 * The AIR pin is the pin the air temperature sensor is connected to.
 * The SKIN pin is the pin measures the temperature value on the user's skin.
 * @returns A struct containing the temperature pins with the following values: PCB, LED, AIR and SKIN
 */
typedef struct
{
  const int PCB = A1;
  const int LED = A2;
  const int AIR = A3;
  const int SKIN = A4;
} TEMPERATURE_PINS;

/**
 * @brief This struct is used to store the information about the pins belonging to the fans
 * @details
 * The LED pin is the pin the LED is connected to.
 * The CONTROL pin is the pin the fan is connected to.
 * @returns A struct containing the fan pins with the following values: LED and CONTROL
 */
typedef struct
{
  const int LED = 10;
  const int CONTROL = 11;
} FAN_PINS;

/**
 * @brief This struct is used to store the error information.
 * @details
 * The error_no is the error number.
 * The category is the category of the error.
 * The error_text is the error text.
 * The failed_part is the part of the code which failed.
 * @returns A struct containing the error information with the following values: error_no, category, error_text and failed_part
 */
struct Error
{
  int error_no;
  String category;
  String error_text;
  String failed_part;
};

#endif // STRUCTS_H