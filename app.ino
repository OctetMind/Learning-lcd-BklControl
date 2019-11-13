#include <SPI.h>
#include "Ucglib.h"

// Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
Ucglib_ST7735_18x128x160_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);

#define blk_wiper A5
#define blk_pinout 6

int wiperValue = 0;
int blkValue = 0;
unsigned long previousMillis = 0;        // will store last time LED was updated
// constants won't change:
const long interval = 1000; 

void setup(void) {
  delay(1000);
  pinMode(blk_pinout, OUTPUT);
  pinMode(blk_wiper, INPUT);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.clearScreen();
}

void loop(void) {

   wiperValue = analogRead(blk_wiper);
    blkValue = map(wiperValue, 0, 1023, 0, 254);
    analogWrite(blk_pinout, blkValue);
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
        
    ucg.setRotate90();    
    ucg.setFontPosTop();
    ucg.setFont(ucg_font_ncenR14_tr);    
      
    ucg.setColor(0, 10, 0);
    ucg.drawBox(0, 25, 45, 20);        
    ucg.drawBox(0, 50, 45, 20);
    ucg.drawBox(0, 80, 45, 20);    
    
    ucg.setColor(255, 255, 255);
    ucg.setPrintPos(0,25);    
    ucg.println(wiperValue);
    ucg.setPrintPos(0,50);    
    ucg.print(blkValue);
  }  
}