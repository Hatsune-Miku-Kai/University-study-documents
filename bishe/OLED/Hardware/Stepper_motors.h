#ifndef	__STEPPER_MOTOR
#define __STEPPER_MOTOR
#include <stdint.h>
void Motor_Init(void);
void StepMotor_Run_Min(uint8_t step);
void StepMotor_Run_Hour(uint8_t step);
void MOTOR_Angle(float angle);
void MOTOR_Angle_Hour(float angle);
void MOTOR_Angle_Min(float angle); 
//extern const uint8_t stepSequence[4];
#endif


#define MOTOR_A_MUSIC  GPIO_Pin_11
#define MOTOR_B_MUSIC  GPIO_Pin_12
#define MOTOR_C_MUSIC  GPIO_Pin_13
#define MOTOR_D_MUSIC  GPIO_Pin_14

#define MOTOR_A_MODE  GPIO_Pin_7
#define MOTOR_B_MODE  GPIO_Pin_0
#define MOTOR_C_MODE  GPIO_Pin_1
#define MOTOR_D_MODE  GPIO_Pin_10


#define MOTOR_A_HIGH 		GPIO_SetBits(GPIOB ,MOTOR_A_MUSIC)
#define MOTOR_A_LOW 		GPIO_ResetBits(GPIOB ,MOTOR_A_MUSIC)

#define MOTOR_B_HIGH 		GPIO_SetBits(GPIOB ,MOTOR_B_MUSIC)
#define MOTOR_B_LOW 		GPIO_ResetBits(GPIOB ,MOTOR_B_MUSIC)

#define MOTOR_C_HIGH 		GPIO_SetBits(GPIOB ,MOTOR_C_MUSIC)
#define MOTOR_C_LOW 		GPIO_ResetBits(GPIOB ,MOTOR_C_MUSIC)

#define MOTOR_D_HIGH 		GPIO_SetBits(GPIOB ,MOTOR_D_MUSIC)
#define MOTOR_D_LOW 		GPIO_ResetBits(GPIOB ,MOTOR_D_MUSIC)


#define MOTOR_A_HIGH_MODE 		GPIO_SetBits(GPIOA ,MOTOR_A_MODE)
#define MOTOR_A_LOW_MODE 		GPIO_ResetBits(GPIOA ,MOTOR_A_MODE)

#define MOTOR_B_HIGH_MODE 		GPIO_SetBits(GPIOB ,MOTOR_B_MODE)
#define MOTOR_B_LOW_MODE 		GPIO_ResetBits(GPIOB ,MOTOR_B_MODE)

#define MOTOR_C_HIGH_MODE 		GPIO_SetBits(GPIOB ,MOTOR_C_MODE)
#define MOTOR_C_LOW_MODE 		GPIO_ResetBits(GPIOB ,MOTOR_C_MODE)

#define MOTOR_D_HIGH_MODE 		GPIO_SetBits(GPIOB ,MOTOR_D_MODE)
#define MOTOR_D_LOW_MODE 		GPIO_ResetBits(GPIOB ,MOTOR_D_MODE)
