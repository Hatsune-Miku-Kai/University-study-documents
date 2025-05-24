#include "stm32f10x.h"                  // Device header
#include <time.h>

void MyRTC_SetTime(void);


int16_t MyRTC_Time[]={2025,2,4,16,39,13};
void MyRTC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	
	PWR_BackupAccessCmd(ENABLE);
	
	if(BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5 )
	{
		RCC_LSEConfig(RCC_LSE_ON);
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET);
		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		
		RTC_WaitForSynchro();		
		RTC_WaitForLastTask();
		
		RTC_SetPrescaler(32768 - 1);
		RTC_WaitForLastTask();
		
		MyRTC_SetTime();
				
		BKP_WriteBackupRegister(BKP_DR1 , 0xA5A5);
	}
	
	else
	{
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
	}
	
}

void MyRTC_SetTime(void)
{
	time_t time_cnt;
	struct tm time_date;
	time_date.tm_year = MyRTC_Time[0] - 1900;	//Set the time after 1970-01-01 00:00:00
	time_date.tm_mon = MyRTC_Time[1] - 1;		//0~11,is necessary to Subtracting 1 to indicate the month
	time_date.tm_mday = MyRTC_Time[2];
	time_date.tm_hour = MyRTC_Time[3];
	time_date.tm_min = MyRTC_Time[4];
	time_date.tm_sec = MyRTC_Time[5];
	
	time_cnt = mktime(&time_date) - (8 * 60 * 60);	//The input time is UTC Time
	RTC_SetCounter(time_cnt);
	RTC_WaitForLastTask();
	
}


void MyRTC_ReadTime(void)
{
	time_t time_cnt;
	struct tm time_date;
																		//UTC time is 1970-01-01 00:00:00
	time_cnt = RTC_GetCounter() + (8 * 60 * 60);	//UTC time is converted to Beijing time
	time_date = *localtime(&time_cnt);
	
	MyRTC_Time[0] = time_date.tm_year + 1900;
	MyRTC_Time[1] = time_date.tm_mon + 1;
	MyRTC_Time[2] = time_date.tm_mday;
	MyRTC_Time[3] = time_date.tm_hour;
	MyRTC_Time[4] = time_date.tm_min;
	MyRTC_Time[5] = time_date.tm_sec;
	RTC_WaitForLastTask();
}
