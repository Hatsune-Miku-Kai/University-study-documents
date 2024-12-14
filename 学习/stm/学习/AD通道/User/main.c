#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "OLED.h"
#include "Timer.h"
#include "Delay.h"
#include "AD.h"

uint16_t Value;
float Voltage;
int main(void)
{
	OLED_Init();
	AD_Init();
	
	OLED_ShowString(1,1,"Value:");
	OLED_ShowString(2,1,"Voltage:0.00V");
	while(1)
	{
		Value=AD_GetValue();
		OLED_ShowNum(1,9,Value,4); 
		Voltage=(float)Value/4095*3.3;
		OLED_ShowNum(2,9,Voltage,1);
		OLED_ShowNum(2,11,(uint16_t)(Voltage*100)%100,2);
	}	
	
}


