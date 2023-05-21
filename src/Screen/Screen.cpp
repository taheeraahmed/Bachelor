#include "Screen/Screen.h"

const int TFT_CS = 32;          // CS
const int TFT_DC = 34;          // A0
const int TFT_RST = 33;         // RESET

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void initScreen(){
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;
  tft.setRotation(3);
}

void drawtextHeading(char *text, uint16_t color) {
  tft.setCursor(10, 30);
  tft.setTextColor(color);
  tft.setTextSize(2);
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
  tft.drawBitmap(130,1, batteri_1_5,30,15, ST7735_WHITE); //Her er possisjon og icon til batteriet batteryState her senere
  tft.drawBitmap(0,16,logoAPT,160,113, ST7735_WHITE); // her er APT sin logo
  testdrawtext("\n Dato: 4. mai 2023 ", ST7735_WHITE); //Her kan man sette inn datofunksjonen til Vilma
}

void clearScreen(){
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(1);
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