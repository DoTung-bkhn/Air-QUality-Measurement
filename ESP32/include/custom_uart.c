#include "custom_uart.h"             

void uart_config(uart_port_t uart_num_x,int uart_tx_pin,int uart_rx_pin)
{
    /* Config UART */
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    uart_port = uart_num_x;
    uart_driver_install(uart_num_x,BUF_SIZE*2,BUF_SIZE*2,20,&uart_queue_handle,0);
    uart_param_config(uart_num_x,&uart_config);
    uart_set_pin(uart_num_x,uart_tx_pin,uart_rx_pin,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE);
}

