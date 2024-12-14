#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Encoder.h"
#include "Delay.h "


int main(void)
{
	OLED_Init();
	Encoder_Init();
	OLED_ShowString(1,1,"CNT:");
	while(1)
	{
		OLED_ShowSignedNum(1,5,Encoder_Get()/4,5);
		Delay_ms(1000);

	}	
	
}


