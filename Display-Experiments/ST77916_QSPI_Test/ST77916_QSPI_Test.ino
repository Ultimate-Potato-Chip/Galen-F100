/*
 * ST77916 - Working QSPI Base Code
 * Use this as your starting point
 * 
 * The protocol works! Now fix the power/refresh issue.
 */

#include <SPI.h>

#define TFT_CS    5
#define TFT_SCK   6
#define TFT_RST   7
#define TFT_D0    8
#define TFT_D1    9
#define TFT_BL    4

SPIClass *spi = NULL;
#define QSPI_WRITE_CMD  0x02

void setup() {
  pinMode(TFT_CS, OUTPUT);
  pinMode(TFT_RST, OUTPUT);
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_CS, HIGH);
  digitalWrite(TFT_BL, LOW);
  
  digitalWrite(TFT_RST, HIGH);
  delay(20);
  digitalWrite(TFT_RST, LOW);
  delay(50);
  digitalWrite(TFT_RST, HIGH);
  delay(150);

  spi = new SPIClass(HSPI);
  spi->begin(TFT_SCK, TFT_D1, TFT_D0, TFT_CS);
  
  initDisplay();
  digitalWrite(TFT_BL, HIGH);
  fillScreen(0xF800);  // RED
}

void loop() {
  // Keep trying to wake display
  delay(50);
  sendCmd(0x29, NULL, 0);  // Display ON
  sendCmd(0x00, NULL, 0);  // NOP
}

void sendCmd(uint8_t cmd, uint8_t* data, uint8_t len) {
  digitalWrite(TFT_CS, LOW);
  spi->beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  
  spi->transfer(QSPI_WRITE_CMD);
  spi->transfer(0x00);
  spi->transfer(cmd);
  spi->transfer(0x00);
  
  for (uint8_t i = 0; i < len; i++) {
    spi->transfer(data[i]);
  }
  
  spi->endTransaction();
  digitalWrite(TFT_CS, HIGH);
  delayMicroseconds(10);
}

