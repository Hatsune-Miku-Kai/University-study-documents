#include "stm32f10x.h"                  // Device header
#include "Delay.h"  
#include "Stepper_motors.h"
static int Sec_count = 1;
static int Min_count = 1;
static int Min_step = 0;
int static step_min = 0;
int static step_hour = 0;
void Motor_Init(void) 
{

    GPIO_ResetBits(GPIOB, MOTOR_A_MUSIC | MOTOR_B_MUSIC | MOTOR_C_MUSIC | MOTOR_D_MUSIC | MOTOR_B_MODE | MOTOR_C_MODE | MOTOR_D_MODE);
	GPIO_ResetBits(GPIOA, MOTOR_A_MODE);
}

/*
The stepper motor operates in four phases and four beats
*/
void StepMotor_Run_Min(uint8_t step)
{	//4-1-4
	Sec_count ++;
    switch(step) {  
		case 0 :
			MOTOR_A_LOW;MOTOR_B_HIGH;MOTOR_C_HIGH;MOTOR_D_HIGH;	//1
		break;
		
		case 1 :
			MOTOR_A_HIGH;MOTOR_B_LOW;MOTOR_C_HIGH;MOTOR_D_HIGH;	//2
		break;
		
		case 2 :
			MOTOR_A_HIGH;MOTOR_B_HIGH;MOTOR_C_LOW;MOTOR_D_HIGH;	//3
		break;
		
		case 3 :
			MOTOR_A_HIGH;MOTOR_B_HIGH;MOTOR_C_HIGH;MOTOR_D_LOW;	//4
		break;	
    }
		if(Sec_count == 60)  //Tim2 will update 68 times per second , so in 60 seconds will update 60*68times = 4080 
		{
			StepMotor_Run_Hour(Min_step);
			Min_step = (Min_step + 1) % 4;
			Sec_count = 1;
		}
}

void StepMotor_Run_Hour(uint8_t step)
{
	Min_count++;
    switch(step) {  
		case 0 :
			MOTOR_A_LOW_MODE;MOTOR_B_HIGH_MODE;MOTOR_C_HIGH_MODE;MOTOR_D_HIGH_MODE;	//1
		break;
		
		case 1 :
			MOTOR_A_HIGH_MODE;MOTOR_B_LOW_MODE;MOTOR_C_HIGH_MODE;MOTOR_D_HIGH_MODE;	//2
		break;
		
		case 2 :
			MOTOR_A_HIGH_MODE;MOTOR_B_HIGH_MODE;MOTOR_C_LOW_MODE;MOTOR_D_HIGH_MODE;	//3
		break;
		
		case 3 :
			MOTOR_A_HIGH_MODE;MOTOR_B_HIGH_MODE;MOTOR_C_HIGH_MODE;MOTOR_D_LOW_MODE;	//4
		break;	
    }
	Delay_ms(10);
		if(Min_count == 60)
		{
			Min_count = 1;
		}

}

void StepMotor_Run(uint8_t step)
{	//4-1-4
    switch(step) {  
		case 0 :
			MOTOR_A_LOW;MOTOR_B_HIGH;MOTOR_C_HIGH;MOTOR_D_HIGH;	//1
		break;
		
		case 1 :
			MOTOR_A_HIGH;MOTOR_B_LOW;MOTOR_C_HIGH;MOTOR_D_HIGH;	//2
		break;
		
		case 2 :
			MOTOR_A_HIGH;MOTOR_B_HIGH;MOTOR_C_LOW;MOTOR_D_HIGH;	//3
		break;
		
		case 3 :
			MOTOR_A_HIGH;MOTOR_B_HIGH;MOTOR_C_HIGH;MOTOR_D_LOW;	//4
		break;	
    }
	Delay_ms(10);

}

void MOTOR_Angle_Min(float angle) 
{	

		for(u16 i=0;i<(64*angle);i++)	//64*64=4096 64*180=256 //512
		{
			StepMotor_Run_Min(step_min);
			step_min = (step_min + 1) % 4;
			Delay_ms(10);
		}
}

void MOTOR_Angle_Hour(float angle) 
{	
	
		for(u16 i=0;i<(64*angle);i++)	//64*64=4096 64*180=256 //512
		{
			StepMotor_Run_Hour(step_hour);
			step_hour = (step_hour + 1) % 4;
			Delay_ms(10);
		}
}
