#ifndef __KEY_H
#define __KEY_H
#include <stdint.h>
void Key_GetNum(void);
void Key_Init(void);
void Switch_Change_Mode(void);
void Alarm_Clock(void);
void Reduce_Num(uint8_t mode, uint8_t arg);
void Alarm_Ring(void);

extern uint8_t SetMode;
extern uint8_t Reduce_Mode ;
extern int16_t Alarm_Time[];
#endif


#include "Buzzer.h"

//DEFINE TIME AND DATE
#define YEAR 0
#define MON 1
#define DAY 2


#define HOUR 3
#define MIN 4
#define SEC 5

#define DATE 6
#define TIME 7
#define ALARM_DATE 8
#define ALARM_TIME 9
#define MUSIC 10







