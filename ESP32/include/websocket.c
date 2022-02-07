#include "websocket.h"

static const char *TAG = "WEB SOCKET";

void http_massage(const char *api_key,const char *web_server,char *buff,float temp,float humid,uint16_t ppm)
{
    char message[256];

    sprintf(message,"api_key=%s&field1=%.1f&field2=%.1f&field3=%d",api_key,temp,humid,ppm);
    sprintf(buff,"POST /update HTTP/1.1\r\n"
                "Host: %s\r\n"
                "Connection: close\r\n"
                "Content-Type: application/x-www-form-urlencoded\r\n"
                "Content-Length:%d\r\n\r\n%s\n",web_server,strlen(message),message);
}

uint8_t http_send_request(const char *web_server,const char *web_port,char *request)
{
    char recv_buf[64];
    const struct addrinfo hints = 
    {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    struct addrinfo *res;
    int s,r;

    /* Get DNS address */
    int err = getaddrinfo(web_server,web_port,&hints,&res);

    if(err != 0 || res == NULL) 
    {
        ESP_LOGE(TAG,"DNS lookup failed err=%d res=%p",err,res);
        return 0;
    }
    else
        ESP_LOGI(TAG,"DNS lookup succeed");

    /* Allocate socket */
    s = socket(res->ai_family,res->ai_socktype,0);
    if(s < 0) 
    {
        ESP_LOGE(TAG,"socket allocated fail");
        freeaddrinfo(res);
        return 0;
    }
    else
        ESP_LOGI(TAG,"socket allocated done");

    /* Connect socket */
    if(connect(s,res->ai_addr,res->ai_addrlen) != 0)
    {
        ESP_LOGE(TAG,"socket connect fail");
        close(s);
        freeaddrinfo(res);
        return 0;
    }
    else
    {
        ESP_LOGI(TAG,"socket connected");
        freeaddrinfo(res);
    }

    /* Send HTTP Message */ 
    if (write(s,request,strlen(request)) < 0) 
    {
        ESP_LOGE(TAG,"socket send message failed");
        close(s);
        return 0;
    }
    else
        ESP_LOGI(TAG,"socket send message done");

    struct timeval receiving_timeout;
    receiving_timeout.tv_sec = 5;
    receiving_timeout.tv_usec = 0;
    if (setsockopt(s,SOL_SOCKET, SO_RCVTIMEO,&receiving_timeout,sizeof(receiving_timeout)) < 0) 
    {
        ESP_LOGE(TAG,"failed to set socket receiving timeout");
        close(s);
        return 0;
    }
    else
        ESP_LOGI(TAG,"set socket receiving timeout success");

    /* Read HTTP response */
    do 
    {
        bzero(recv_buf,sizeof(recv_buf));
        r = read(s,recv_buf,sizeof(recv_buf)-1);
        for(int i=0;i<r;i++) 
        {
            putchar(recv_buf[i]);
        }
    }while(r>0);
    close(s);
    return 1;
}