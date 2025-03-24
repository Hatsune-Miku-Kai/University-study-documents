#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Rtc_Clock.h"
#include "Key.h"
#include <time.h>


//Identify The Revise Mode
uint8_t SetMode = 0;

//Identify The reduce Num
uint8_t Reduce_Mode = 99;

//Alarm clock
int16_t Alarm_Time[]={0,0,0,0,0,0};
static uint8_t lock = 0;//This lock is for show the alarm time


/*
To reduce the num of all mode
*/
								//Setmode     mode to reduce
void Reduce_Num(uint8_t mode , uint8_t arg)
{
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1) 
	{
			Delay_ms(200);
			if((SetMode != ALARM_DATE) && (SetMode != ALARM_TIME))
			{
				switch(arg)
				{
					case MON:
					{
						MyRTC_Time[arg] --;
						if(MyRTC_Time[arg] == 0)
						{
							MyRTC_Time[arg] = 12;
						}
						MyRTC_SetTime();
					}break;
					
					case YEAR:
					{
						MyRTC_Time[arg] --;
						MyRTC_SetTime();
					}break;
					
					case DAY:
					{
						MyRTC_Time[arg] --;
						if(MyRTC_Time[arg] == 0)
						{
							MyRTC_Time[arg] = 31;
						}
						MyRTC_SetTime();
					}break;
					
					case MIN:
					{
						MyRTC_Time[arg] --;
						if(MyRTC_Time[arg] == -1)
						{
							MyRTC_Time[arg] = 59;
						}
						MyRTC_SetTime();
					}break;
					
					case HOUR:
					{
						MyRTC_Time[arg] --;
						if(MyRTC_Time[arg] == -1)
						{
							MyRTC_Time[arg] = 23;
						}
						MyRTC_SetTime();
					}break;
					
					case SEC:
					{
						MyRTC_Time[arg] --;
						if(MyRTC_Time[arg] == -1)
						{
							MyRTC_Time[arg] = 59;
						}
						MyRTC_SetTime();
					}break;
					
				}
			}
			
			if((SetMode == ALARM_DATE) || (SetMode == ALARM_TIME))
			{
				switch(arg)
				{
					case MON:
					{
						Alarm_Time[arg] --;
						if(Alarm_Time[arg] == 0)
						{
							Alarm_Time[arg] = 12;
						}
					}break;
					
					case YEAR:
					{
						Alarm_Time[arg] --;
					}break;
					
					case DAY:
					{
						Alarm_Time[arg] --;
						if(Alarm_Time[arg] == 0)
						{
							Alarm_Time[arg] = 31;
						}
					}break;
					
					case MIN:
					{
						Alarm_Time[arg] --;
						if(Alarm_Time[arg] == -1)
						{
							Alarm_Time[arg] = 59;
						}
					}break;
					
					case HOUR:
					{
						Alarm_Time[arg] --;
						if(Alarm_Time[arg] == -1)
						{
							Alarm_Time[arg] = 23;
						}
					}break;
					
					case SEC:
					{
						Alarm_Time[arg] --;
						if(Alarm_Time[arg] == -1)
						{
							Alarm_Time[arg] = 59;
						}
					}break;
					
				}
			}
	}

}

/*
///Init The GPIO Status
*/
void Key_Init(void)
{
	//GPIOB Key
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_8 | GPIO_Pin_9; //oled driver && buzzer driver pin
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//GPIOA Key
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //button driver pin
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15;//motor driver pin
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	//GPIOC Key
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

}


/*
///TO Get The Key Status And Change Date Or Time
*/
void Key_GetNum(void)
{
   //uint8_t KeyNum=0;
	if(SetMode == DATE)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==0)
		{
			Reduce_Mode = MON;
			//while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
			Delay_ms(200);
			MyRTC_ReadTime();
			MyRTC_Time[MON] ++;
			if(MyRTC_Time[MON] == 13)
			{
				MyRTC_Time[MON] = 1;
			}
			MyRTC_SetTime();
		}
		
		
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
		{
			Reduce_Mode = YEAR;
			//while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
			Delay_ms(200);
			MyRTC_ReadTime();
			MyRTC_Time[YEAR] ++;
			MyRTC_SetTime();
		}
		
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==0)
		{
			Reduce_Mode = DAY;
			//while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
			Delay_ms(200);
			MyRTC_ReadTime();
			MyRTC_Time[DAY] ++;
			if(MyRTC_Time[DAY] == 32)
			{
				MyRTC_Time[DAY] = 1;
			}
			MyRTC_SetTime();
		}
	}


	if(SetMode == TIME)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==0)
		{
			//while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
			Reduce_Mode = MIN;
			Delay_ms(200);
			MyRTC_ReadTime();
			MyRTC_Time[MIN] ++;
			if(MyRTC_Time[MIN] == 60)
			{
				MyRTC_Time[MIN] = 0;
			}
			MyRTC_SetTime();
		}
		
		
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
		{
			//while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
			Reduce_Mode = HOUR;
			Delay_ms(200);
			MyRTC_ReadTime();
			MyRTC_Time[HOUR] ++;
			if(MyRTC_Time[HOUR] == 24)
			{
				MyRTC_Time[HOUR] = 0;
			}
			MyRTC_SetTime();
		}
		
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==0)
		{
			//while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
			Reduce_Mode = SEC;
			Delay_ms(200);
			MyRTC_ReadTime();
			MyRTC_Time[SEC] ++;
			if(MyRTC_Time[SEC] == 60)
			{
				MyRTC_Time[SEC] = 0;
			}
			MyRTC_SetTime();
		}
	}

}





