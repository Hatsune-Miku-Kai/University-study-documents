#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Serial.h"
#include "Delay.h"



int main(void)
{
//	uint8_t MyArray[]={0x42,0x43,0x44,0x45};
	OLED_Init();

	Serial_Init();
	//Serial_SendByte(0x41);
	//OLED_Clear();
	//Serial_SendArray(MyArray,4);
	//Serial_SendString("Hello World!\r\n");
	//Serial_SendNumber(30000,5);
	//printf("Num=%d\r\n",666);
	
	//char String[100];
	//sprintf(String,"Num=%d\r\n",666);
	//Serial_SendString(String);
	
	//Serial_Printf("Num=%d\r\n",666);
	Serial_Printf("你好,世界");
	while(1)
	{
		
	}	
	
}


