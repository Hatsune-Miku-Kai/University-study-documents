#include "stm32f10x.h"                  // Device header



void PWM_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启时钟信号
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	TIM_InternalClockConfig(TIM2);//内部时钟

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//采样频率的选择,暂时随便选
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//计数器模式,向上计数
	TIM_TimeBaseInitStructure.TIM_Period=100-1;//自动重装器
	TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;//预分频器
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//重复计数器,高级定时器才有,意为每隔多少周期才开始计数
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	

	TIM_OCInitTypeDef TIM_OCInitstructure;
	TIM_OCStructInit(&TIM_OCInitstructure);
	TIM_OCInitstructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitstructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitstructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitstructure.TIM_Pulse=0;

	TIM_OC1Init(TIM2,&TIM_OCInitstructure);

	TIM_Cmd(TIM2,ENABLE);//启动定时器

	

}



void PWM_SetCompare1(uint16_t Compare)
{

	TIM_SetCompare1(TIM2,Compare);
}
