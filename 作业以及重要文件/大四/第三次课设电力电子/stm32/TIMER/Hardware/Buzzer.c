#include "stm32f10x.h"                  // Device header


void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}

void Buzzer_OFF(void)
{
 GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

