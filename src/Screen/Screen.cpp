#include "Screen/Screen.h"
/*
Bruker "Adafruit ST7735 and ST7789 Library" elksempelkode "graphicstest" til oppsett og initialisering av skjermen.
https://github.com/adafruit/Adafruit-ST7735-Library/blob/master/examples/graphicstest/graphicstest.ino
I denne koden er det brukt en ST3577S skjerm på 1.8 inch TFT. 
Oppkobling fra skjerm til Arduino er som følger:
LED –› 3.3V
SCK –› 52
SDA –› 51
A0 –› 34
RESET –› 33
CS –› 32
GND –› GND
VCC –› 5V
*/

const int TFT_CS = 32;          // (CS)
const int TFT_DC = 34;          // (A0)
const int TFT_RST = 33;         // (RESET)

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);  // Bruker maskinvare SPI der SCLK (SCK) er koblet til pinne 52 og MOSI (SDA) er på pinne 51

void initScreen(){                // Initialiserer skjermen
  tft.initR(INITR_BLACKTAB);      // Initialiserer en 1.8 inc TFT skjerm med ST7735S chip
 // uint16_t time = millis();     // fjern dette ?
  tft.fillScreen(ST7735_BLACK);   // Fyller skjermen med svart farge
 // time = millis() - time;       // fjern dette ?
  tft.setRotation(3);             // Roterer skjermen 90 grader med klokken
}

void clearScreen(){                 // tømmer skjermen for innhold
  tft.fillScreen(ST7735_BLACK);     // farger hele skjermen svart
  tft.setCursor(0, 0);              // setter X og Y kordinatene til 0 og 0
  tft.setTextSize(1);               // setter tekst til orginal størrelse
}

