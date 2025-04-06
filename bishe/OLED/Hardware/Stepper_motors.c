#include "stm32f10x.h"                  // Device header
#include "Delay.h"  
#include "Stepper_motors.h"
static int Sec_count = 1;
static int Min_count = 1;
static int Min_step = 0;
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
	Sec_count ++;
    switch(step) {  
		case 0:
            MOTOR_A_HIGH; MOTOR_B_LOW;  MOTOR_C_LOW;  MOTOR_D_LOW;  // 1000
            break;
        case 1:
            MOTOR_A_HIGH; MOTOR_B_HIGH; MOTOR_C_LOW;  MOTOR_D_LOW;  // 1100
            break;
        case 2:
            MOTOR_A_LOW;  MOTOR_B_HIGH; MOTOR_C_LOW;  MOTOR_D_LOW;  // 0100
            break;
        case 3:
            MOTOR_A_LOW;  MOTOR_B_HIGH; MOTOR_C_HIGH; MOTOR_D_LOW;  // 0110
            break;
        case 4:
            MOTOR_A_LOW;  MOTOR_B_LOW;  MOTOR_C_HIGH; MOTOR_D_LOW;  // 0010
            break;
        case 5:
            MOTOR_A_LOW;  MOTOR_B_LOW;  MOTOR_C_HIGH; MOTOR_D_HIGH; // 0011
            break;
        case 6:
            MOTOR_A_LOW;  MOTOR_B_LOW;  MOTOR_C_LOW;  MOTOR_D_HIGH; // 0001
            break;
        case 7:
            MOTOR_A_HIGH; MOTOR_B_LOW;  MOTOR_C_LOW;  MOTOR_D_HIGH; // 1001
            break;
    }
		if(Sec_count == 60)  //Tim2 will update 68 times per second , so in 60 seconds will update 60*68times = 4080 
		{
			StepMotor_Run_Mode(Min_step);
			Min_step = (Min_step + 1) % 8;
			Sec_count = 1;
		}
}

void StepMotor_Run_Mode(uint8_t step)
{
	Min_count++;
    switch(step) {  
		case 0:
        MOTOR_A_HIGH_MODE; MOTOR_B_LOW_MODE;  MOTOR_C_LOW_MODE;  MOTOR_D_LOW_MODE;  // 1000
        break;
    case 1:
        MOTOR_A_HIGH_MODE; MOTOR_B_HIGH_MODE; MOTOR_C_LOW_MODE;  MOTOR_D_LOW_MODE;  // 1100
        break;
    case 2:
        MOTOR_A_LOW_MODE;  MOTOR_B_HIGH_MODE; MOTOR_C_LOW_MODE;  MOTOR_D_LOW_MODE;  // 0100
        break;
    case 3:
        MOTOR_A_LOW_MODE;  MOTOR_B_HIGH_MODE; MOTOR_C_HIGH_MODE; MOTOR_D_LOW_MODE;  // 0110
        break;
    case 4:
        MOTOR_A_LOW_MODE;  MOTOR_B_LOW_MODE;  MOTOR_C_HIGH_MODE; MOTOR_D_LOW_MODE;  // 0010
        break;
    case 5:
        MOTOR_A_LOW_MODE;  MOTOR_B_LOW_MODE;  MOTOR_C_HIGH_MODE; MOTOR_D_HIGH_MODE; // 0011
        break;
    case 6:
        MOTOR_A_LOW_MODE;  MOTOR_B_LOW_MODE;  MOTOR_C_LOW_MODE;  MOTOR_D_HIGH_MODE; // 0001
        break;
    case 7:
        MOTOR_A_HIGH_MODE; MOTOR_B_LOW_MODE;  MOTOR_C_LOW_MODE;  MOTOR_D_HIGH_MODE; // 1001
        break;
    }
		if(Min_count == 60)
		{
			Min_count = 1;
		}

}

void StepMotor_Run(uint8_t step)
{	//4-1-4
    switch(step) {  
		case 0:
            MOTOR_A_HIGH; MOTOR_B_LOW;  MOTOR_C_LOW;  MOTOR_D_LOW;  // 1000
            break;
        case 1:
            MOTOR_A_HIGH; MOTOR_B_HIGH; MOTOR_C_LOW;  MOTOR_D_LOW;  // 1100
            break;
        case 2:
            MOTOR_A_LOW;  MOTOR_B_HIGH; MOTOR_C_LOW;  MOTOR_D_LOW;  // 0100
            break;
        case 3:
            MOTOR_A_LOW;  MOTOR_B_HIGH; MOTOR_C_HIGH; MOTOR_D_LOW;  // 0110
            break;
        case 4:
            MOTOR_A_LOW;  MOTOR_B_LOW;  MOTOR_C_HIGH; MOTOR_D_LOW;  // 0010
            break;
        case 5:
            MOTOR_A_LOW;  MOTOR_B_LOW;  MOTOR_C_HIGH; MOTOR_D_HIGH; // 0011
            break;
        case 6:
            MOTOR_A_LOW;  MOTOR_B_LOW;  MOTOR_C_LOW;  MOTOR_D_HIGH; // 0001
            break;
        case 7:
            MOTOR_A_HIGH; MOTOR_B_LOW;  MOTOR_C_LOW;  MOTOR_D_HIGH; // 1001
            break;
    }

}

void MOTOR_Angle(uint16_t angle) 
{	
		int step = 0;
		for(u16 i=0;i<(64*angle);i++)	//64*64=4096 64*180=256 //512
		{
			StepMotor_Run(step);
			step = (step + 1) % 8;
		}
}
