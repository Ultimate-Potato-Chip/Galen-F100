#pragma once

#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_err.h"
#include <stdint.h>

// ===========================================================================
// LCD Panel: SF-TO400XC-8996A2-N  (4.0" 720x720 IPS, NV3052CGRB)
// Interface: 3-wire SPI (init) + 16-bit RGB565 (pixel data)
// ===========================================================================

// Display resolution
#define LCD_H_RES   720
#define LCD_V_RES   720

// ---------------------------------------------------------------------------
// GPIO Pin Assignments  (ESP32-S3-DevKitC)
// ---------------------------------------------------------------------------

// 3-Wire SPI control (bit-banged, used only during init)
#define PIN_LCD_SPI_CS      39
#define PIN_LCD_SPI_SCK     48
#define PIN_LCD_SPI_MOSI    47

// LCD Reset (active low, min 10us low pulse per datasheet)
#define PIN_LCD_RST         21

// RGB interface control signals
#define PIN_LCD_PCLK        45
#define PIN_LCD_DE          46
#define PIN_LCD_HSYNC       40
#define PIN_LCD_VSYNC       41

// RGB565 data pins (16 bits -> panel 18-bit bus, see wiring table below)
//
// ESP32 data[n]  -> Panel Pin  -> Panel Signal
// ------------------------------------------------
// data[0]  GPIO 1   -> Pin 17 (DB1)  -> B3
// data[1]  GPIO 2   -> Pin 18 (DB2)  -> B4
// data[2]  GPIO 3   -> Pin 19 (DB3)  -> B5
// data[3]  GPIO 4   -> Pin 20 (DB4)  -> B6
// data[4]  GPIO 5   -> Pin 21 (DB5)  -> B7
// data[5]  GPIO 6   -> Pin 22 (DB6)  -> G2
// data[6]  GPIO 7   -> Pin 23 (DB7)  -> G3
// data[7]  GPIO 8   -> Pin 24 (DB8)  -> G4
// data[8]  GPIO 9   -> Pin 25 (DB9)  -> G5
// data[9]  GPIO 10  -> Pin 26 (DB10) -> G6
// data[10] GPIO 11  -> Pin 27 (DB11) -> G7
// data[11] GPIO 12  -> Pin 29 (DB13) -> R3
// data[12] GPIO 13  -> Pin 30 (DB14) -> R4
// data[13] GPIO 14  -> Pin 31 (DB15) -> R5
// data[14] GPIO 15  -> Pin 32 (DB16) -> R6
// data[15] GPIO 16  -> Pin 33 (DB17) -> R7
//
// Panel Pin 16 (DB0/B2) -> GND    (sacrificed LSB, saves 1 wire)
// Panel Pin 28 (DB12/R2) -> GND   (sacrificed LSB, saves 1 wire)

#define PIN_LCD_DATA0       1
#define PIN_LCD_DATA1       2
#define PIN_LCD_DATA2       3
#define PIN_LCD_DATA3       4
#define PIN_LCD_DATA4       5
#define PIN_LCD_DATA5       6
#define PIN_LCD_DATA6       7
#define PIN_LCD_DATA7       8
#define PIN_LCD_DATA8       9
#define PIN_LCD_DATA9       10
#define PIN_LCD_DATA10      11
#define PIN_LCD_DATA11      12
#define PIN_LCD_DATA12      13
#define PIN_LCD_DATA13      14
#define PIN_LCD_DATA14      15
#define PIN_LCD_DATA15      16

// RGB timing parameters (from panel datasheet section 6.2)
#define LCD_PIXEL_CLOCK_HZ      (16 * 1000 * 1000)  // 16 MHz start conservative
#define LCD_HSYNC_BACK_PORCH    44
#define LCD_HSYNC_FRONT_PORCH   46
#define LCD_HSYNC_PULSE_WIDTH   2
#define LCD_VSYNC_BACK_PORCH    16
#define LCD_VSYNC_FRONT_PORCH   50
#define LCD_VSYNC_PULSE_WIDTH   5

// ---------------------------------------------------------------------------
// Test pattern API
// ---------------------------------------------------------------------------

typedef enum {
    LCD_PATTERN_SOLID = 0,   // Single solid color (set via nv3052c_set_color)
    LCD_PATTERN_BARS,        // 8 vertical color bars
    LCD_PATTERN_GRADIENT,    // RGB gradient bands (top=red, mid=green, bot=blue)
} lcd_test_pattern_t;

/**
 * Initialize the NV3052C LCD panel.
 * Performs hardware reset, sends SPI init sequence, creates RGB panel.
 * Uses bounce buffers — no PSRAM required.
 */
esp_err_t nv3052c_init(void);

/**
 * Set the solid fill color (RGB565). Only visible when pattern = LCD_PATTERN_SOLID.
 */
void nv3052c_set_color(uint16_t color_rgb565);

/**
 * Switch the active test pattern. Takes effect on the next frame.
 */
void nv3052c_set_pattern(lcd_test_pattern_t pattern);