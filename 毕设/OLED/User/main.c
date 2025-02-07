#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "OLED.h"
#include "Timer.h"
#include "Delay.h"
#include "Rtc_Clock.h"
#include "Key.h"


int main(void)
{
	OLED_Init();
	MyRTC_Init();
	Key_Init();
	
	OLED_ShowString(1,1,"Date:XXXX-XX-XX");
	OLED_ShowString(2,1,"Time:XX:XX:XX");
	OLED_ShowString(3,1,"Cnt :");
	OLED_ShowString(4,1,"Div :");
	
	while(1)
	{
		Switch_Change_Mode();
		Key_GetNum();
		MyRTC_ReadTime();
		OLED_ShowNum(1,6,MyRTC_Time[0], 4);
		OLED_ShowNum(1,11,MyRTC_Time[1], 2);
		OLED_ShowNum(1,14,MyRTC_Time[2], 2);
		OLED_ShowNum(2,6,MyRTC_Time[3], 2);
		OLED_ShowNum(2,9,MyRTC_Time[4], 2);
		OLED_ShowNum(2,12,MyRTC_Time[5], 2);
		
		OLED_ShowNum(3,6,RTC_GetCounter(),10);
		OLED_ShowNum(4,6,(32767 - RTC_GetDivider()) / 32767.0 * 999,10);
	}	
	
}


