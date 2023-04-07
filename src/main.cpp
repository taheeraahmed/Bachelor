#include <Arduino.h>
#include <Keypad.h>

                                          // Definerer antall rader og kolonner
const byte ROWS = 4;                      //fire rader
const byte COLS = 3;                      //tre kolonner

// Definerer symbolene tilhørende de forskjellige knappene på tastaturet
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
// 
byte rowPins[ROWS] = {22, 23, 24, 25};      //connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 27, 28};          //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
// Keypad(makeKeymap(userKeymap), row[], col[], rows, cols)

Keypad this_keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char customKey = this_keypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
}