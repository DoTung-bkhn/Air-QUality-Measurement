#ifndef _DHT_H_
#define _DHT_H_

#include "main.h"
#include <stdbool.h>
#include <math.h>

#pragma pack(1)
typedef struct
{
  float temp;
  float humid;
  bool check;
}DHT_Value;
#pragma pack()

typedef enum
{
  Input,
  Output
}DHT_GPIO_DIRECTION;

typedef enum
{
  DHT11,
  DHT22
}DHT_TypeDef;

void DHT_Init(DHT_TypeDef Type,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,TIM_HandleTypeDef timer_handle);
void DHT_ReadData(DHT_Value *value);

#endif
