#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H

void TIM2_Init(void);
void TIM2_ON(void);
void TIM2_OFF(void);
void Ultrasonic_Init(void);
void EXTI4_IRQHandler(void);
void Ultrasonic_Start(void);
int Distance(void);

#endif
