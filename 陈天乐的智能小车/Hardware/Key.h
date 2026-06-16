#ifndef __KEY_H
#define __KEY_H

#define HW_1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define HW_2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define HW_3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)
#define HW_4 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)

void Key_Init(void);
uint8_t Key_GetNum(void);
void TCRT5000_Init(void);

#endif
