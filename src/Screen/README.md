# Example code for running screen + menu

This is the code that has been used for testing and developing this part of the code

```cpp
#include <Arduino.h>
#include <menu/menu.h>
#include "Screen/Screen.h"

void setup() {
    Serial.begin(9600);
    initScreen();
}


void loop() {
    systemWaiting();
}
```