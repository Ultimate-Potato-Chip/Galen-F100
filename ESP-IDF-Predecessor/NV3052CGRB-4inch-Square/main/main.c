#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nv3052c.h"

static const char *TAG = "main";

// RGB565 color macros
#define COLOR_RED       0xF800
#define COLOR_GREEN     0x07E0
#define COLOR_BLUE      0x001F
#define COLOR_WHITE     0xFFFF
#define COLOR_BLACK     0x0000
#define COLOR_YELLOW    0xFFE0
#define COLOR_CYAN      0x07FF
#define COLOR_MAGENTA   0xF81F

void app_main(void)
{
    ESP_LOGI(TAG, "========================================");
    ESP_LOGI(TAG, "NV3052C 720x720 LCD Color Test");
    ESP_LOGI(TAG, "========================================");

    esp_err_t ret = nv3052c_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "LCD init failed: %s", esp_err_to_name(ret));
        return;
    }

    ESP_LOGI(TAG, "LCD running. Starting color cycle.");

    int step = 0;
    while (1) {
        switch (step) {
            case 0:
                ESP_LOGI(TAG, "RED");
                nv3052c_set_color(COLOR_RED);
                break;
            case 1:
                ESP_LOGI(TAG, "GREEN");
                nv3052c_set_color(COLOR_GREEN);
                break;
            case 2:
                ESP_LOGI(TAG, "BLUE");
                nv3052c_set_color(COLOR_BLUE);
                break;
            case 3:
                ESP_LOGI(TAG, "WHITE");
                nv3052c_set_color(COLOR_WHITE);
                break;
            case 4:
                ESP_LOGI(TAG, "BLACK");
                nv3052c_set_color(COLOR_BLACK);
                break;
            case 5:
                ESP_LOGI(TAG, "COLOR BARS");
                nv3052c_set_pattern(LCD_PATTERN_BARS);
                break;
            case 6:
                ESP_LOGI(TAG, "RGB GRADIENT");
                nv3052c_set_pattern(LCD_PATTERN_GRADIENT);
                break;
        }
        step = (step + 1) % 7;
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}