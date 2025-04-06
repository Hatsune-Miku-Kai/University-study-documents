#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "OLED.h"
#include "Timer.h"
#include "Delay.h"
#include "Rtc_Clock.h"
#include "Key.h"
#include "Stepper_motors.h"
#include "TIM.h"

/*
//                            _ooOoo_  
//                           o8888888o  
//                           88" . "88  
//                           (| -_- |)  
//                            O\ = /O  
//                        ____/`---'\____  
//                      .   ' \\| |// `.  
//                       / \\||| : |||// \  
//                     / _||||| -:- |||||- \  
//                       | | \\\ - /// | |  
//                     | \_| ''\---/'' | |  
//                      \ .-\__ `-` ___/-. /  
//                   ___`. .' /--.--\ `. . __  
//                ."" '< `.___\_<|>_/___.' >'"".  
//               | | : `- \`.;`\ _ /`;.`/ - ` : | |  
//                 \ \ `-. \_ __\ /__ _/ .-` / /  
//         ======`-.____`-.___\_____/___.-`____.-'======  
//                            `=---='  
//  
//         .............................................  
//                  ¦ò¯ª«O¦ö             ¥ÃwuBUG 
*/

volatile int8_t step = 0;

int main(void)
{
	OLED_Init();
	MyRTC_Init();
	TIM2_Init();
	Motor_Init(); 
	Key_Init();

	
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
			OLED_ShowString(3,6,"MUSIC      ");
			while(1)//To ensure the step motor 100% Take control the core
			{
					Switch_Change_Mode();
					MyRTC_ReadTime();
					Key_GetNum();//get key status to break the loop

					OLED_ShowNum(1,6,MyRTC_Time[0], 4);
					OLED_ShowNum(1,11,MyRTC_Time[1], 2);
					OLED_ShowNum(1,14,MyRTC_Time[2], 2);
					OLED_ShowNum(2,6,MyRTC_Time[3], 2);
					OLED_ShowNum(2,9,MyRTC_Time[4], 2);
					OLED_ShowNum(2,12,MyRTC_Time[5], 2);
					OLED_ShowNum(4,6,(32767 - RTC_GetDivider()) / 32767.0 * 999,10);
					
					StepMotor_Run_Music(step);
					StepMotor_Run_Mode(step);
					step = (step + 1) % 4;  
					//Delay_ms(50);
				if(SetMode != MUSIC)
					break;
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

void TIM2_IRQHandler(void) 
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
		{
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        StepMotor_Run_Music(step);        // update motor 
        step = step % 4; 
		step++;
		}
}
