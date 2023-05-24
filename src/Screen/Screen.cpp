#include "Screen/Screen.h"
#include "utils/utils.h"
/*
Bruker "Adafruit ST7735 and ST7789 Library" elksempelkode "graphicstest" til oppsett og initialisering av skjermen.
https://github.com/adafruit/Adafruit-ST7735-Library/blob/master/examples/graphicstest/graphicstest.ino
I denne koden er det brukt en ST3577S skjerm på 1.8 inch TFT.
Oppkobling fra skjerm til Arduino er som følger:
LED –› 3.3V
SCK –› (52)
SDA –› (51)
A0 –› 34
RESET –› 33
CS –› 32
GND –› GND
VCC –› 5V
*/

const int TFT_CS = 32;  // (CS)
const int TFT_DC = 34;  // (A0)
const int TFT_RST = 33; // (RESET)


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST); // Bruker maskinvare SPI der SCLK (SCK) er koblet til pinne 52 og MOSI (SDA) er på pinne 51
/*
//Alternativt kan man bruke denne koden om man ikke skal bruke maskinvare SPI:
// Navn i parantes er navngiving på selve skjermpinnene

const int TFT_CS = 32;  // (CS)
const int TFT_DC = 34;  // (A0)
const int TFT_RST = 33; // (RESET)
const int TFT_MOSI = 35;  // (SDA)
const int TFT_SCLK = 36;  // (SCK)

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
*/

void initScreen()
{                               // Initialiserer skjermen
  tft.initR(INITR_BLACKTAB);    // Initialiserer en 1.8 inc TFT skjerm med ST7735S chip
                                // uint16_t time = millis();     // fjern dette ?
  tft.fillScreen(ST7735_BLACK); // Fyller skjermen med svart farge
                                // time = millis() - time;       // fjern dette ?
  tft.setRotation(3);           // Roterer skjermen 90 grader med klokken
}

void clearScreen()
{                               // tømmer skjermen for innhold
  tft.fillScreen(ST7735_BLACK); // farger hele skjermen svart
  tft.setCursor(0, 0);          // setter X og Y kordinatene til 0 og 0
  tft.setTextSize(1);           // setter tekst til orginal størrelse
}


void batteryCharge(uint8_t battery_charge)
{
  switch (battery_charge)
  {
  case 0:
    tft.drawBitmap(130, 1, batteri_1_5, 30, 15, ST7735_WHITE);
    break;
  case 1:
    tft.drawBitmap(130, 1, batteri_2_5, 30, 15, ST7735_WHITE);
    break;
  case 2:
    tft.drawBitmap(130, 1, batteri_3_5, 30, 15, ST7735_WHITE);
    break;
  case 3:
    tft.drawBitmap(130, 1, batteri_4_5, 30, 15, ST7735_WHITE);
    break;
  case 4:
    tft.drawBitmap(130, 1, batteri_5_5, 30, 15, ST7735_WHITE);
    break;
  }
}
void skinContactStatus(uint8_t skin_contact)
{
  switch (skin_contact)
  {
  case 0:
    greenRectangle();
    break;
  case 1:
    yellowRectangle();
    break;
  case 2:
    redRectangle();
    break;
  }
}

void drawDateAndBatteyCharge(uint8_t battery_charge, char date[8])
{
  batteryCharge(battery_charge);
  tft.setCursor(0, 5);
  tft.println("Dato: ");
  tft.setCursor(40, 5);
  tft.println(date);
}

void homeScreen(uint8_t battery_charge, char date[8])
{
  clearScreen();
  drawDateAndBatteyCharge(battery_charge, date);
  tft.drawBitmap(0, 16, logoAPT, 160, 113, ST7735_WHITE);       // her er APT sin logo
}

void setPasswordScreen(uint8_t battery_charge, char date[8])
{
  clearScreen();
  drawDateAndBatteyCharge(battery_charge, date);
  tft.setCursor(10, 30);
  tft.setTextSize(2);
  tft.println("\n Passord: ");
  tft.setTextSize(1);
  tft.setCursor(20, 110);
  tft.println(" .................. ");
}

