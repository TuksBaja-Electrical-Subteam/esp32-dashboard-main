#include "nvs_flash.h"
#include "wifi_manager.h"
#include "speed_calculator.h"
#include "web_server.h"

#define HALL_SENSOR_GPIO 18
#define WHEEL_CIRCUMFERENCE 1.72

void app_main(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    speed_calc_init(HALL_SENSOR_GPIO, WHEEL_CIRCUMFERENCE);
    wifi_init_softap();
    start_webserver();
}