#ifndef _MQ135_H_
#define _MQ135_H_

#include "stm32f1xx_hal.h"
#include <math.h>

#define PARAA   105.6405
#define PARAB   -2.8604
#define RZERO   9446.1078
#define RL      1000

#define CORRA		0.0004
#define CORRB		-0.0259
#define CORRC		1.4664
#define CORRD		-0.0025

void MQ135_Read(ADC_HandleTypeDef *hadc,float temp,float humid,uint16_t *ppm);

#endif

