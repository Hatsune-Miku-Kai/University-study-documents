#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void  MyI2C_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	Delay_us(10);
}


void  MyI2C_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	Delay_us(10);
}


uint8_t  MyI2C_R_SDA(void)
{
	uint8_t BitValue=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return BitValue;
}


void MyI2CInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_SetBits(GPIOA,GPIO_Pin_10 | GPIO_Pin_11);
}


void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}


void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}


void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		MyI2C_W_SDA(Byte &0x80>>i);
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	}
	
}

uint8_t MyI2C_ReceiveByte(void)//主机接收信息
{
	uint8_t i,Byte=0x00;
	MyI2C_W_SDA(1);//主机交出数据线控制权,从机几乎同一时刻进行数据上传进而改变数据线电平
	for(i=0;i<8;i++)
	{
		MyI2C_W_SCL(1);//主机接收从机发送的一位数据
		if(MyI2C_R_SDA()==1)Byte =(Byte | 0x80>>i);	//此时如果从机没有改变数据线的电平,则说明从机发送的这一位数据是1,反之改变了则这一位是0
		MyI2C_W_SCL(0);//主机准备接收下一位数据
	}
	return Byte;//返回从机发送的数据,上面循环进行的是或操作
}




void MyI2C_SendAck(uint8_t AckBit)
{

		MyI2C_W_SDA(AckBit);
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveAck(void)//主机接收从机的应答位
{
		uint8_t AckBit;
		MyI2C_W_SDA(1);//主机交出数据线控制权,此时从机改变数据线电平
		MyI2C_W_SCL(1);
		AckBit=MyI2C_R_SDA();
		MyI2C_W_SCL(0);
		return AckBit;//主机接收的数据进行返回
}
