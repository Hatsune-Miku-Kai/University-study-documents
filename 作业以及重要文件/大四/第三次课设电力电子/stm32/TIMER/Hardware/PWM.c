#include "stm32f10x.h"                  // Device header



void PWM_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//开启时钟信号
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;//通道三,通道四
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	TIM_InternalClockConfig(TIM4);//内部时钟

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//采样频率的选择,暂时随便选
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//计数器模式,向上计数
	TIM_TimeBaseInitStructure.TIM_Period=100-1;//自动重装器ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;//预分频器PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//重复计数器,高级定时器才有,意为每隔多少周期才开始计数
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	

	TIM_OCInitTypeDef TIM_OCInitstructure;
	TIM_OCStructInit(&TIM_OCInitstructure);
	TIM_OCInitstructure.TIM_OCMode=TIM_OCMode_PWM1;//配置输出模式为PWM1
	TIM_OCInitstructure.TIM_OCPolarity=TIM_OCPolarity_High;//配置REF高电平有效,即原始输出
	TIM_OCInitstructure.TIM_OutputState=TIM_OutputState_Enable;//设置输出有效
	TIM_OCInitstructure.TIM_Pulse=0;//CCR,占空比的值,默认为0,电机不转
	TIM_OC3Init(TIM4,&TIM_OCInitstructure);
	TIM_OC4Init(TIM4,&TIM_OCInitstructure);

	TIM_Cmd(TIM4,ENABLE);//启动定时器

	

}



void PWM_SetCompare3(uint16_t Compare)//调节占空比,compare是目标占空比
{

	TIM_SetCompare3(TIM4,Compare);
}


void PWM_SetCompare4(uint16_t Compare)//调节占空比,compare是目标占空比
{

	TIM_SetCompare4(TIM4,Compare);//让蜂鸣器输出不同声音
}
