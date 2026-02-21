#include <stdio.h>
#include "esp_now.h"

const uint8_t PEER_MAC_ADDRESS = 30 : C9 : 22 : 32 : CF : F4;
bool peer_connected = false;

void initialize(void)
{
    esp_now_init();
    esp_now_register_recv_cb(receive_data);
    esp_now_register_send_cb(send_data);
    esp_now_add_peer(PEER_MAC_ADDRESS);
}

void receive_data(void)
{
}

void send_data(void)
{
    esp_err_t result = esp_now_send("", 8, 8);
}

void app_main(void)
{
}

void reconnect_to_peer(void)
{
}
