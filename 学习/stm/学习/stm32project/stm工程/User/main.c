#include "stm32f10x.h"                  // Device header

int main()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//GPIO_SetBits(GPIOC,GPIO_Pin_13);
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	
	
	GPIO_InitTypeDef GPIO_AInitStructure;
	GPIO_AInitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_AInitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_AInitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_AInitStructure);
	while(1)
	{
		 GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
	}
}
