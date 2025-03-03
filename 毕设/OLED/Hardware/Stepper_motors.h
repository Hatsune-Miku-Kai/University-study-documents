#ifndef	__STEPPER_MOTOR
#define __STEPPER_MOTOR

void Motor_Init(void);
void StepMotor_Run(uint8_t step);

//extern const uint8_t stepSequence[4];
#endif


#define MOTOR_A  GPIO_Pin_1
#define MOTOR_B  GPIO_Pin_2
#define MOTOR_C  GPIO_Pin_3
#define MOTOR_D  GPIO_Pin_4

#define MOTOR_A_HIGH 		GPIO_SetBits(GPIOA ,MOTOR_A)
#define MOTOR_A_LOW 		GPIO_ResetBits(GPIOA ,MOTOR_A)

#define MOTOR_B_HIGH 		GPIO_SetBits(GPIOA ,MOTOR_B)
#define MOTOR_B_LOW 		GPIO_ResetBits(GPIOA ,MOTOR_B)

#define MOTOR_C_HIGH 		GPIO_SetBits(GPIOA ,MOTOR_C)
#define MOTOR_C_LOW 		GPIO_ResetBits(GPIOA ,MOTOR_C)

#define MOTOR_D_HIGH 		GPIO_SetBits(GPIOA ,MOTOR_D)
#define MOTOR_D_LOW 		GPIO_ResetBits(GPIOA ,MOTOR_D)