void wrongPasswordScreen(uint8_t battery_charge, char date[8])
{
  clearScreen();
  drawDateAndBatteyCharge(battery_charge, date);
  tft.setCursor(10, 50);
  tft.setTextSize(2);
  tft.setTextColor(ST7735_WHITE);
  tft.print("Feil passord");
}

void setPatientIDScreen(uint8_t battery_charge, char date[8])
{
  clearScreen();
  drawDateAndBatteyCharge(battery_charge, date);
  tft.setTextSize(2);
  tft.setCursor(10, 30);
  tft.println("\n Pasient ID: ");
  tft.setTextSize(1);
  tft.setCursor(20, 110);
  tft.println(" .................. ");
}

void chooseTimeScreen(uint8_t battery_charge, char date[8])
{
  clearScreen();
  drawDateAndBatteyCharge(battery_charge, date);
  tft.setTextSize(2);
  tft.setCursor(10, 30);
  tft.setTextSize(2);
  tft.println("\n Velg tid: ");
  tft.setTextSize(1);
  tft.setCursor(10, 70);
  tft.println(" 1. 20 min");
  tft.setCursor(10, 90);
  tft.println(" 2. 30 min");
  tft.setCursor(10, 110);
  tft.println(" 3. 40 min");
}

void getLEDHeadScreen(uint8_t battery_charge, char date[8])
{
  clearScreen();
  drawDateAndBatteyCharge(battery_charge, date);
  tft.setTextSize(2);
  tft.setCursor(10, 30);
  tft.setTextSize(2);
  tft.println("\n LED-hode: ");
  tft.setTextSize(1);
  tft.setCursor(60, 80);
  tft.println("Hode: ");
  tft.setCursor(100, 80);
  tft.println("X");             //input LED-hode
}

void pulseNIRSettingsScreen(uint8_t battery_charge, char date[8])
{
  clearScreen();
  drawDateAndBatteyCharge(battery_charge, date);
  tft.setTextSize(2);
  tft.setCursor(10, 30);
  tft.setTextSize(2);
  tft.println(" Pulsering: ");
  tft.setTextSize(1);
  tft.setCursor(10, 70);
  tft.println(" 1. Kontinuelig");
  tft.setCursor(10, 90);
  tft.println(" 2. Hoyfrekvent pulsering");
  tft.setCursor(10, 110);
  tft.println(" 3. Lavfrekvent pulsering");
}

void chooseModeScreen(uint8_t battery_charge, char date[8])
{
  clearScreen();
  drawDateAndBatteyCharge(battery_charge, date);
  tft.setTextSize(2);
  tft.setCursor(10, 30);
  tft.setTextSize(2);
  tft.println("\n Modus: ");
  tft.setTextSize(1);
  tft.setCursor(10, 70);
  tft.println(" 1. Nir-lys");
  tft.setCursor(10, 90);
  tft.println(" 2. Placebo");
  tft.setCursor(10, 110);
  tft.println(" 3. Randomisert");
}

void showSettingsScreen(uint8_t battery_charge, char date[8], TestChoices test_choices)
{
  clearScreen();
  drawDateAndBatteyCharge(battery_charge, date);
  tft.setCursor(0, 30);
  tft.println("PasientID: ");
  tft.setCursor(65, 30);
  tft.println(test_choices.patient_id);                 // input pasientID
  tft.setCursor(0, 50);
  tft.println("Tid: ");
  tft.setCursor(65, 50);
  tft.println(durationToString(test_choices.duration)); // input Tid
  tft.setCursor(0, 70);
  tft.println("Hode:");
  tft.setCursor(65, 70);
  tft.println("3");                                     // input LED-hode
  tft.setCursor(0, 90);
  tft.println("Pulsering: ");
  tft.setCursor(65, 90);
  tft.println(pvmFreqToString(test_choices.pvm_freq)); // input Pulsering
  tft.setCursor(0, 110);
  tft.println("Modus:");
  tft.setCursor(65, 110);
  tft.println(modeToString(test_choices.mode)); // input Modus
}

