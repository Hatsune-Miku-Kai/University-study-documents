#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"
#include "Encoder.h"

int16_t Num=0;

int main(void)
{
	
	OLED_Init();
	Encoder_Init();
	
	OLED_ShowString(1,1,"Count:");
	//OLED_Clear();
	while(1)
	{
		Num+=Encoder_Get();
		OLED_ShowSignedNum(1,7,Num,5);
	
	}	
	
}
