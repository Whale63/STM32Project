#include "stm32f10x.h"
#include "pwm.h"
#include "infrared.h"
#include "Delay.h"
#include "wheels.h"
#include "OLED.h"
#include "ultrasonic.h"

//////////////////////////////////////////////////////////////////////////////////	 
//未经作者许可，不得用于其它任何用途
//STM32f103c8t6ka开发板
//作者：Whale Zhang  QQ:3056512049
//修改：WhaleZhang 13939381056
//修改日期:2024/06/23
//版本：V5.0
//版权所有，盗版必究。
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	


int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	TIM4_Pwm_Init();
	IR_Posture_Init();
	Wheels_Init();
	OLED_Init();
	TIM2_Init();
	Ultrasonic_Init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	GPIO_SetBits(GPIOA,GPIO_Pin_13);
	
	while(1)
	{
//		if(IR_Posture_distinction()==3)//this bar is to pass the crossing gently
//		{
//			GPIO_SetBits(GPIOB,GPIO_Pin_0);
//			GPIO_SetBits(GPIOA,GPIO_Pin_13);

//			OLED_ShowString(1,1,"forward");
//		  forward();
//		}
		if(IR_Posture_distinction()==0)
		{
			OLED_ShowString(1,1,"forward");
		  forward();
		}
		else if(IR_Posture_distinction()==11)//11 means left
		{
			OLED_Clear();
			OLED_ShowString(1,1,"left");
			forward();
		}
		else if(IR_Posture_distinction()==22)//22 means right
		{
			OLED_Clear();
			OLED_ShowString(1,1,"right");
			forward();
		}
		else if(IR_Posture_distinction()==111)//111 means very left
		{	
			OLED_Clear();
			OLED_ShowString(1,1,"left");
			forward();
		}
		else if(IR_Posture_distinction()==222)//222 means very right
		{
			OLED_Clear();
			OLED_ShowString(1,1,"right");
			forward();
		}
		else if(IR_Posture_distinction()==6)
		{
			OLED_Clear();
			OLED_ShowString(1,1,"auto");
			left();
			Delay_ms(700);
			forward();
			Delay_s(2);
			Delay_ms(100);
			right();
			Delay_s(1);
			Delay_ms(300);
			forward();
			Delay_s(2);
			Delay_ms(300);
		}
	}	
}
