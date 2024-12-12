#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Key.h"
#include "PWM.h"
#include "LED.h"
uint8_t display[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uint8_t runmode=0;//获取电梯状态
uint8_t open=0;//电梯门状态，默认是关闭
uint8_t temp=0;
uint8_t	tempopen=0;
uint8_t	ring=1;
uint16_t i=0;//设置电机占空比

int main(void)
{
	Key_Init();
	PWM_Init();
	uint8_t floor=1;

	while(1)
	{	
		runmode=Key_GetRunMode();//获取一楼的人是否按上楼键,1上楼,2下楼,0默认值//bug,每次扫描都会等于0
		if(runmode==1)temp=1;
		if(runmode==2)temp=2;
		//if(runmode==0)temp=0;
		open=Key_GetDoorMode();//1为开门,2为关门,0为默认值//BUG,每次扫描都会等于0	
		if(open==1)tempopen=1;
		if(open==2)tempopen=2;
		switch(temp)
		{
			case 1://一楼的人去二楼
				if(tempopen==1)//开门
				{
					temp=0;//防止下次电机继续转
					ring=1;
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1){
					GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);
					GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_RESET);
						if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
						{break;}				
					}
					GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_SET);//驱动电机正转,PWM控制
					GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_RESET);
					//if(floor!=2)
					//{
						//for(i=0;i<50;i++)PWM_SetCompare3(i);	
						//for(i=50;i>0;i--)PWM_SetCompare3(i);				//驱动电机减速,PWM控制	
					//GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);
					//GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_RESET);
					//}
					floor=2;//显示在二楼
					tempopen=2;
				}	
				break;
				
			case 2://二楼的人去一楼
				if(tempopen==1)//开门
				{
					temp=0;//防止下次开门电机转
					ring=1;
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1){
					GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);
					GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_RESET);
						if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
						{break;}				
					}
					GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_SET);//驱动电机反转,PWM控制
					GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);
					//if(floor==1)
					//{
						//for(i=0;i<50;i++)PWM_SetCompare3(i);//不减速了
						//for(i=50;i>0;i--)PWM_SetCompare3(i);//
					//GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);
					//GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_RESET);
					//}
						floor=1;//显示在一楼
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
					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);//选择高位
					GPIO_Write(GPIOA,display[0]);//显示0
					Delay_ms(1);
					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);//选择低位
					GPIO_Write(GPIOA,display[2]);//显示数字02,电梯在二楼
					Delay_ms(1);
					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);//清除
					if(tempopen==2&&ring==1){
						PWM_SetCompare4(30);//1kHz 			//可以修改,等到开新的定时器产生新的PWM频率,不开了
						Delay_ms(50);
						PWM_SetCompare4(50);//1.3KHz     //可以修改,等到开新的定时器产生新的PWM频率
						Delay_ms(50);
						PWM_SetCompare4(100);//2KHz      //可以修改,等到开新的定时器产生新的PWM频率
						Delay_ms(50);
						ring=0;
						}
					if(tempopen==1&&ring==0)PWM_SetCompare4(0);	
					}
						
		if(floor==1){
					if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_3)==1) {Delay_ms(200);GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_RESET);}
					LED_clear();
					Delay_ms(1);
					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);//选择高位
					GPIO_Write(GPIOA,display[0]);//显示0
					Delay_ms(1);
					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);//选择低位
					GPIO_Write(GPIOA,display[1]);//显示数字01,电梯在一楼
					Delay_ms(1);
					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);//清除
					if(tempopen==2&&ring==1){
						PWM_SetCompare4(30);     //可以修改,等到开新的定时器产生新的PWM频率,不开了
						Delay_ms(50);
						PWM_SetCompare4(50);     //可以修改,等到开新的定时器产生新的PWM频率
						Delay_ms(50);
						PWM_SetCompare4(100);    //可以修改,等到开新的定时器产生新的PWM频率
						Delay_ms(50);
						ring=0;                 
						}
					if(tempopen==1&&ring==0)PWM_SetCompare4(0);
					}
			
	}
					
}

//备份
	//	runmode=Key_GetRunMode();//获取一楼的人是否按上楼键
	//	open=Key_GetMode();
	//	switch(runmode)
	//	{
	//		case 1://一楼的人去二楼
	//			if(open==1)//关门
	//			{
	//				GPIO_SetBits(GPIOB,GPIO_Pin_2);//驱动电机正转,PWM控制
	//				GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	//				for(i=0;i<50;i++)
	//					PWM_SetCompare3(i);
	//				for(i=50;i>0;i--)					//驱动电机减速,PWM控制
	//					PWM_SetCompare3(i);
	//				floor=2;//显示在二楼
	//			}	
	//			break;
	//			
	//		case 2://二楼的人去一楼
	//			if(open==1)
	//			{
	//				GPIO_SetBits(GPIOB,GPIO_Pin_3);//驱动电机转,PWM控制
	//				GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//				for(i=0;i<50;i++)
	//					PWM_SetCompare3(i);
	//				for(i=50;i>0;i--)
	//					PWM_SetCompare3(i);
	//				floor=1;//显示在一楼
	//			}	
	//			break;
	//			
	//		default:
	//			if(runmode==0&&open==1){
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);//选择高位
	//					GPIO_Write(GPIOA,display[0]);//显示0
	//					Delay_ms(1);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);//选择低位
	//					GPIO_Write(GPIOA,display[1]);//显示数字01,电梯默认在一楼
	//					Delay_ms(1);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);//清除
	//		}
	//		break;
	//	}
	//			if(floor==2){
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);//选择高位
	//					GPIO_Write(GPIOA,display[0]);//显示0
	//					Delay_ms(1);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);//选择低位
	//					GPIO_Write(GPIOA,display[2]);//显示数字02,电梯在二楼
	//					Delay_ms(1);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);//清除
	//					}
	//			if(floor==1){
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);//选择高位
	//					GPIO_Write(GPIOA,display[0]);//显示0
	//					Delay_ms(1);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);//选择低位
	//					GPIO_Write(GPIOA,display[1]);//显示数字01,电梯在一楼
	//					Delay_ms(1);
	//					GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);//清除
	//			}
  //
