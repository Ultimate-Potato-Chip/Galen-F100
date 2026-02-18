#include "nv3052c.h"

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_check.h"
#include "esp_attr.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"
#include "rom/ets_sys.h"

static const char *TAG = "nv3052c";

// ---------------------------------------------------------------------------
// 3-Wire SPI (9-bit, bit-banged) — used only for NV3052C register init
//
// Protocol: 9 bits per transfer, MSB first
//   bit[8] = 0 -> command byte
//   bit[8] = 1 -> data byte
// ---------------------------------------------------------------------------

static void spi_write_9bit(uint16_t data9)
{
    gpio_set_level(PIN_LCD_SPI_CS, 0);
    for (int i = 8; i >= 0; i--) {
        gpio_set_level(PIN_LCD_SPI_SCK, 0);
        gpio_set_level(PIN_LCD_SPI_MOSI, (data9 >> i) & 1);
        ets_delay_us(1);
        gpio_set_level(PIN_LCD_SPI_SCK, 1);
        ets_delay_us(1);
    }
    gpio_set_level(PIN_LCD_SPI_CS, 1);
    ets_delay_us(1);
}

static inline void lcd_cmd(uint8_t cmd)  { spi_write_9bit(cmd); }
static inline void lcd_data(uint8_t d)   { spi_write_9bit(0x100 | d); }
static inline void lcd_reg(uint8_t r, uint8_t v) { lcd_cmd(r); lcd_data(v); }

// ---------------------------------------------------------------------------
// NV3052C Register Init Sequence
// Source: Adafruit HD40015C40 / Arduino_GFX (also a 720x720 NV3052C panel)
// ---------------------------------------------------------------------------

typedef struct { uint8_t reg; uint8_t val; } nv3052c_reg_t;

static const nv3052c_reg_t nv3052c_init_regs[] = {
    // ---- Page 1: Power, VCOM, analog ----
    {0xFF,0x30},{0xFF,0x52},{0xFF,0x01},
    {0xE3,0x00},{0x0A,0x11},{0x23,0xA0},{0x24,0x32},{0x25,0x12},
    {0x26,0x2E},{0x27,0x2E},{0x29,0x02},{0x2A,0xCF},{0x32,0x34},
    {0x38,0x9C},{0x39,0xA7},{0x3A,0x27},{0x3B,0x94},
    {0x42,0x6D},{0x43,0x83},{0x81,0x00},
    {0x91,0x67},{0x92,0x67},
    {0xA0,0x52},{0xA1,0x50},{0xA4,0x9C},{0xA7,0x02},{0xA8,0x02},
    {0xA9,0x02},{0xAA,0xA8},{0xAB,0x28},{0xAE,0xD2},{0xAF,0x02},
    {0xB0,0xD2},{0xB2,0x26},{0xB3,0x26},

    // ---- Page 2: Gamma ----
    {0xFF,0x30},{0xFF,0x52},{0xFF,0x02},
    {0xB1,0x0A},{0xD1,0x0E},{0xB4,0x2F},{0xD4,0x2D},
    {0xB2,0x0C},{0xD2,0x0C},{0xB3,0x30},{0xD3,0x2A},
    {0xB6,0x1E},{0xD6,0x16},{0xB7,0x3B},{0xD7,0x35},
    {0xC1,0x08},{0xE1,0x08},{0xB8,0x0D},{0xD8,0x0D},
    {0xB9,0x05},{0xD9,0x05},{0xBD,0x15},{0xDD,0x15},
    {0xBC,0x13},{0xDC,0x13},{0xBB,0x12},{0xDB,0x10},
    {0xBA,0x11},{0xDA,0x11},{0xBE,0x17},{0xDE,0x17},
    {0xBF,0x0F},{0xDF,0x0F},{0xC0,0x16},{0xE0,0x16},
    {0xB5,0x2E},{0xD5,0x3F},{0xB0,0x03},{0xD0,0x02},

    // ---- Page 3: GIP timing & pin mapping ----
    {0xFF,0x30},{0xFF,0x52},{0xFF,0x03},
    {0x08,0x09},{0x09,0x0A},{0x0A,0x0B},{0x0B,0x0C},
    {0x28,0x22},{0x2A,0xE9},{0x2B,0xE9},
    {0x34,0x51},{0x35,0x01},{0x36,0x26},{0x37,0x13},
    {0x40,0x07},{0x41,0x08},{0x42,0x09},{0x43,0x0A},
    {0x44,0x22},{0x45,0xDB},{0x46,0xDC},{0x47,0x22},{0x48,0xDD},{0x49,0xDE},
    {0x50,0x0B},{0x51,0x0C},{0x52,0x0D},{0x53,0x0E},
    {0x54,0x22},{0x55,0xDF},{0x56,0xE0},{0x57,0x22},{0x58,0xE1},{0x59,0xE2},
    {0x80,0x1E},{0x81,0x1E},{0x82,0x1F},{0x83,0x1F},
    {0x84,0x05},{0x85,0x0A},{0x86,0x0A},{0x87,0x0C},{0x88,0x0C},
    {0x89,0x0E},{0x8A,0x0E},{0x8B,0x10},{0x8C,0x10},
    {0x8D,0x00},{0x8E,0x00},{0x8F,0x1F},{0x90,0x1F},
    {0x91,0x1E},{0x92,0x1E},{0x93,0x02},{0x94,0x04},
    {0x96,0x1E},{0x97,0x1E},{0x98,0x1F},{0x99,0x1F},
    {0x9A,0x05},{0x9B,0x09},{0x9C,0x09},{0x9D,0x0B},{0x9E,0x0B},
    {0x9F,0x0D},{0xA0,0x0D},{0xA1,0x0F},{0xA2,0x0F},
    {0xA3,0x00},{0xA4,0x00},{0xA5,0x1F},{0xA6,0x1F},
    {0xA7,0x1E},{0xA8,0x1E},{0xA9,0x01},{0xAA,0x03},

    // ---- Page 0: Display control ----
    {0xFF,0x30},{0xFF,0x52},{0xFF,0x00},
    {0x36,0x0A},  // MADCTL: scan direction
};

