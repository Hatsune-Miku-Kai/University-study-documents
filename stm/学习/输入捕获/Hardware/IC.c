#include "stm32f10x.h"                  // Device header
void IC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//开启时钟信号
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	TIM_InternalClockConfig(TIM3);//定时器采用内部时钟

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//采样频率的选择,暂时随便选
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//计数器模式,向上计数
	TIM_TimeBaseInitStructure.TIM_Period=65536-1;//自动重装器ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1;//预分频器PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//重复计数器,高级定时器才有,意为每隔多少周期才开始计数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter=0x5;
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM3,&TIM_ICInitStructure);

	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);

	TIM_Cmd(TIM3,ENABLE);
}


uint32_t IC_GetFreq(void)
{
	return 1000000/TIM_GetCapture1(TIM3);
}

