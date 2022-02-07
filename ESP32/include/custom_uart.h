#ifndef _CUSTOM_UART_H_
#define _CUSTOM_UART_H_

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define PATTERN_CHR_NUM         3        
#define BUF_SIZE                1024
#define RD_BUF_SIZE             BUF_SIZE

QueueHandle_t uart_queue_handle;         /* UART Queue Handle */
uart_port_t uart_port;                   /* UART Port */  

/* UARTx Init */
void uart_config(uart_port_t uart_num,int uart_tx_pin,int uart_rx_pin);

#endif