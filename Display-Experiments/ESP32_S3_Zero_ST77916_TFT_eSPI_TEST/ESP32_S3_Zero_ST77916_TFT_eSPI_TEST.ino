/*
2024.09.10
- 1.8 inch round display icindir: https://tr.aliexpress.com/item/1005007316063855.html?spm=a2g0o.order_list.order_list_main.31.4a783d1277oQyW&gatewayAdapt=glo2tur
- ESP32 S3 Zero board ile denendi
- TFT_eSPI dosyalari guncellendi: ST77196_Defines.h, ST77196_Init.h, ST77196_Rotation.h, TFT_eSPI.cpp, User_Setup_Select.h, Setup27tk_1_8Round_ST77916_ESP32.h (klasorde .zip dosyada)  
- Rotate ve swapbytes konusuna dikkat
*/


#include "Tekli.h"

#include <TFT_eSPI.h>       // Include the graphics library
TFT_eSPI tft = TFT_eSPI();  // Create object "tft"


// -------------------------------------------------------------------------
// Setup
// -------------------------------------------------------------------------
void setup(void) 
{
  Serial.begin(115200);
  tft.begin(); // initialize the display
  tft.setTextFont(2);
  tft.setTextSize(2);
  Serial.println("TFT_DARKGREY");
  tft.fillScreen(TFT_DARKGREY);
  delay(1000);
  tft.setSwapBytes(true);
  tft.pushImage(50,50,240,240,epd_bitmap_Taban);
  delay(1000);

}

// -------------------------------------------------------------------------
// Main loop
// -------------------------------------------------------------------------
void loop()
{
  for(uint8_t rd=0; rd<9; rd++)
  {
  tft.setRotation(rd);
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(50,50,240,240,epd_bitmap_Taban);

  Serial.println(rd);
  tft.setCursor(90,120);
  tft.print(rd);     
  tft.fillScreen(TFT_RED);
  tft.print(" - RED ");     
  Serial.println("RED ");
  delay(5000);
  
  tft.fillScreen(TFT_GREEN);
  tft.print("GREEN ");     
  Serial.println("GREEN ");
  delay(5000);
  
  tft.fillScreen(TFT_BLUE);
  tft.print("BLUE ");     
  Serial.println("BLUE ");
  delay(5000);
  }
}
