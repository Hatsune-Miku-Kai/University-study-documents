#ifndef  __MyRTC_H
#define __MyRTC_H
#include <stdint.h>

void MyRTC_Init(void);
void MyRTC_SetTime(void);
void MyRTC_ReadTime(void);
extern int16_t MyRTC_Time[];

#endif
