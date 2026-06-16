#ifndef __PWM_H
#define __PWM_H

void TIM2_PWM_Init(void);
void TIM3_PWM_Init(void);
void PWM_SetCompare2(uint16_t Compare);
void PWM_SetCompare3(uint16_t Compare);
void PWM_SetCompare1(uint16_t Compare);
 

#endif
