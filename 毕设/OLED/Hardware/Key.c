#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Rtc_Clock.h"

//DEFINE TIME AND DATE
#define YEAR 0
#define MON 1
#define DAY 2


#define HOUR 3
#define MIN 4
#define SEC 5

#define DATE 6
#define TIME 7

//Identify The Revise Mode
uint8_t SetMode = 0;


/*
///Init The GPIO Status
*/
void Key_Init(void)
	
{
	//GPIOB Key
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//GPIOA Key
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_0;
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
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
		{
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
			MyRTC_Time[YEAR] ++;
		}
		
		
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
		{
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
			MyRTC_Time[MON] ++;
		}
		
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
		{
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
			MyRTC_Time[DAY] ++;
		}
	}


	if(SetMode == TIME)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
		{
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
			MyRTC_Time[HOUR] ++;
		}
		
		
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
		{
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
			MyRTC_Time[MIN] ++;
		}
		
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
		{
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
			MyRTC_Time[SEC] ++;
		}
	}
	//return KeyNum;
}


/*
///To Get The Switch Mode   DATE or TIME
*/
void Switch_Change_Mode(void)
{

	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
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
					SetMode = DATE;
				}
					break;
				
			default:
					break;
		}
	}

}

