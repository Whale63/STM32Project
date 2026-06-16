#include "stm32f10x.h"
#include "pwm.h"


void TIM4_Pwm_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	TIM_InternalClockConfig(TIM4);//Configures the TIM4 internal Clock
	
	TIM_TimeBaseInitTypeDef Tim_TimeBaseInitStructure;
	Tim_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	Tim_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	Tim_TimeBaseInitStructure.TIM_Period=2000;//ARR value
	Tim_TimeBaseInitStructure.TIM_Prescaler=720-1;//PSC value
	Tim_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM4,&Tim_TimeBaseInitStructure);
	
	
	TIM_OCInitTypeDef Tim_OCInitStructure;
	
	TIM_OCStructInit(&Tim_OCInitStructure);
	
	Tim_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	Tim_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//REFerence high effect
	Tim_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	Tim_OCInitStructure.TIM_Pulse=0;//CCR value
	
	
	TIM_OC1Init(TIM4,&Tim_OCInitStructure);
	TIM_OC2Init(TIM4,&Tim_OCInitStructure);
	TIM_OC3Init(TIM4,&Tim_OCInitStructure);
	TIM_OC4Init(TIM4,&Tim_OCInitStructure);
	
	TIM_ARRPreloadConfig(TIM4,ENABLE);
	TIM_CtrlPWMOutputs(TIM4,ENABLE);
	TIM_OC1PreloadConfig(TIM4,ENABLE);
	TIM_OC2PreloadConfig(TIM4,ENABLE);
	TIM_OC3PreloadConfig(TIM4,ENABLE);
	TIM_OC4PreloadConfig(TIM4,ENABLE);
	
	TIM_Cmd(TIM4,ENABLE);// Enables the TIM4 peripheral.
	
	
}


void PWM_SetCompare(uint16_t compare)//FRONTA==PB6,FRONTB==PB7;BACKA==PB9,BACKB==PB8
{

	TIM_SetCompare1(TIM4,compare);
	TIM_SetCompare2(TIM4,compare);//FRONTB
	TIM_SetCompare3(TIM4,compare);//BACKB
	TIM_SetCompare4(TIM4,compare);

}
void PWM_SetCompareB(uint16_t compare)//FRONTA==PB6,FRONTB==PB7;BACKA==PB9,BACKB==PB8
{

//	TIM_SetCompare1(TIM4,compare);
	TIM_SetCompare2(TIM4,compare);//FRONTB
	TIM_SetCompare3(TIM4,compare);//BACKB
//	TIM_SetCompare4(TIM4,compare);

}
void PWM_SetCompareA(uint16_t compare)
{

	TIM_SetCompare1(TIM4,compare);//FRONTA
//	TIM_SetCompare2(TIM4,compare);//7
//	TIM_SetCompare3(TIM4,compare);//8
	TIM_SetCompare4(TIM4,compare);//BACKA

}