// ---------------------------------------------------------------------------
// Bounce buffer state — written from app, read from ISR callback
// ---------------------------------------------------------------------------

static volatile uint16_t        s_fill_color = 0x0000;
static volatile lcd_test_pattern_t s_pattern = LCD_PATTERN_SOLID;

static const uint16_t BAR_COLORS[] = {
    0xF800,  // Red
    0x07E0,  // Green
    0x001F,  // Blue
    0xFFFF,  // White
    0xFFE0,  // Yellow
    0x07FF,  // Cyan
    0xF81F,  // Magenta
    0x0000,  // Black
};
#define NUM_BARS  (sizeof(BAR_COLORS) / sizeof(BAR_COLORS[0]))

// Called from ISR — must be in IRAM, no heap, no printf
static bool IRAM_ATTR lcd_bounce_fill_cb(esp_lcd_panel_handle_t panel,
                                          void *bounce_buf,
                                          int pos_px,
                                          int len_bytes,
                                          void *user_ctx)
{
    uint16_t *buf = (uint16_t *)bounce_buf;
    int len_px = len_bytes / 2;
    lcd_test_pattern_t pat = s_pattern;

    switch (pat) {

        case LCD_PATTERN_BARS:
            for (int i = 0; i < len_px; i++) {
                int x = (pos_px + i) % LCD_H_RES;
                buf[i] = BAR_COLORS[(x * NUM_BARS) / LCD_H_RES];
            }
            break;

        case LCD_PATTERN_GRADIENT: {
            int band_h = LCD_V_RES / 3;
            for (int i = 0; i < len_px; i++) {
                int abs_px = pos_px + i;
                int y = abs_px / LCD_H_RES;
                int x = abs_px % LCD_H_RES;
                uint16_t c;
                if (y < band_h) {
                    c = ((uint16_t)((x * 31) / (LCD_H_RES - 1))) << 11; // Red
                } else if (y < band_h * 2) {
                    c = ((uint16_t)((x * 63) / (LCD_H_RES - 1))) << 5;  // Green
                } else {
                    c = (uint16_t)((x * 31) / (LCD_H_RES - 1));         // Blue
                }
                buf[i] = c;
            }
            break;
        }

        case LCD_PATTERN_SOLID:
        default: {
            uint16_t color = s_fill_color;
            for (int i = 0; i < len_px; i++) {
                buf[i] = color;
            }
            break;
        }
    }
    return false;  // No high-priority task woken
}

// ---------------------------------------------------------------------------
// Initialisation helpers
// ---------------------------------------------------------------------------

