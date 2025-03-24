#include "stm32f10x.h"                  // Device header


void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启时钟信号
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_Inverted,0x0f);


	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);


	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//采样频率的选择,暂时随便选
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//计数器模式,向上计数
	TIM_TimeBaseInitStructure.TIM_Period=10-1;//自动重装器
	TIM_TimeBaseInitStructure.TIM_Prescaler=1-1;//预分频器
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//重复计数器,高级定时器才有,意为每隔多少周期才开始计数
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//消除时基函数产生的置标志位带来的副作用

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能中断,让定时器产生的中断信息能够传达给NVIC,并选择更新中断参数

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);


	TIM_Cmd(TIM2,ENABLE);//启动定时器
}


uint16_t Timer_GetCounter()
{
	return TIM_GetCounter(TIM2);
}


/*
void TIM2_IRQHandler()
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{	
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
*/
