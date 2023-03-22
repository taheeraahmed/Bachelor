struct TestChoices {
  int mode;     // (1) Placebo, (2) Not Placebo (3) PWM 
  int duration; // (1) 30 min (2) 45 min
  int pvm_freq; // (1) ??  (2) ?? (3) ?? 
};

struct MEMORY_EXTENSION_PINS {
  const int CS = 53;    // SPI chip select pin
  const int DO = 50;    // SPI data out pin
  const int DI = 51;    // SPI data in pin
  const int CLK = 52;   // SPI clock pin
  const int CD = 49;    // Card detect pin I/O
};

struct TEMPERATURE_PINS {
  const int PCB = A1;
  const int LED = A2;
  const int AIR = A3;
  const int SKIN = A4;
};