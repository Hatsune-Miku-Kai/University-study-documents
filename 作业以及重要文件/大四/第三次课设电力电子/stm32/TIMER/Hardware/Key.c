#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//���ݿ�������PA9
//����¥��PA10	

void Key_Init(void)
	
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//�˴�Ϊ������λ����ܵ�GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1 | GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4 | GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);




	
	//�����λѡ�Լ����������GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1 | GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

			//�˴�Ϊ������GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4| GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//��������	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}


//�����ŵ�ƽ��ȡ,����Ϊ�͵�ƽ,����Ϊ�ߵ�ƽ
uint8_t Key_GetDoorMode(void)
{
   uint8_t KeyNum=0;
	
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0)KeyNum=1;//�˴��Ǵ�����ݿ���
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)KeyNum=2;//�˴�������ݹ���
	
	return KeyNum;
}

//�жϵ��������л�������
uint8_t Key_GetRunMode(void)
{
	uint8_t run=0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0)run=1;//�˴��Ǵ�����ݰ���1¥�ϰ�ť
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0)run=2;//�˴�������ݰ���2¥�°�ť
	
	return run;

}
