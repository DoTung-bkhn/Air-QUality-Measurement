set (pri_req nvs_flash)
idf_component_register(SRCS "custom_uart.c" "websocket.c" "wifi_station.c"
                    INCLUDE_DIRS "."
                    REQUIRES ${pri_req})
