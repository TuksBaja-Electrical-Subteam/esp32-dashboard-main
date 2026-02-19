#include "gps_handler.h"
#include "driver/uart.h"
#include "esp_log.h"

#define UART_NUM UART_NUM_1
#define BUF_SIZE 1024

static float _lat = 0.0, _lon = 0.0;

void gps_init(int tx_io, int rx_io) {
    uart_config_t uart_config = {
        .baud_rate = 9600, // NEO-6M default
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, tx_io, rx_io, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);

    // Simple task to read UART (In a real app, use a proper NMEA parser library)
    xTaskCreate([](void* p){
        uint8_t data[BUF_SIZE];
        while(1) {
            int len = uart_read_bytes(UART_NUM, data, BUF_SIZE - 1, 100 / portTICK_PERIOD_MS);
            if (len > 0) {
                data[len] = 0;
                // Basic check for coordinates - simplified for this example
                char* p_lat = strstr((char*)data, "$GPRMC"); 
                if(p_lat) { /* Parse logic would go here to update _lat and _lon */ }
            }
        }
    }, "gps_task", 4096, NULL, 5, NULL);
}

float get_gps_latitude(void) { return _lat; }
float get_gps_longitude(void) { return _lon; }