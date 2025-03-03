#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "OLED.h"
#include "Timer.h"
#include "Delay.h"
#include "Rtc_Clock.h"
#include "Key.h"
#include "Stepper_motors.h"



int8_t step = 1;

int main(void)
{
	OLED_Init();
	MyRTC_Init();
	Key_Init();
	Motor_Init();
	Buzzer_Init();
	
	OLED_ShowString(1,1,"Date:XXXX-XX-XX");
	OLED_ShowString(2,1,"Time:XX:XX:XX");
	OLED_ShowString(3,1,"Mode:");
	OLED_ShowString(4,1,"Div :");
	
while(1)
{
		MyRTC_ReadTime();
		Switch_Change_Mode();
		Key_GetNum();
		Reduce_Num(SetMode , Reduce_Mode);
		Alarm_Clock();
		Alarm_Ring();

	if((SetMode != ALARM_DATE) && (SetMode != ALARM_TIME))
	{
		OLED_ShowNum(1,6,MyRTC_Time[0], 4);
		OLED_ShowNum(1,11,MyRTC_Time[1], 2);
		OLED_ShowNum(1,14,MyRTC_Time[2], 2);
		OLED_ShowNum(2,6,MyRTC_Time[3], 2);
		OLED_ShowNum(2,9,MyRTC_Time[4], 2);
		OLED_ShowNum(2,12,MyRTC_Time[5], 2);
	}
		//OLED_ShowNum(3,7,RTC_GetCounter(),10);
		
		if(SetMode == 0)				OLED_ShowString(3,6,"NONE      ");
		if(SetMode == DATE)			OLED_ShowString(3,6,"DATE       ");
		if(SetMode == TIME)			OLED_ShowString(3,6,"TIME       ");
	
		if(SetMode == MUSIC)
		{
			while(1)//To ensure the step motor 100% Take control the core
			{
					Key_GetNum();//get key status to break the loop
					if((SetMode != ALARM_DATE) && (SetMode != ALARM_TIME))
					{
						OLED_ShowNum(1,6,MyRTC_Time[0], 4);
						OLED_ShowNum(1,11,MyRTC_Time[1], 2);
						OLED_ShowNum(1,14,MyRTC_Time[2], 2);
						OLED_ShowNum(2,6,MyRTC_Time[3], 2);
						OLED_ShowNum(2,9,MyRTC_Time[4], 2);
						OLED_ShowNum(2,12,MyRTC_Time[5], 2);
					}
						StepMotor_Run(step);
						step = (step + 1) % 4;  
						//Delay_ms(50);
						OLED_ShowString(3,6,"MUSIC      ");
			}
		}
		
		if(SetMode == ALARM_DATE) 
		{
			OLED_ShowString(3,6,"ALARM_DATE ");
			OLED_ShowNum(1,6,Alarm_Time[0], 4);
			OLED_ShowNum(1,11,Alarm_Time[1], 2);
			OLED_ShowNum(1,14,Alarm_Time[2], 2);
			OLED_ShowNum(2,6,Alarm_Time[3], 2);
			OLED_ShowNum(2,9,Alarm_Time[4], 2);
			OLED_ShowNum(2,12,Alarm_Time[5], 2);
		}
		
		
		if(SetMode == ALARM_TIME) 
		{
			OLED_ShowString(3,6,"ALARM_TIME ");
			OLED_ShowNum(1,6,Alarm_Time[0], 4);
			OLED_ShowNum(1,11,Alarm_Time[1], 2);
			OLED_ShowNum(1,14,Alarm_Time[2], 2);
			OLED_ShowNum(2,6,Alarm_Time[3], 2);
			OLED_ShowNum(2,9,Alarm_Time[4], 2);
			OLED_ShowNum(2,12,Alarm_Time[5], 2);
		}
		OLED_ShowNum(4,6,(32767 - RTC_GetDivider()) / 32767.0 * 999,10);
	}	
}

/*
			if(lock ==0)
			{
				OLED_ShowString(3,1,"ADate:XXXX-XX-XX");
				OLED_ShowString(4,1,"ATime:XX:XX:XX");
				lock =1;
			}
			OLED_ShowNum(3,7,Alarm_Time[YEAR],4);
			OLED_ShowNum(3,12,Alarm_Time[MON],2);
			OLED_ShowNum(3,15,Alarm_Time[DAY],2);
			OLED_ShowNum(4,7,Alarm_Time[HOUR],2);
			OLED_ShowNum(4,10,Alarm_Time[MIN],2);
			OLED_ShowNum(4,13,Alarm_Time[SEC],2);
*/