/*
To Set the Alarm Clock
*/
void Alarm_Clock(void)
{
		if(SetMode == ALARM_TIME)
		{
			
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==0)
			{
				Reduce_Mode = MIN;
				//while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
				Delay_ms(200);
				Alarm_Time[MIN] ++;
				if(Alarm_Time[MIN] == 60)
					Alarm_Time[MIN] = 0;
			}
			
			
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
			{
				Reduce_Mode = HOUR;
				//while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
				Delay_ms(200);
				Alarm_Time[HOUR] ++;
				if(Alarm_Time[HOUR] == 24)
					Alarm_Time[HOUR] = 0;
			}
			
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==0)
			{
				Reduce_Mode = SEC;
				//while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
				Delay_ms(200);
				Alarm_Time[SEC] ++;
				if(Alarm_Time[SEC] == 60)
					Alarm_Time[SEC] = 0;
			}
		}
		
		if(SetMode == ALARM_DATE)
		{
			if( !lock )
			{
				MyRTC_ReadTime();
				Alarm_Time[YEAR] = MyRTC_Time[YEAR];
				Alarm_Time[MON] = MyRTC_Time[MON];
				Alarm_Time[DAY] = MyRTC_Time[DAY];
				Alarm_Time[HOUR] = MyRTC_Time[HOUR];
				Alarm_Time[MIN] = MyRTC_Time[MIN];
				Alarm_Time[SEC] = 0;
				lock = 1;
			}
						
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==0)
			{
				Reduce_Mode = MON;
				//while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
				Delay_ms(200);
				Alarm_Time[MON] ++;
				if(Alarm_Time[MON] == 13)
					Alarm_Time[MON] = 1;
			}
			
			
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
			{
				Reduce_Mode = YEAR;
				//while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
				Delay_ms(200);
				Alarm_Time[YEAR] ++;
			}
			
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==0)
			{
				Reduce_Mode = DAY;
				//while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
				Delay_ms(200);
				Alarm_Time[DAY] ++;
				if(Alarm_Time[DAY] == 32)
					Alarm_Time[DAY] = 1;
			}
			
		}	
}



/*
///To Get The Switch Mode   DATE or TIME
*/
void Switch_Change_Mode(void)
{

	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0)
	{
		Delay_ms(200);
		//while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
		switch(SetMode)
		{
			case 0:
				{
					SetMode = DATE;
				}
					break;
			
			case DATE:
				{
					SetMode = TIME;
				}
					break;
				
			case TIME:
				{
					SetMode = ALARM_DATE;
				}
					break;
			
			case ALARM_DATE:
				{
					SetMode = ALARM_TIME;
				}
					break;	
				
			case ALARM_TIME:
				{
					lock = 0;
					SetMode = MUSIC;
				}
					break;
			
			case MUSIC:
				{
					SetMode = 0;
				}
					break;
				
			default:
					break;
		}
	}
}

/*
To ring the buzzer
*/
void Alarm_Ring(void)
{
	uint32_t time_cnt;
	struct tm time_date;
	time_date.tm_year = Alarm_Time[0] - 1900;	//Set the time after 1970-01-01 00:00:00
	time_date.tm_mon = Alarm_Time[1] - 1;		//0~11,is necessary to Subtracting 1 to indicate the month
	time_date.tm_mday = Alarm_Time[2];
	time_date.tm_hour = Alarm_Time[3];
	time_date.tm_min = Alarm_Time[4];
	time_date.tm_sec = Alarm_Time[5];
	
	time_cnt = mktime(&time_date); 	//the clock time convert to utc ,but it's china time, in a world is utc+8 
	
	if((RTC_GetCounter() + (8 * 60 * 60)) == time_cnt ) 	//RTC_Getcounter function is utc time ,is utc+0,if we want buzzer ring at local time ,we need to convert to utc+8
		Buzzer_ON();
	
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3) == 0)
		Buzzer_OFF();
}

