#include "stm32f10x.h"                  // Device header


void LED_clear(void)
{
	GPIO_SetBits(GPIOA,0X00);
}




