/* ============================================================================
 * F100 Gauge Cluster - Display Test
 * ST77916 1.5" Round Display (360x360) + LVGL
 * Using Modified TFT_eSPI Library for ST77916
 * ============================================================================
 */

#include <TFT_eSPI.h>
#include <lvgl.h>

// ============================================================================
// DISPLAY CONFIGURATION
// ============================================================================

#define TFT_BL    4

TFT_eSPI tft = TFT_eSPI();

// ============================================================================
// LVGL CONFIGURATION
// ============================================================================

#define SCREEN_WIDTH  360
#define SCREEN_HEIGHT 360
#define BUFFER_SIZE (SCREEN_WIDTH * 40)

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[BUFFER_SIZE];
static lv_disp_drv_t disp_drv;

// LVGL display flush callback
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushPixels((uint16_t *)&color_p->full, w * h);
    tft.endWrite();
    
    lv_disp_flush_ready(disp);
}

// ============================================================================
// GAUGE UI
// ============================================================================

lv_obj_t *gauge_meter;
lv_meter_indicator_t *needle_rpm;
lv_obj_t *label_value;

void create_gauge() {
    // Create meter/gauge object
    gauge_meter = lv_meter_create(lv_scr_act());
    lv_obj_set_size(gauge_meter, 320, 320);
    lv_obj_center(gauge_meter);
    
    // Set dark background
    lv_obj_set_style_bg_color(gauge_meter, lv_color_hex(0x000000), 0);
    
    // Add scale (0-8000 RPM, 270° sweep)
    lv_meter_scale_t *scale = lv_meter_add_scale(gauge_meter);
    lv_meter_set_scale_ticks(gauge_meter, scale, 41, 2, 10, lv_color_white());
    lv_meter_set_scale_major_ticks(gauge_meter, scale, 8, 4, 15, lv_color_white(), 10);
    lv_meter_set_scale_range(gauge_meter, scale, 0, 8000, 270, 135);
    
    // Add red zone (6000-8000)
    lv_meter_indicator_t *red_arc = lv_meter_add_arc(gauge_meter, scale, 5, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(gauge_meter, red_arc, 6000);
    lv_meter_set_indicator_end_value(gauge_meter, red_arc, 8000);
    
    // Add needle
    needle_rpm = lv_meter_add_needle_line(gauge_meter, scale, 4, lv_palette_main(LV_PALETTE_RED), -10);
    
    // Add value label in center
    label_value = lv_label_create(gauge_meter);
    lv_label_set_text(label_value, "0");
    lv_obj_set_style_text_font(label_value, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(label_value, lv_color_white(), 0);
    lv_obj_align(label_value, LV_ALIGN_CENTER, 0, 40);
}

// ============================================================================
// SETUP
// ============================================================================

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n=== F100 Display Test - ST77916 ===");
    Serial.println("Initializing display...");
    
    // Initialize backlight
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    
    // Initialize display
    tft.begin();
    tft.setRotation(0);
    tft.setSwapBytes(true);  // CRITICAL for ST77916!
    
    Serial.println("Display initialized!");
    
    // Color test
    Serial.println("Black screen");
    tft.fillScreen(TFT_BLACK);
    delay(2000);
    
    Serial.println("White screen");
    tft.fillScreen(TFT_WHITE);
    delay(2000);
    
    Serial.println("Red screen");
    tft.fillScreen(TFT_RED);
    delay(2000);
    
    Serial.println("Green screen");
    tft.fillScreen(TFT_GREEN);
    delay(2000);
    
    Serial.println("Blue screen");
    tft.fillScreen(TFT_BLUE);
    delay(2000);
    
    tft.fillScreen(TFT_BLACK);
    delay(1000);
    
    // Initialize LVGL
    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, BUFFER_SIZE);
    
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);
    
    Serial.println("LVGL initialized!");
    
    // Create gauge
    create_gauge();
    
    Serial.println("Gauge created! Starting sweep test...");
}

// ============================================================================
// MAIN LOOP
// ============================================================================

void loop() {
    static float rpm = 0;
    static float direction = 50;
    
    // Sweep RPM up and down
    rpm += direction;
    
    if (rpm >= 8000) {
        rpm = 8000;
        direction = -50;
    } else if (rpm <= 0) {
        rpm = 0;
        direction = 50;
    }
    
    // Update needle
    lv_meter_set_indicator_value(gauge_meter, needle_rpm, (int)rpm);
    
    // Update text
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", (int)rpm);
    lv_label_set_text(label_value, buf);
    
    // Handle LVGL
    lv_timer_handler();
    
    delay(20);
}