void initDisplay() {
  uint8_t d;
  
  sendCmd(0x01, NULL, 0);
  delay(150);
  sendCmd(0x11, NULL, 0);
  delay(150);
  
  d = 0x08; sendCmd(0xF0, &d, 1);
  d = 0x08; sendCmd(0xF2, &d, 1);
  d = 0x51; sendCmd(0x9B, &d, 1);
  d = 0x53; sendCmd(0x86, &d, 1);
  d = 0x80; sendCmd(0xF2, &d, 1);
  d = 0x00; sendCmd(0xF0, &d, 1);
  d = 0x01; sendCmd(0xF0, &d, 1);
  d = 0x01; sendCmd(0xF1, &d, 1);
  
  d = 0x54; sendCmd(0xB0, &d, 1);
  d = 0x3F; sendCmd(0xB1, &d, 1);
  d = 0x2A; sendCmd(0xB2, &d, 1);
  d = 0x46; sendCmd(0xB4, &d, 1);
  d = 0x34; sendCmd(0xB5, &d, 1);
  d = 0xD5; sendCmd(0xB6, &d, 1);
  d = 0x30; sendCmd(0xB7, &d, 1);
  d = 0x00; sendCmd(0xBA, &d, 1);
  d = 0x08; sendCmd(0xBB, &d, 1);
  d = 0x08; sendCmd(0xBC, &d, 1);
  d = 0x00; sendCmd(0xBD, &d, 1);
  
  d = 0x80; sendCmd(0xC0, &d, 1);
  d = 0x10; sendCmd(0xC1, &d, 1);
  d = 0x37; sendCmd(0xC2, &d, 1);
  d = 0x80; sendCmd(0xC3, &d, 1);
  d = 0x10; sendCmd(0xC4, &d, 1);
  d = 0x37; sendCmd(0xC5, &d, 1);
  d = 0xA9; sendCmd(0xC6, &d, 1);
  d = 0x41; sendCmd(0xC7, &d, 1);
  d = 0x51; sendCmd(0xC8, &d, 1);
  d = 0xA9; sendCmd(0xC9, &d, 1);
  d = 0x41; sendCmd(0xCA, &d, 1);
  d = 0x51; sendCmd(0xCB, &d, 1);
  
  d = 0x91; sendCmd(0xD0, &d, 1);
  d = 0x68; sendCmd(0xD1, &d, 1);
  d = 0x69; sendCmd(0xD2, &d, 1);
  
  uint8_t f5[] = {0x00, 0xA5};
  sendCmd(0xF5, f5, 2);
  
  d = 0x35; sendCmd(0xDD, &d, 1);
  d = 0x35; sendCmd(0xDE, &d, 1);
  d = 0x10; sendCmd(0xF1, &d, 1);
  d = 0x00; sendCmd(0xF0, &d, 1);
  d = 0x02; sendCmd(0xF0, &d, 1);
  
  uint8_t e0[] = {0x70,0x09,0x12,0x0C,0x0B,0x27,0x38,0x54,0x4E,0x19,0x15,0x15,0x2C,0x2F};
  sendCmd(0xE0, e0, 14);
  
  uint8_t e1[] = {0x70,0x08,0x11,0x0C,0x0B,0x27,0x38,0x43,0x4C,0x18,0x14,0x14,0x2B,0x2D};
  sendCmd(0xE1, e1, 14);
  
  d = 0x10; sendCmd(0xF0, &d, 1);
  d = 0x10; sendCmd(0xF3, &d, 1);
  d = 0x0A; sendCmd(0xE0, &d, 1);
  d = 0x00; sendCmd(0xE1, &d, 1);
  d = 0x00; sendCmd(0xE2, &d, 1);
  d = 0x00; sendCmd(0xE3, &d, 1);
  d = 0xE0; sendCmd(0xE4, &d, 1);
  d = 0x06; sendCmd(0xE5, &d, 1);
  d = 0x21; sendCmd(0xE6, &d, 1);
  d = 0x00; sendCmd(0xE7, &d, 1);
  d = 0x05; sendCmd(0xE8, &d, 1);
  d = 0x82; sendCmd(0xE9, &d, 1);
  d = 0xDF; sendCmd(0xEA, &d, 1);
  d = 0x89; sendCmd(0xEB, &d, 1);
  d = 0x20; sendCmd(0xEC, &d, 1);
  d = 0x14; sendCmd(0xED, &d, 1);
  d = 0xFF; sendCmd(0xEE, &d, 1);
  d = 0x00; sendCmd(0xEF, &d, 1);
  d = 0xFF; sendCmd(0xF8, &d, 1);
  d = 0x00; sendCmd(0xF9, &d, 1);
  d = 0x00; sendCmd(0xFA, &d, 1);
  d = 0x30; sendCmd(0xFB, &d, 1);
  d = 0x00; sendCmd(0xFC, &d, 1);
  d = 0x00; sendCmd(0xFD, &d, 1);
  d = 0x00; sendCmd(0xFE, &d, 1);
  d = 0x00; sendCmd(0xFF, &d, 1);
  d = 0x00; sendCmd(0xF0, &d, 1);
  
  d = 0x55; sendCmd(0x3A, &d, 1);
  d = 0x00; sendCmd(0x36, &d, 1);
  sendCmd(0x13, NULL, 0);
  sendCmd(0x21, NULL, 0);
  sendCmd(0x29, NULL, 0);
  delay(200);
}

void fillScreen(uint16_t color) {
  uint8_t caset[] = {0x00, 0x00, 0x01, 0x67};
  sendCmd(0x2A, caset, 4);
  
  uint8_t raset[] = {0x00, 0x00, 0x01, 0x67};
  sendCmd(0x2B, raset, 4);
  
  digitalWrite(TFT_CS, LOW);
  spi->beginTransaction(SPISettings(30000000, MSBFIRST, SPI_MODE0));
  
  spi->transfer(QSPI_WRITE_CMD);
  spi->transfer(0x00);
  spi->transfer(0x2C);
  spi->transfer(0x00);
  
  for (uint32_t i = 0; i < 129600; i++) {
    spi->transfer16(color);
  }
  
  spi->endTransaction();
  digitalWrite(TFT_CS, HIGH);
}
