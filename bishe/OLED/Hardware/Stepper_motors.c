#include "stm32f10x.h"                  // Device header
#include "Delay.h"  
#include "Stepper_motors.h"

void Motor_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = MOTOR_A_MUSIC | MOTOR_B_MUSIC | MOTOR_C_MUSIC | MOTOR_D_MUSIC | MOTOR_A_MODE | MOTOR_B_MODE | MOTOR_C_MODE | MOTOR_D_MODE;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    GPIO_ResetBits(GPIOA, MOTOR_A_MUSIC | MOTOR_B_MUSIC | MOTOR_C_MUSIC | MOTOR_D_MUSIC | MOTOR_A_MODE | MOTOR_B_MODE | MOTOR_C_MODE | MOTOR_D_MODE);
}

/*
The stepper motor operates in four phases and four beats
*/
void StepMotor_Run_Music(uint8_t step)
{	//4-1-4
    switch(step) {  
		
		case 0 :
			MOTOR_A_LOW;MOTOR_B_HIGH;MOTOR_C_HIGH;MOTOR_D_LOW;	//1
			Delay_ms(1);
		break;
		
		case 1 :
			MOTOR_A_LOW;MOTOR_B_LOW;MOTOR_C_HIGH;MOTOR_D_HIGH;	//2
			Delay_ms(1);
		break;
		
		case 2 :
			MOTOR_A_HIGH;MOTOR_B_LOW;MOTOR_C_LOW;MOTOR_D_HIGH;	//3
			Delay_ms(1);
		break;
		
		case 3 :
			MOTOR_A_HIGH;MOTOR_B_HIGH;MOTOR_C_LOW;MOTOR_D_LOW;	//4
			Delay_ms(1);
		break;			
    }
}

void StepMotor_Run_Mode(uint8_t step)
{
    switch(step) {  
		
		case 0 :
			MOTOR_A_LOW_MODE;MOTOR_B_HIGH_MODE;MOTOR_C_HIGH_MODE;MOTOR_D_LOW_MODE;	//1
			Delay_ms(1);
		break;
		
		case 1 :
			MOTOR_A_LOW_MODE;MOTOR_B_LOW_MODE;MOTOR_C_HIGH_MODE;MOTOR_D_HIGH_MODE;	//2
			Delay_ms(1);
		break;
		
		case 2 :
			MOTOR_A_HIGH_MODE;MOTOR_B_LOW_MODE;MOTOR_C_LOW_MODE;MOTOR_D_HIGH_MODE;	//3
			Delay_ms(1);
		break;
		
		case 3 :
			MOTOR_A_HIGH_MODE;MOTOR_B_HIGH_MODE;MOTOR_C_LOW_MODE;MOTOR_D_LOW_MODE;	//4
			Delay_ms(1);
		break;			
    }

}
