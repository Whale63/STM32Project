#include "stm32f10x.h"                  // Device header

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启总线时钟
	TIM_InternalClockConfig(TIM2);//选择时基单元时钟，选择了tim2时基单元的内部时钟；上电后默认选择了内置时钟，所以此函数可省略
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrucyure;
	TIM_TimeBaseInitStrucyure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStrucyure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStrucyure.TIM_Period=10000-1;
	TIM_TimeBaseInitStrucyure.TIM_Prescaler=7200-1;
	//TIM_TimeBaseInitStrucyure.TIM_RepetitionCounter=;只有高级定时器才有，通用
	
	TIM_TimeBaseInit（TIM2,&TIM_TimeBaseInitStrucyure);//配置时基单元
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能更新中断，开启了中断到nvic的路径
	
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//nvic优先级分组
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=;
	NVIC_InitStructure.NVIC_IRQChannelCmd=;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=;
}