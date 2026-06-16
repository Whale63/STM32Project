#include "stm32f10x.h"                  // Device header
void TIM2_PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
    
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    
	TIM_Cmd(TIM2, ENABLE);
}
 
void TIM3_PWM_Init(void)
{
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;// ??????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);							
 
	TIM_InternalClockConfig(TIM3);
 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=100-1; 
	TIM_TimeBaseInitStruct.TIM_Prescaler=720-1; 
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct); 
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1; 
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High; 
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable; 
	TIM_OCInitStruct.TIM_Pulse=0; 
	//ARR=100-1,PSC=720-1,CCR=50????????1KHz,????50%?PWM??
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);
	TIM_ARRPreloadConfig(TIM3,ENABLE);								  
	TIM_CtrlPWMOutputs(TIM3,ENABLE);								 
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  				 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);				 	
 
	TIM_Cmd(TIM3,ENABLE);
}

void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM3,Compare);
	TIM_SetCompare2(TIM2,Compare);
}

void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM3,Compare);

}

void PWM_SetCompare3(uint16_t Compare)
{
 
	TIM_SetCompare3(TIM2,Compare);
}

 
 

 


 

