

// Version Info
// ESP32                v2.0.14
// LVGL                 v9.0.0
// TFT_eSPI             v2.5.34
// FT6236(Dustin Watts) v1.0.2

#include <lvgl.h>
#include <TFT_eSPI.h>
#include <demos/lv_demos.h>


#define TFT_HOR_RES 480
#define TFT_VER_RES 320

unsigned long lastTickMillis = 0;

TFT_eSPI tft = TFT_eSPI(TFT_HOR_RES, TFT_VER_RES); /* TFT instance */

void my_flush_cb(lv_display_t *display, const lv_area_t *area, lv_color_t *color_p) {

  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->red, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(display);
}
static uint16_t buf[TFT_HOR_RES * TFT_VER_RES / 10];

void setup() {

  lv_display_t *disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);

  lv_display_set_flush_cb(disp, my_flush_cb);

  lv_display_set_buffers(disp, buf, NULL, sizeof(buf), LV_DISP_RENDER_MODE_PARTIAL);

  Serial.begin(9600);

  lv_init();

  String LVGL_Arduino = "Hello Arduino!\n";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.println(LVGL_Arduino);

  lv_demo_benchmark();

  // lv_demo_widgets();
}

void loop() {
  // LVGL Tick Interface
  unsigned int tickPeriod = millis() - lastTickMillis;
  lv_tick_inc(tickPeriod);
  lastTickMillis = millis();

  // LVGL Task Handler
  lv_task_handler();
}