#include "mq135.h"

static float GET_Corrected_Factor(float temp,float humid)
{
  return CORRA*pow(temp,2) + CORRB*temp + CORRC + CORRD*humid;
}

void MQ135_Read(ADC_HandleTypeDef *hadc,float temp,float humid,uint16_t *ppm)
{
  float Vout,RS,corrected_factor;
  uint16_t adc_value;
	
  //Get corrected factor
  corrected_factor = GET_Corrected_Factor(temp,humid);
	
  //Start reading ADC value
  HAL_ADCEx_Calibration_Start(hadc);
  HAL_ADC_Start(hadc);
  HAL_ADC_PollForConversion(hadc,1000);
  adc_value = HAL_ADC_GetValue(hadc);
	
  //Calculate ppm value
  Vout = (3.3*adc_value)/4095;
  RS = ((5-Vout)*RL)/Vout;
  *ppm = (uint16_t)(PARAA*pow((RS/(corrected_factor*RZERO)),PARAB));
}
