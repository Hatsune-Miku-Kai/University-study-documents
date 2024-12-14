#include "stm32f10x.h"                  // Device header
#include "Servo.h"
#include "OLED.h"
#include "Timer.h"
#include "Delay.h"
#include "Key.h"

uint8_t KeyNum;
float Angle;
int main(void)
{
	OLED_Init();
	Key_Init();
	Servo_Init();
	OLED_Init();
	
	//OLED_Clear();
	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum==1)
			Angle+=90;
			if(Angle>180)
				Angle=0;
		Servo_SetAngle(Angle);
		OLED_ShowString(1,1,"Angle:");
		OLED_ShowNum(1,7,Angle,3);
	}	
	
}