void SaveOrExitScreen(uint8_t battery_charge, char date[8])
{
  clearScreen();
  drawDateAndBatteyCharge(battery_charge, date);
  tft.setTextSize(2);
  tft.setCursor(10, 30);
  tft.setTextSize(2);
  tft.println("\n Lagre -> * \n Exit -> # ");
}

void getSkinContactScreen(uint8_t battery_charge, char date[8], uint8_t skin_contact)
{
  clearScreen();
  drawDateAndBatteyCharge(battery_charge, date);
  tft.setCursor(10, 30);
  tft.setTextSize(2);
  tft.println("\n Opprett \n hudkontakt");
  skinContactStatus(skin_contact);
}

void selectStartButtonScreen(uint8_t battery_charge, char date[8], uint8_t skin_contact)
{
  clearScreen();
  drawDateAndBatteyCharge(battery_charge, date);
  tft.setCursor(10, 30);
  tft.setTextSize(2);
  tft.println("\n Trykk -> \n start knapp");
  skinContactStatus(skin_contact);
}

void runExperimentScreen(uint8_t battery_charge, char date[8], char remaining_seconds[2], char remaining_minutes[2], uint8_t skin_contact)
{
  clearScreen();
  drawDateAndBatteyCharge(battery_charge, date);
  tft.setCursor(0, 30);
  tft.println("PasientID: ");
  tft.setCursor(65, 30);
  tft.println("xx");
  tft.setCursor(0, 50);
  tft.println("Gjenstaaende tid: ");
  tft.setCursor(20, 70);
  tft.println(remaining_minutes);
  tft.setCursor(20, 90);
  tft.println(remaining_seconds);
  tft.setCursor(40, 70);
  tft.println("min ");
  tft.setCursor(40, 90);
  tft.println("sek");
  skinContactStatus(skin_contact);
}

void exitExperimentScreen(uint8_t battery_charge, char date[8])
{
  clearScreen();
  drawDateAndBatteyCharge(battery_charge, date);
  tft.setCursor(10, 30);
  tft.setTextSize(2);
  tft.println("\n \n Test ferdig!");
}

void criticalErrorScreen()
{
  clearScreen();
  tft.setCursor(0, 50);
  tft.setTextSize(2);
  tft.setTextColor(ST7735_WHITE);
  tft.print("Kritisk feil!");
  tft.setTextSize(1);
  tft.setCursor(8, 70);
  tft.println("Slaa av, prov igjen om 3 \n minutter");
}

void noSkinContactScreen()
{
  clearScreen();
  tft.setTextSize(2);
  tft.setCursor(50, 10);
  tft.print("Ingen");
  tft.setCursor(25, 40);
  tft.print("hudkontakt");
  tft.setCursor(30, 70);
  tft.print("opprettet");
  redRectangle();
}

void greenRectangle()
{
  tft.setTextSize(1);
  tft.setCursor(20, 110);
  tft.println("Hudkontakt: ");
  tft.fillRect(131, 106, 24, 20, ST7735_BLACK);
  tft.fillRect(133, 108, 20, 16, ST7735_GREEN);
}

void yellowRectangle()
{
  tft.setTextSize(1);
  tft.setCursor(20, 110);
  tft.println("Hudkontakt: ");
  tft.fillRect(131, 106, 24, 20, ST7735_BLACK);
  tft.fillRect(133, 108, 20, 16, ST7735_YELLOW);
}

void redRectangle()
{
  tft.setTextSize(1);
  tft.setCursor(20, 110);
  tft.println("Hudkontakt: ");
  tft.fillRect(131, 106, 24, 20, ST7735_BLACK);
  tft.fillRect(133, 108, 20, 16, ST7735_RED);
}
