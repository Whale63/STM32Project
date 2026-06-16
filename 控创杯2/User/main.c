#include "stm32f10x.h"
#include "pwm.h"
#include "Delay.h"
#include "infrared.h"
#include "wheels.h"
#include "OLED.h"

#define delay 0
int main()
{
	
	TIM4_Pwm_Init();
	IR_Posture_Init();
	Wheels_Init();
	OLED_Init();
	
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
	
	
	while(1)
	{

		if(IR_Posture_distinction()==3)
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
			GPIO_SetBits(GPIOA,GPIO_Pin_13);

			OLED_ShowString(1,1,"forward");
		  forward();
		}
		if(IR_Posture_distinction()==0)
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
			GPIO_SetBits(GPIOA,GPIO_Pin_13);

			OLED_ShowString(1,1,"forward");
		  forward();
		}
		else if(IR_Posture_distinction()==1)//1 means left
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_0);//front STBY
			GPIO_SetBits(GPIOA,GPIO_Pin_13);//back STBY
			
			OLED_Clear();
			OLED_ShowString(1,1,"left");
//			Delay_ms(delay);
			left();
			
		}
		else if(IR_Posture_distinction()==2)//2 means right
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
			GPIO_SetBits(GPIOA,GPIO_Pin_13);
			
			OLED_Clear();
			OLED_ShowString(1,1,"right");
//			Delay_ms(delay);
			right();
			
		}
		else if(IR_Posture_distinction()==11)//1 means left
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_0);//front STBY
			GPIO_SetBits(GPIOA,GPIO_Pin_13);//back STBY
			
			OLED_Clear();
			OLED_ShowString(1,1,"left");
//			Delay_ms(delay);
			left();
			
		}
		else if(IR_Posture_distinction()==22)//2 means right
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
			GPIO_SetBits(GPIOA,GPIO_Pin_13);
			
			OLED_Clear();
			OLED_ShowString(1,1,"right");
//			Delay_ms(delay);
			right();
			
		}
		else if(IR_Posture_distinction()==111)//1 means left
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_0);//front STBY
			GPIO_SetBits(GPIOA,GPIO_Pin_13);//back STBY
			
			OLED_Clear();
			OLED_ShowString(1,1,"left");
			left();
			Delay_s(delay);
		}
		else if(IR_Posture_distinction()==222)//2 means right
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
			GPIO_SetBits(GPIOA,GPIO_Pin_13);
			
			OLED_Clear();
			OLED_ShowString(1,1,"right");
			right();
			Delay_s(delay);
		}
 
	
	}
}

