#include "dht.h"

static DHT_TypeDef DHT_Type;
static GPIO_TypeDef *DHT_GPIO;			//DHT Port
static uint16_t DHT_Pin;			//DHT Pin
static TIM_HandleTypeDef ustim;			//Timer for us delay

static void __DELAY_US(uint16_t us)
{
  __HAL_TIM_SET_COUNTER(&ustim,0);
  __HAL_TIM_SET_AUTORELOAD(&ustim,65535);
  HAL_TIM_Base_Start(&ustim);
  while(__HAL_TIM_GetCounter(&ustim)<us);
  HAL_TIM_Base_Stop(&ustim);
}

void DHT_Init(DHT_TypeDef Type,GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin,TIM_HandleTypeDef htim)
{
  DHT_Type = Type;
  DHT_GPIO = GPIOx;
  DHT_Pin = GPIO_Pin;
  ustim = htim;
}

static void DHT_SetDirection(DHT_GPIO_DIRECTION dir)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(dir == Input)
  {
    GPIO_InitStruct.Pin = DHT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(DHT_GPIO,&GPIO_InitStruct);
  }
  else if(dir == Output)
  {
    GPIO_InitStruct.Pin = DHT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DHT_GPIO,&GPIO_InitStruct);
  }
}

void DHT_SendRequest(void)
{
  DHT_SetDirection(Output);
  HAL_GPIO_WritePin(DHT_GPIO,DHT_Pin,GPIO_PIN_RESET);
  if(DHT_Type == DHT11)
    HAL_Delay(20);
  if(DHT_Type == DHT22)
    HAL_Delay(1);
  HAL_GPIO_WritePin(DHT_GPIO,DHT_Pin,GPIO_PIN_SET);
  __DELAY_US(30);
}

void DHT_WaitResponse(void)
{
  DHT_SetDirection(Input);
  while(!(HAL_GPIO_ReadPin(DHT_GPIO,DHT_Pin)));
  while(HAL_GPIO_ReadPin(DHT_GPIO,DHT_Pin));
}

static uint8_t DHT_ReadByte(void)
{
  uint8_t value = 0;
  for(int i=0;i<8;i++)
  {
    while(!(HAL_GPIO_ReadPin(DHT_GPIO,DHT_Pin)));
    __DELAY_US(30);
    if(HAL_GPIO_ReadPin(DHT_GPIO,DHT_Pin))
      value = (value<<1)|0x01;
    else
      value = value<<1;
    while(HAL_GPIO_ReadPin(DHT_GPIO,DHT_Pin));
  }
  return value;
}
	
void DHT_ReadData(DHT_Value *value)
{
  uint8_t data[5];
	
  DHT_SendRequest();
  DHT_WaitResponse();
	
  if(DHT_Type == DHT22)
  {
    uint8_t check_sum;
		
    for(int i=0;i<5;i++)
    {
      data[i] = DHT_ReadByte();
    }

    check_sum = data[0]+data[1]+data[2]+data[3];

    if(data[4] == check_sum)
    {
      value->check = true;
      if (data[2]>127)
        value->temp = (float)data[3]/10*(-1);
      else
        value->temp = (float)((data[2]<<8)|data[3])/10;
      value->humid = (float) ((data[0]<<8)|data[1])/10;
    }
    else
      *value = (DHT_Value){0,0,false};
  }

  else if(DHT_Type == DHT11)
  {
    uint8_t check_sum;
		
    for(int i=0;i<5;i++)
    {
      data[i] = DHT_ReadByte();
    }
		
    check_sum = data[0]+data[1]+data[2]+data[3];
		
    if(data[4] == check_sum)
    {
      value->humid = data[0];value->temp = data[2];
      for(int i=0;i<8;i++)
      {
        value->temp += ((data[3]>>(7-i))&0x01) * (float)pow(10,-(i+1));
        value->humid +=  ((data[1]>>(7-i))&0x01) * (float)pow(10,-(i+1));
      }
      value->check = true;
    }
    else
      *value = (DHT_Value){0,0,false};
  }
}
