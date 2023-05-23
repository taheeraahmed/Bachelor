#include "menu/menu.h"



uint8_t key;
bool PasswordCorrect = 0;
char password[6] = {'2','7','8','2','7','8'};   // Passorder for å aktivere funksjonalitetene til forskeren kan kun bestå av 6 siffer.
char password_in[6];
uint8_t counter = 0;
uint8_t menuState = 0;

//Midlertidig variabler som skal lagres eller forkastes
char tempPasientID[2];
uint8_t tempTestTime;
uint8_t tempNirSettings;
uint8_t tempTestMode;

//Variablene som skal lagres til CSV
char PasientID[2];
uint8_t TestTime;
uint8_t NirSettings;
uint8_t TestMode;
/*
Brukte denne eksempelkoden for å skreddersy tastaturet og initialisere det:
https://codebender.cc/example/Keypad/CustomKeypad#CustomKeypad.ino
*/

const byte ROWS = 4;        // fire rader
const byte COLS = 3;        // tre kolonner

char symbols_on_keypad[ROWS][COLS] = {       // Definerer tegnene som er tilkoblet til tastaturet
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[ROWS] = {22, 23, 24, 25};      // Pinnene som er tilknyttet radpinnene på tastaturet
byte colPins[COLS] = {26, 27, 28};          // Pinnene som er tilknyttet kolonnepinnene på tastaturet

// Initialiserer tastaturet ved å tilordne tegnene til tastene på tastaturet ved knytte de til  rad- og kolonnepinnene
Keypad customKeypad = Keypad( makeKeymap(symbols_on_keypad), rowPins, colPins, ROWS, COLS);

void waitForPassword(void){
    bool exit = 0;
    counter = 0;
    // Tømmer skjermen og setter inn grafikk for skjerm for CASE1
    clearScreen();
    setPasswordScreen();

    while (counter < 6){
        key = customKeypad.getKey();
        if (key == '1' | key == '2' | key == '3' | key == '4' | key == '5' | key == '6' | key == '7' | key == '8' | key == '9' | key == '0'){
            
            if (counter == 0){
                password_in[0] = key;
            }
            else if(counter == 1){
                password_in[1] = key;
            }
            else if (counter == 2){
                password_in[2] = key;
            }
            else if(counter == 3){
                password_in[3] = key;
            }
            else if (counter == 4){
                password_in[4] = key;
            }
            else if(counter == 5){
                password_in[5] = key;
            }
            counter += 1;
        }  
 
    }
    Serial.print("Passord:");
        Serial.print(password_in[0]);
        Serial.print(password_in[1]);
        Serial.print(password_in[2]);
        Serial.print(password_in[3]);
        Serial.print(password_in[4]);
        Serial.println(password_in[5]);


    counter = 0;
    for (uint8_t i = 0; i < 6; i++){
        if (password[i] == password_in[i]){
            PasswordCorrect = true;
            // Fortset til meny
        }
        else{
            PasswordCorrect = false;
            clearScreen();
            wrongPasswordScreen();
            delay(1000);
            break;
            // Tilbake til apt logo
        }
    }
}

void setPatientID(void){
    // Sett inn grafikk her
            clearScreen();
            setPatientIDScreen();
    while (counter < 2){

        
        key = customKeypad.getKey();
        if (key == '1' | key == '2' | key == '3' | key == '4' | key == '5' | key == '6' | key == '7' | key == '8' | key == '9' | key == '0'){
           
            if (counter == 0){
                tempPasientID[0] = key;
            }
            else if(counter == 1){
                tempPasientID[1] = key;
            }
            counter += 1;
        }  
        
    }
    Serial.print("Pasient ID:");
        Serial.print(tempPasientID[0]);
        Serial.println(tempPasientID[1]);
} 

void setTime(){
    char customKey = '0';

    clearScreen();
    chooseTimeScreen();
    while (customKey != '1' & customKey != '2' & customKey != '3'){
        customKey = customKeypad.getKey();
        
    }

    if (customKey == '1'){
        tempTestTime = 20;              //default minutter
    }
    else if (customKey == '2'){
        tempTestTime = 30;              //default minutter
    }
    else if (customKey == '3'){
        tempTestTime = 40;              //default minutter
    }
}

void showLed(uint8_t ledHead){
    char customKey = '0';
    // Sett in skjermbilde med led hode.
        clearScreen();
        getLEDHeadScreen();
    while (customKey != '*'){
        customKey = customKeypad.getKey();

        
    }
}

void chooseNIRsettings(void){
    char customKey = '0';

    // Sett inn grafikk her
    clearScreen();
    pulseNIRSettingsScreen();
    
    while (customKey != '1' & customKey != '2' & customKey != '3'){
        customKey = customKeypad.getKey();
        
    }

    if (customKey == '1'){
        tempNirSettings = 1;         // Kontinuelig
    }
    else if (customKey == '2'){
        tempNirSettings = 2;         // Høyfrekvent pulsering
    }
    else if (customKey == '3'){      // Lavfrekvent pulsering
        tempNirSettings = 3;
    }
}

void chooseMode(void){
    char customKey = '0';
    clearScreen();
    chooseModeScreen();

    while (customKey != '1' & customKey != '2' & customKey != '3'){
        customKey = customKeypad.getKey();
        
    }

    if (customKey == '1'){
        tempTestMode = 1;           // NIR-LYS
    }
    else if (customKey == '2'){
        tempTestMode = 2;           // PLACEBO
    }
    else if (customKey == '3'){
        tempTestMode = 3;           // RANDOMISERT
    }
}

void showSettings(void){
     char customKey = '0';
    clearScreen();
    showSettingsScreen();
    while(customKey != '*'){
        customKey = customKeypad.getKey();

        // Sett inn skjermbilde med temp values.
    }
}

void SaveOrExit(void){
    char customKey = '0';
    clearScreen();
    SaveOrExitScreen();
    while (customKey != '*' & customKey != '#'){
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

void systemWaiting(void){
    char customKey = '0'; //forandret på denne sånn at man hopper tilbake til hjemskjermen var char customKey;
    clearScreen();
    homeScreen();
    while (customKey != '*'){

        customKey = customKeypad.getKey();
    }
}

void RunMenu(void){
    while(1){
        switch(menuState){
            case 0:
                systemWaiting();
                menuState = 1;
                break;

             case 1:
                waitForPassword();
                if (PasswordCorrect == true){
                    menuState = 2;
                }
                else{
                    menuState = 3; // hvorfor hit og ikke direkte til 0?
                }
                break;

            case 2:

                setPatientID();
                menuState = 4;
                break;

            case 3: 
                menuState = 0;
                break;

            case 4:
                setTime();
                menuState = 10;
                break;
            
            case 10:
                showLed(1);
                menuState = 5;
                break;
            case 5:
                chooseNIRsettings();
                menuState = 6;
                break;

            case 6:
                chooseMode();
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