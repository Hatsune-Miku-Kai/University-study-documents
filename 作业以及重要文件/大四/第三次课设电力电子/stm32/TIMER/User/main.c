#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Key.h"
#include "PWM.h"
#include "LED.h"
uint8_t display[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uint8_t runmode=0;//��ȡ����״̬
uint8_t open=0;//������״̬��Ĭ���ǹر�
uint8_t temp=0;
uint8_t	tempopen=0;
uint8_t	ring=1;
uint16_t i=0;//���õ��ռ�ձ�

int main(void)
{
	Key_Init();
	PWM_Init();
	uint8_t floor=1;

	while(1)
	{	
		runmode=Key_GetRunMode();//��ȡһ¥�����Ƿ���¥��,1��¥,2��¥,0Ĭ��ֵ//bug,ÿ��ɨ�趼�����0
		if(runmode==1)temp=1;
		if(runmode==2)temp=2;
		//if(runmode==0)temp=0;
		open=Key_GetDoorMode();//1Ϊ����,2Ϊ����,0ΪĬ��ֵ//BUG,ÿ��ɨ�趼�����0	
		if(open==1)tempopen=1;
		if(open==2)tempopen=2;
		switch(temp)
		{
			case 1://һ¥����ȥ��¥
				if(tempopen==1)//����
				{
					temp=0;//��ֹ�´ε������ת
					ring=1;
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1){
					GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);
					GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_RESET);
						if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
						{break;}				
					}
					GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_SET);//���������ת,PWM����
					GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_RESET);
					//if(floor!=2)
					//{
						//for(i=0;i<50;i++)PWM_SetCompare3(i);	
						//for(i=50;i>0;i--)PWM_SetCompare3(i);				//�����������,PWM����	
					//GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);
					//GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_RESET);
					//}
					floor=2;//��ʾ�ڶ�¥
					tempopen=2;
				}	
				break;
				
			case 2://��¥����ȥһ¥
				if(tempopen==1)//����
				{
					temp=0;//��ֹ�´ο��ŵ��ת
					ring=1;
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1){
					GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);
					GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_RESET);
						if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
						{break;}				
					}
					GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_SET);//���������ת,PWM����
					GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);
					//if(floor==1)
					//{
						//for(i=0;i<50;i++)PWM_SetCompare3(i);//��������
						//for(i=50;i>0;i--)PWM_SetCompare3(i);//
					//GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);
					//GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_RESET);
					//}
						floor=1;//��ʾ��һ¥
						tempopen=2;
				}	
				break;
				
			default:
				break;
		}
		if(floor==2){
					if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_2)==1) {Delay_ms(200);GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);}
					LED_clear();
					Delay_ms(1);
					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);//ѡ���λ
					GPIO_Write(GPIOA,display[0]);//��ʾ0
					Delay_ms(1);
					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);//ѡ���λ
					GPIO_Write(GPIOA,display[2]);//��ʾ����02,�����ڶ�¥
					Delay_ms(1);
					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);//���
					if(tempopen==2&&ring==1){
						PWM_SetCompare4(30);//1kHz 			//�����޸�,�ȵ����µĶ�ʱ�������µ�PWMƵ��,������
						Delay_ms(50);
						PWM_SetCompare4(50);//1.3KHz     //�����޸�,�ȵ����µĶ�ʱ�������µ�PWMƵ��
						Delay_ms(50);
						PWM_SetCompare4(100);//2KHz      //�����޸�,�ȵ����µĶ�ʱ�������µ�PWMƵ��
						Delay_ms(50);
						ring=0;
						}
					if(tempopen==1&&ring==0)PWM_SetCompare4(0);	
					}
						
		if(floor==1){
					if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_3)==1) {Delay_ms(200);GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_RESET);}
					LED_clear();
					Delay_ms(1);
					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);//ѡ���λ
					GPIO_Write(GPIOA,display[0]);//��ʾ0
					Delay_ms(1);
					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);//ѡ���λ
					GPIO_Write(GPIOA,display[1]);//��ʾ����01,������һ¥
					Delay_ms(1);
					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);//���
					if(tempopen==2&&ring==1){
						PWM_SetCompare4(30);     //�����޸�,�ȵ����µĶ�ʱ�������µ�PWMƵ��,������
						Delay_ms(50);
						PWM_SetCompare4(50);     //�����޸�,�ȵ����µĶ�ʱ�������µ�PWMƵ��
						Delay_ms(50);
						PWM_SetCompare4(100);    //�����޸�,�ȵ����µĶ�ʱ�������µ�PWMƵ��
						Delay_ms(50);
						ring=0;                 
						}
					if(tempopen==1&&ring==0)PWM_SetCompare4(0);
					}
			
	}
					
}

//����
	//	runmode=Key_GetRunMode();//��ȡһ¥�����Ƿ���¥��
	//	open=Key_GetMode();
	//	switch(runmode)
	//	{
	//		case 1://һ¥����ȥ��¥
	//			if(open==1)//����
	//			{
	//				GPIO_SetBits(GPIOB,GPIO_Pin_2);//���������ת,PWM����
	//				GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	//				for(i=0;i<50;i++)
	//					PWM_SetCompare3(i);
	//				for(i=50;i>0;i--)					//�����������,PWM����
	//					PWM_SetCompare3(i);
	//				floor=2;//��ʾ�ڶ�¥
	//			}	
	//			break;
	//			
	//		case 2://��¥����ȥһ¥
	//			if(open==1)
	//			{
	//				GPIO_SetBits(GPIOB,GPIO_Pin_3);//�������ת,PWM����
	//				GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//				for(i=0;i<50;i++)
	//					PWM_SetCompare3(i);
	//				for(i=50;i>0;i--)
	//					PWM_SetCompare3(i);
	//				floor=1;//��ʾ��һ¥
	//			}	
	//			break;
	//			
	//		default:
	//			if(runmode==0&&open==1){
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);//ѡ���λ
	//					GPIO_Write(GPIOA,display[0]);//��ʾ0
	//					Delay_ms(1);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);//ѡ���λ
	//					GPIO_Write(GPIOA,display[1]);//��ʾ����01,����Ĭ����һ¥
	//					Delay_ms(1);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);//���
	//		}
	//		break;
	//	}
	//			if(floor==2){
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);//ѡ���λ
	//					GPIO_Write(GPIOA,display[0]);//��ʾ0
	//					Delay_ms(1);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);//ѡ���λ
	//					GPIO_Write(GPIOA,display[2]);//��ʾ����02,�����ڶ�¥
	//					Delay_ms(1);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);//���
	//					}
	//			if(floor==1){
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);//ѡ���λ
	//					GPIO_Write(GPIOA,display[0]);//��ʾ0
	//					Delay_ms(1);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);//ѡ���λ
	//					GPIO_Write(GPIOA,display[1]);//��ʾ����01,������һ¥
	//					Delay_ms(1);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);//���
	//			}
  //
