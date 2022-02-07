#ifndef _WEBSOCKET_H_
#define _WEBSOCKET_H_

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

//Create HTTP request message
void http_massage(const char *api_key,const char *web_server,char *buff,float temp,float humid,uint16_t ppm);

//Send HTTP request via web socket
uint8_t http_send_request(const char *web_server,const char *web_port,char *request);

#endif