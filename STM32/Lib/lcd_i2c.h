#ifndef _LCD_I2C_H_
#define _LCD_I2C_H_

#include "main.h"
#include <stdio.h>

#define CLEAR_DISPLAY		0x01
#define RETURN_HOME		0x02

typedef struct
{
  I2C_HandleTypeDef* I2C;
  uint8_t ADDRESS;
}LCD_HandleTypeDef;

void LCD_I2C_Init(LCD_HandleTypeDef *LCD);
void LCD_I2C_Send_Cmd(uint8_t cmd);
void LCD_I2C_Send_Char(char data);
void LCD_I2C_Send_String(char *str);
void LCD_I2C_Set_Cursor(uint8_t position);

#endif
