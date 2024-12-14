#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//电梯开关门是PA9
//上下楼是PA10	

void Key_Init(void)
	
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//此处为控制两位数码管的GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1 | GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4 | GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);




	
	//数码管位选以及电机驱动的GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1 | GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

			//此处为按键的GPIO初始化
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4| GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}


//开关门电平获取,开门为低电平,关门为高电平
uint8_t Key_GetDoorMode(void)
{
   uint8_t KeyNum=0;
	
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0)KeyNum=1;//此处是代表电梯开门
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)KeyNum=2;//此处代表电梯关门
	
	return KeyNum;
}

//判断电梯是上行还是下行
uint8_t Key_GetRunMode(void)
{
	uint8_t run=0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0)run=1;//此处是代表电梯按下1楼上按钮
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0)run=2;//此处代表电梯按下2楼下按钮
	
	return run;

}
