#include "stm32f10x.h"                  // Device header

int16_t Encoder_Count=0;

void Encoder_Init()
{   //开启GPIOB以及AFIO的时钟,NVIC和EXIT不用开
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);//指定EXTI需要开通指向NVIC的哪些通道
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);

	EXTI_InitTypeDef EXTI_Initstructure;
	EXTI_Initstructure.EXTI_Line=EXTI_Line0|EXTI_Line1;
	EXTI_Initstructure.EXTI_LineCmd=ENABLE;
	EXTI_Initstructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Initstructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_Initstructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;//接入EXTI0的线程
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;//接入EXTI1的线程
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);

}


int16_t Encoder_Get(void)
{
	int16_t temp;
	temp=Encoder_Count;
	Encoder_Count=0;
	return temp;
}

void EXTI0_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
		Encoder_Count--;
EXTI_ClearITPendingBit(EXTI_Line0);
	}
}



void EXTI1_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line1)==SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
		Encoder_Count++;
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}
