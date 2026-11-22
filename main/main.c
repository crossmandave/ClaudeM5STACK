#include <stdio.h>
#include "esp_log.h"
#include "esp_heap_caps.h"
#include "bsp/esp-bsp.h"
#include "lvgl.h"

static const char *TAG = "main";

static lv_obj_t *count_label;
static int press_count;

static void button_event_cb(lv_event_t *e)
{
    press_count++;
    lv_label_set_text_fmt(count_label, "Pressed %d times", press_count);
    ESP_LOGI(TAG, "Button pressed (%d)", press_count);
}

static void build_ui(void)
{
    lv_obj_t *scr = lv_screen_active();

    lv_obj_t *title = lv_label_create(scr);
    lv_label_set_text(title, "ClaudeM5STACK");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    lv_obj_t *btn = lv_button_create(scr);
    lv_obj_set_size(btn, 160, 60);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(btn, button_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Tap me");
    lv_obj_center(btn_label);

    count_label = lv_label_create(scr);
    lv_label_set_text(count_label, "Pressed 0 times");
    lv_obj_align(count_label, LV_ALIGN_BOTTOM_MID, 0, -20);
}

void app_main(void)
{
    ESP_LOGI(TAG, "PSRAM free: %u bytes",
             (unsigned)heap_caps_get_free_size(MALLOC_CAP_SPIRAM));

    lv_display_t *disp = bsp_display_start();
    if (disp == NULL) {
        ESP_LOGE(TAG, "Display init failed");
        return;
    }
    bsp_display_backlight_on();

    bsp_display_lock(0);
    build_ui();
    bsp_display_unlock();
}
