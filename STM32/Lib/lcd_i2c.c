#include "lcd_i2c.h"

LCD_HandleTypeDef *LCD;

void LCD_I2C_Send_Cmd(uint8_t cmd)
{
  uint8_t data_h;
  uint8_t data_l;
  uint8_t data[4];
	
  data_h = cmd&0xF0;
  data_l = (cmd<<4)&0xF0;
	
  data[0] = data_h|0x0C;  
  HAL_Delay(1);
  data[1] = data_h|0x08;  
  data[2] = data_l|0x0C; 
  HAL_Delay(1);
  data[3] = data_l|0x08; 
  HAL_I2C_Master_Transmit(LCD->I2C,LCD->ADDRESS,(uint8_t*)data,4,100);
}

void LCD_I2C_Init(LCD_HandleTypeDef *hlcd)
{
  LCD = hlcd;
	
  HAL_Delay(50);
  LCD_I2C_Send_Cmd(0x33);
  HAL_Delay(5);
  LCD_I2C_Send_Cmd(0x32);
  HAL_Delay(5);
  LCD_I2C_Send_Cmd(0x20);
  HAL_Delay(5);
  LCD_I2C_Send_Cmd(0x06);
  LCD_I2C_Send_Cmd(0x0C);
  LCD_I2C_Send_Cmd(0x14);
  LCD_I2C_Send_Cmd(0x28);	
  LCD_I2C_Send_Cmd(CLEAR_DISPLAY);
  LCD_I2C_Send_Cmd(RETURN_HOME);
}

void LCD_I2C_Send_Char(char data)
{
  char data_h,data_l;
  uint8_t data_t[4];
  data_h = data&0xF0;
  data_l = (data<<4)&0xF0;
	
  data_t[0] = data_h|0x0D;
  data_t[1] = data_h|0x09;  
  data_t[2] = data_l|0x0D;
  data_t[3] = data_l|0x09;  
  HAL_I2C_Master_Transmit(LCD->I2C,LCD->ADDRESS,(uint8_t*)data_t,4,100);
}

void LCD_I2C_Send_String(char *str)
{
  while(*str)
  {
    LCD_I2C_Send_Char(*str++);
  }
}

void LCD_I2C_Set_Cursor(uint8_t position)
{
  uint8_t cmd;
	
  if(position >= 16)
    position = 0x40 + position - 16;
  cmd = position|0x80;
  LCD_I2C_Send_Cmd(cmd);
}