void drawtextHeading(char *text, uint16_t color) {
  tft.setCursor(10, 30);
  tft.setTextSize(2);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void drawtextSkinContact(char *text, uint16_t color){ //int16_t x, int16_t y og sett setCursor(x,y)
  tft.setCursor(20,110);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.setTextSize(1);
  tft.print(text);
}

void drawtextDate(char *text, uint16_t color){
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void drawtextNormal(char *text, uint16_t color){
  tft.setTextColor(color);
  tft.setTextWrap(false);
  tft.print(text);
}

/*
unsigned char batteryState(uint8_t batterycharge){
  unsigned char batt;
  if (batterycharge == 1){ // 
  batt = batteri_1_5;
  }
  if (batterycharge == 2){ // 
  batt = batteri_2_5;
  }
  if (batterycharge == 3){ // 
  batt = batteri_3_5;
  }
  if (batterycharge == 4){ // 
  batt = batteri_4_5;
  }
  if (batterycharge == 5){ // 
  batt = batteri_5_5;
  }
  return batt;
}
*/

void homeScreen(){
  clearScreen();
  tft.drawBitmap(130,1, batteri_1_5,30,15, ST7735_WHITE);     //Her er possisjon og icon til batteriet batteryState her senere
  tft.drawBitmap(0,16,logoAPT,160,113, ST7735_WHITE);         //her er APT sin logo
  drawtextDate("\n Dato: 4. mai 2023 ", ST7735_WHITE);        //Her kan man sette inn datofunksjonen til Vilma
}

void setPasswordScreen(){
  clearScreen();
  tft.drawBitmap(130,1, batteri_2_5,30,15, ST7735_WHITE); //Her er possisjon og icon til batteriet batteryState her senere
  drawtextDate("\n Dato: ", ST7735_WHITE); //Her kan man sette inn datofunksjonen til Vilma
  tft.setTextSize(2);
  drawtextHeading("\n Passord: ", ST7735_WHITE);
  tft.setTextSize(1);
  tft.setCursor(20,110);
  drawtextNormal(" .................. ", ST7735_WHITE);
}

void setPatientIDScreen(){
  clearScreen();
  tft.drawBitmap(130,1, batteri_3_5,30,15, ST7735_WHITE); 
  drawtextDate("\n Dato: ", ST7735_WHITE);
  tft.setTextSize(2);
  drawtextHeading("\n Pasient ID: ", ST7735_WHITE);
  tft.setTextSize(1);
  tft.setCursor(20,110);
  drawtextNormal(" .................. ", ST7735_WHITE);
}

void chooseTimeScreen(){
  clearScreen();
  tft.drawBitmap(130,1, batteri_3_5,30,15, ST7735_WHITE); //Her er possisjon og icon til batteriet batteryState her senere
  drawtextDate("\n Dato: ", ST7735_WHITE); //Her kan man sette inn datofunksjonen til Vilma
  tft.setTextSize(2);
  drawtextHeading("\n Velg tid: ", ST7735_WHITE);
  tft.setTextSize(1);
  tft.setCursor(10,70);
  drawtextNormal(" 1. 20 min", ST7735_WHITE);
  tft.setCursor(10,90);
  drawtextNormal(" 2. 30 min", ST7735_WHITE);
  tft.setCursor(10,110);
  drawtextNormal(" 3. 40 min", ST7735_WHITE);
  
}

void getLEDHeadScreen(){
  clearScreen();
  tft.drawBitmap(130,1, batteri_3_5,30,15, ST7735_WHITE); //Her er possisjon og icon til batteriet batteryState her senere
  drawtextDate("\n Dato: ", ST7735_WHITE); //Her kan man sette inn datofunksjonen til Vilma
  tft.setTextSize(2);
    drawtextHeading("\n LED-hode: ", ST7735_WHITE);
  tft.setTextSize(1);
  tft.setCursor(60,80);
  drawtextNormal("Hode: ", ST7735_WHITE);
  tft.setCursor(100,80);
  drawtextNormal("X", ST7735_WHITE);      //input
}

void pulseNIRSettingsScreen(){
  clearScreen();
  tft.drawBitmap(130,1, batteri_3_5,30,15, ST7735_WHITE);          //input
  drawtextDate("\n Dato: ", ST7735_WHITE);                         //input
  tft.setTextSize(2);
    tft.setTextSize(2);
    drawtextHeading("\n Pulsering: ", ST7735_WHITE);
  tft.setTextSize(1);
  tft.setCursor(10,70);
  drawtextNormal(" 1. Kontinuelig", ST7735_WHITE);                //input
  tft.setCursor(10,90);
  drawtextNormal(" 2. Hoyfrekvent pulsering", ST7735_WHITE);      //input
  tft.setCursor(10,110);
  drawtextNormal(" 3. Lavfrekvent pulsering", ST7735_WHITE);      //input
}

void wrongPasswordScreen(){
  clearScreen();
  tft.drawBitmap(130,1, batteri_3_5,30,15, ST7735_WHITE);           // input
  drawtextDate("\n Dato: ", ST7735_WHITE);                          // input
  tft.setCursor(10,50);
  tft.setTextSize(2);
  tft.setTextColor(ST7735_WHITE);
  tft.print("Feil passord");
}


void chooseModeScreen(){
  clearScreen();
  tft.drawBitmap(130,1, batteri_3_5,30,15, ST7735_WHITE);         //input
  drawtextDate("\n Dato: ", ST7735_WHITE);                        //input
  tft.setTextSize(2);
  drawtextHeading("\n Modus: ", ST7735_WHITE);
  tft.setTextSize(1);
  tft.setCursor(10,70);
  drawtextNormal(" 1. Nir-lys", ST7735_WHITE);            //input
  tft.setCursor(10,90);
  drawtextNormal(" 2. Placebo", ST7735_WHITE);            //input
  tft.setCursor(10,110);
  drawtextNormal(" 3. Randomisert", ST7735_WHITE);        //input
}

void showSettingsScreen(){
  clearScreen();
  tft.drawBitmap(130,1, batteri_3_5,30,15, ST7735_WHITE);       //input batteri
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.println("\n Dato: ");                //input Dato
  tft.setCursor(0, 30);
  tft.println("PasientID: ");
  tft.setCursor(65, 30);
  tft.println("25");                    //input pasientID
  tft.setCursor(0, 50);
  tft.println("Tid: ");
  tft.setCursor(65, 50);
  tft.println("60 min ");               //input Tid
  tft.setCursor(0, 70);
  tft.println("Hode:");
  tft.setCursor(65, 70);
  tft.println("3");                      //input LED-hode
  tft.setCursor(0, 90);
  tft.println("Pulsering: ");
  tft.setCursor(65, 90);
  tft.println("Kontinuelig");           //input Pulsering
  tft.setCursor(0, 110);
  tft.println("Modus:");
  tft.setCursor(65, 110);
  tft.println("NIR");                   //input Modus
}

void SaveOrExitScreen(){
  clearScreen();
  tft.drawBitmap(130,1, batteri_3_5,30,15, ST7735_WHITE);     //input
  drawtextDate("\n Dato: ", ST7735_WHITE);                    //input
  tft.setTextSize(2);
  drawtextHeading("\n Lagre -> * \n Exit -> # ", ST7735_WHITE);
}

void getSkinContactScreen(){
  clearScreen();
  drawtextDate("\n Dato: ", ST7735_WHITE);
  tft.drawBitmap(130,1, batteri_3_5,30,15, ST7735_WHITE);
  drawtextHeading("\n Opprett \n hudkontakt", ST7735_WHITE);
  redRectangle();
}

void selectStartButtonScreen(){
  clearScreen();
  drawtextDate("\n Dato: ", ST7735_WHITE);
  tft.drawBitmap(130,1, batteri_3_5,30,15, ST7735_WHITE);
  drawtextHeading("\n Trykk -> \n start knapp", ST7735_WHITE);
  redRectangle();
}

void runExperimentScreen(){
  clearScreen();
  tft.drawBitmap(130,1, batteri_3_5,30,15, ST7735_WHITE);       //input batteri
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.println("Dato: ");                //input Dato
  tft.setCursor(0, 30);
  tft.println("PasientID: ");
  tft.setCursor(65, 30);
  tft.println("x x");                    //input pasientID
  tft.setCursor(0, 50);
  tft.println("Gjenstaaende tid: ");
  tft.setCursor(20, 70);
  tft.println("60");                   //input Tid
  tft.setCursor(20, 90);
  tft.println("30");                      //input LED-hode
  tft.setCursor(40, 70);
  tft.println("min ");                   //input Tid
  tft.setCursor(40, 90);
  tft.println("sek"); 
  redRectangle();
}

void exitExperimentScreen(){
  clearScreen();
  drawtextDate("\n Dato: ", ST7735_WHITE);
  tft.drawBitmap(130,1, batteri_3_5,30,15, ST7735_WHITE);
  drawtextHeading("\n \n Test ferdig!", ST7735_WHITE);
}


void overheatingScreen(){
  clearScreen();
  tft.setCursor(0,50);
  tft.setTextSize(2);
  tft.setTextColor(ST7735_WHITE);
  tft.print("Overoppheting");
  tft.setTextSize(1);
  tft.setCursor(8,70);
  drawtextNormal("Slaa av, prov igjen om 3 \n minutter", ST7735_WHITE);

}

void noSkinContactScreen(){
  clearScreen();
  tft.setTextSize(2);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(50,10);
  tft.print("Ingen");
  tft.setCursor(25,40);
  tft.print("hudkontakt");
  tft.setCursor(30,70);
  tft.print("opprettet");
  redRectangle();                   //input
}

void greenRectangle(){
  tft.fillRect(131,106,24,20,ST7735_BLACK);
  tft.fillRect(133,108,20,16,ST7735_GREEN);
  drawtextSkinContact("Hudkontakt: ", ST7735_WHITE);
}

void yellowRectangle(){
  tft.fillRect(131,106,24,20,ST7735_BLACK);
  tft.fillRect(133,108,20,16,ST7735_YELLOW);
  drawtextSkinContact("Hudkontakt: ", ST7735_WHITE);
}

void redRectangle(){
  tft.fillRect(131,106,24,20,ST7735_BLACK);
  tft.fillRect(133,108,20,16,ST7735_RED);
  drawtextSkinContact("Hudkontakt: ", ST7735_WHITE);
}