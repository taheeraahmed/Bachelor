#include "menu/menu.h"



uint8_t key;
bool PasswordCorrect = 0;
char password[6] = {2,7,8,2,7,8};
char password_in[6];
uint8_t counter = 0;
uint8_t menuState = 0;

char tempPasientID[2];
uint8_t tempTestTime;
uint8_t tempNirSettings;
uint8_t tempTestMode;

char PasientID[2];
uint8_t TestTime;
uint8_t NirSettings;
uint8_t TestMode;


const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[ROWS] = {22, 23, 24, 25}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 27, 28}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void waitForPassword(void){
    while (1){
        key = customKeypad.getKey();


        //Sett inn skjermbilde for passord her



        if (key != '0'){
            for (uint8_t i = 0; i < 5; i++){
                password_in[i] = password_in[i+1];
            }
            password_in[5] = key;
            counter += 1;
        }
        if (counter == 6){
            counter = 0;
            if (password == password_in){
                PasswordCorrect = true;
                // Fortset til meny
                menuState = 2;
            }
            else{
                PasswordCorrect = false;
                // Tilbake til apt logo
                menuState = 3;
            }
            break;
        }   
    }
}

void setPatientID(void){
    while (counter <= 2){

        // Sett inn grafikk her

        if (1){
            if (counter == 0){
                tempPasientID[1] = customKeypad.getKey();
            }
            else if(counter == 1){
                tempPasientID[0] = customKeypad.getKey();
            }
            counter += 1;
        }
        if (counter == 2){
            break;
        }   
    }
} 

void setTime(){
    char customKey = '0';
    while (customKey == '0'){
        customKey = customKeypad.getKey();

        // Sett inn grafikk her

    }

    if (customKey == '1'){
        tempTestTime = 20;
    }
    else if (customKey == '2'){
        tempTestTime = 30;
    }
    else if (customKey == '3'){
        tempTestTime = 40;
    }
}

void showLed(uint8_t ledHead){
    char customKey;
    while (customKey != '*'){
        customKey = customKeypad.getKey();

        // Sett in skjermbilde med led hode.
    }
}

void chooseNIRsettings(void){
    char customKey = '0';
    while (customKey == '0'){
        customKey = customKeypad.getKey();

        // Sett inn grafikk her
    }

    if (customKey == '1'){
        tempNirSettings = 1;
    }
    else if (customKey == '2'){
        tempNirSettings = 2;
    }
    else if (customKey == '3'){
        tempNirSettings = 3;
    }
}

void chooseTestsettings(void){
    char customKey = '0';
    while (customKey == '0'){
        // Sett inn grafikk her
        customKey = customKeypad.getKey();
    }

    if (customKey == '1'){
        tempTestMode = 1;
    }
    else if (customKey == '2'){
        tempTestMode = 2;
    }
    else if (customKey == '3'){
        tempTestMode = 3;
    }
}

void showSettings(void){
    char customKey;

    while(customKey != '*'){
        customKey = customKeypad.getKey();

        // Sett inn skjermbilde med temp values.
    }
}

void SaveOrExit(void){
    char customKey = '0';
    while (customKey == '0'){

        // Sett inn grafikk her
        customKey = customKeypad.getKey();
    }

    if (customKey == '*'){
        PasientID[0] = tempPasientID[0];
        PasientID[1] = tempPasientID[1];
        TestTime = tempTestTime;
        NirSettings = tempNirSettings;
        TestMode = tempTestMode;

        PasientID[0] = '0';
        PasientID[1] = '0';
        tempTestTime  = 0; 
        tempNirSettings = 0;
        tempTestMode = 0;
    }
    else if (customKey == '#'){
        PasientID[0] = '0';
        PasientID[1] = '0';
        tempTestTime  = 0; 
        tempNirSettings = 0;
        tempTestMode = 0;
    }
}

void RunMenu(void){
    while(1){
        switch(menuState){
            case 0:
                menuState = 1;
                break;

             case 1:
                waitForPassword();
                break;

            case 2:

                setPatientID();
                menuState = 4;
                break;

            case 3:
                // Feil passord
                menuState = 0;
                break;

            case 4:
                setTime();
                menuState = 5;
                break;
            
            case 5:
                chooseNIRsettings();
                menuState = 6;
                break;

            case 6:
                chooseTestsettings();
                menuState = 7;
                break;

            case 7:
                showSettings();
                menuState = 8;
                break;

            case 8: 
                SaveOrExit();
                menuState = 0;
                break;
        }
    }
}