static void spi_gpio_init(void)
{
    gpio_config_t io = {
        .pin_bit_mask = (1ULL << PIN_LCD_SPI_CS)   |
                        (1ULL << PIN_LCD_SPI_SCK)   |
                        (1ULL << PIN_LCD_SPI_MOSI)  |
                        (1ULL << PIN_LCD_RST),
        .mode         = GPIO_MODE_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    gpio_config(&io);
    gpio_set_level(PIN_LCD_SPI_CS,   1);
    gpio_set_level(PIN_LCD_SPI_SCK,  1);
    gpio_set_level(PIN_LCD_SPI_MOSI, 0);
    gpio_set_level(PIN_LCD_RST,      1);
}

static void lcd_hardware_reset(void)
{
    ESP_LOGI(TAG, "Hardware reset");
    gpio_set_level(PIN_LCD_RST, 1); vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(PIN_LCD_RST, 0); vTaskDelay(pdMS_TO_TICKS(15));
    gpio_set_level(PIN_LCD_RST, 1); vTaskDelay(pdMS_TO_TICKS(150));
}

static void lcd_send_init_sequence(void)
{
    size_t n = sizeof(nv3052c_init_regs) / sizeof(nv3052c_init_regs[0]);
    ESP_LOGI(TAG, "Sending %d init registers", (int)n);
    for (size_t i = 0; i < n; i++) {
        lcd_reg(nv3052c_init_regs[i].reg, nv3052c_init_regs[i].val);
    }
    lcd_cmd(0x11);                      // Sleep Out
    vTaskDelay(pdMS_TO_TICKS(200));
    lcd_cmd(0x29);                      // Display On
    vTaskDelay(pdMS_TO_TICKS(50));
    ESP_LOGI(TAG, "Init sequence done");
}

static esp_err_t lcd_create_rgb_panel(void)
{
    ESP_LOGI(TAG, "Creating RGB panel %dx%d @ %d Hz (bounce buffer, no PSRAM needed)",
             LCD_H_RES, LCD_V_RES, LCD_PIXEL_CLOCK_HZ);

    esp_lcd_rgb_panel_config_t cfg = {
        .clk_src    = LCD_CLK_SRC_DEFAULT,
        .timings = {
            .pclk_hz            = LCD_PIXEL_CLOCK_HZ,
            .h_res              = LCD_H_RES,
            .v_res              = LCD_V_RES,
            .hsync_back_porch   = LCD_HSYNC_BACK_PORCH,
            .hsync_front_porch  = LCD_HSYNC_FRONT_PORCH,
            .hsync_pulse_width  = LCD_HSYNC_PULSE_WIDTH,
            .vsync_back_porch   = LCD_VSYNC_BACK_PORCH,
            .vsync_front_porch  = LCD_VSYNC_FRONT_PORCH,
            .vsync_pulse_width  = LCD_VSYNC_PULSE_WIDTH,
            .flags.pclk_active_neg = true,
        },
        .data_width         = 16,
        .num_fbs            = 0,                    // No frame buffer
        .bounce_buffer_size_px = LCD_H_RES * 10,   // ~14 KB in internal SRAM
        .hsync_gpio_num     = PIN_LCD_HSYNC,
        .vsync_gpio_num     = PIN_LCD_VSYNC,
        .de_gpio_num        = PIN_LCD_DE,
        .pclk_gpio_num      = PIN_LCD_PCLK,
        .disp_gpio_num      = -1,
        .data_gpio_nums = {
            PIN_LCD_DATA0,  PIN_LCD_DATA1,  PIN_LCD_DATA2,  PIN_LCD_DATA3,
            PIN_LCD_DATA4,  PIN_LCD_DATA5,  PIN_LCD_DATA6,  PIN_LCD_DATA7,
            PIN_LCD_DATA8,  PIN_LCD_DATA9,  PIN_LCD_DATA10, PIN_LCD_DATA11,
            PIN_LCD_DATA12, PIN_LCD_DATA13, PIN_LCD_DATA14, PIN_LCD_DATA15,
        },
        .flags.fb_in_psram = false,
    };

    esp_lcd_panel_handle_t panel = NULL;
    ESP_RETURN_ON_ERROR(esp_lcd_new_rgb_panel(&cfg, &panel),
                        TAG, "Failed to create RGB panel");

    // Register bounce-buffer fill callback
    esp_lcd_rgb_panel_event_callbacks_t cbs = {
        .on_bounce_empty = lcd_bounce_fill_cb,
    };
    ESP_RETURN_ON_ERROR(esp_lcd_rgb_panel_register_event_callbacks(panel, &cbs, NULL),
                        TAG, "Failed to register callbacks");

    ESP_RETURN_ON_ERROR(esp_lcd_panel_reset(panel), TAG, "Panel reset failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_init(panel),  TAG, "Panel init failed");

    ESP_LOGI(TAG, "RGB panel running");
    return ESP_OK;
}

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------

esp_err_t nv3052c_init(void)
{
    spi_gpio_init();
    lcd_hardware_reset();
    lcd_send_init_sequence();
    return lcd_create_rgb_panel();
}

void nv3052c_set_color(uint16_t color_rgb565)
{
    s_fill_color = color_rgb565;
    s_pattern    = LCD_PATTERN_SOLID;
}

void nv3052c_set_pattern(lcd_test_pattern_t pattern)
{
    s_pattern = pattern;
}