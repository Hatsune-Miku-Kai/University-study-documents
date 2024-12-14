#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "LED.h"
#include "Key.h"



int main(void)
{
	LED_Init();
	Key_Init();
	uint8_t KeyNum=0;
	
	while(1)
	{
	  KeyNum=Key_GetNum();
	  if(KeyNum==1)
		  LED1_Turn();
	}	
	
}
