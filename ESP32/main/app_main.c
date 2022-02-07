#include "custom_uart.h"
#include "websocket.h"
#include "wifi_station.h"

/* Define config for UART */
#define UART_TX_PIN         GPIO_NUM_12
#define UART_RX_PIN         GPIO_NUM_14

/* Define config for server connection */
#define WEB_SERVER      "api.thingspeak.com"
#define WEB_PORT        "80"
#define API_KEY         "XGX28I7CSZHXUCIS"

const char *TAG = "uart_events";         /* UART LOG */

// UART Data Event Handle Function
static void uart_data_event_handle(uint8_t *dtmp)
{
    char *temp;
    char *humid;
    char *ppm;
    char *request = (char*)malloc(512*sizeof(char));

    temp = strtok((char*)dtmp,"-");
    humid = strtok(NULL,"-");
    ppm = strtok(NULL,"-");

    printf("\nSend data: Temp: %s Humid: %s PPM: %s",temp,humid,ppm);
    http_massage(API_KEY,WEB_SERVER,request,atof(temp),atof(humid),atoi(ppm));
    http_send_request(WEB_SERVER,WEB_PORT,request);
    free(request);
}

// UART Event Handle 
static void uart_event_handle()
{
    uart_event_t event;
    size_t buffered_size;
    uint8_t* dtmp = (uint8_t*)malloc(RD_BUF_SIZE);
    while(1)
    {
        //Waiting for UART event.
        if(xQueueReceive(uart_queue_handle,(void*)&event,(portTickType)portMAX_DELAY)) {
            bzero(dtmp,RD_BUF_SIZE);
            switch(event.type) 
            {
                case UART_DATA:
                    uart_read_bytes(uart_port,dtmp,event.size,portMAX_DELAY);
                    uart_data_event_handle(dtmp);
                    break;
                case UART_FIFO_OVF:
                    uart_flush_input(UART_NUM_1);
                    xQueueReset(uart_queue_handle);
                    break;
                case UART_BUFFER_FULL:
                    uart_flush_input(UART_NUM_1);
                    xQueueReset(uart_queue_handle);
                    break;
                case UART_PATTERN_DET:
                    uart_get_buffered_data_len(uart_port, &buffered_size);
                    int pos = uart_pattern_pop_pos(uart_port);
                    if (pos == -1)
                        uart_flush_input(uart_port);
                    else 
                    {
                        uart_read_bytes(uart_port,dtmp,pos,100/portTICK_PERIOD_MS);
                        uint8_t pat[PATTERN_CHR_NUM + 1];
                        memset(pat,0,sizeof(pat));
                        uart_read_bytes(uart_port,pat,PATTERN_CHR_NUM,100/portTICK_PERIOD_MS);
                    }
                    break;
                default:
                    ESP_LOGI(TAG,"uart event type: %d",event.type);
                    break;
            }
            vTaskDelay(1000/portTICK_PERIOD_MS);
        }
    }
    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
}

void app_main(void)
{
    //UART Init 
    uart_config(UART_NUM_1,UART_TX_PIN,UART_RX_PIN);

    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    //WIFI Station Init 
    wifi_station_init();

    //Create a task to handler UART event from ISR
    xTaskCreate(uart_event_handle,"uart_event_task",2048,NULL,12,NULL);
}