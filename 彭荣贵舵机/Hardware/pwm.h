#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"
void Pwm_Init(void);
void PWM_SetCompare(uint16_t compare);
void PWM_SetCompareB(uint16_t compare);
void PWM_SetCompareA(uint16_t compare);



#endif
