#include "stm32f10x.h"
#include "pwm.h"
#include "infrared.h"
#include "Delay.h"
#include "wheels.h"
#include "OLED.h"
#include "ultrasonic.h"

#define delay 0
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
	
	
	while(1)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
		GPIO_SetBits(GPIOA,GPIO_Pin_13);

			switch(IR_Posture_distinction())
			{
				case 0:
				{
						OLED_ShowString(1,1,"forward");
						forward();
					break;
				}
				case 1:
				{
						OLED_Clear();
						OLED_ShowString(1,1,"left");
						left();
					break;
				}
				case 2:
				{
						OLED_Clear();
						OLED_ShowString(1,1,"right");
						right();
					break;
				}
				case 11:
				{
						OLED_Clear();
						OLED_ShowString(1,1,"left");
						left();
					break;
				}
				case 22:
				{
						OLED_Clear();
						OLED_ShowString(1,1,"right");
						right();	
					break;
				}
				case 111:
				{
						OLED_Clear();
						OLED_ShowString(1,1,"left");
						left();
						Delay_s(delay);
					break;
				}
				case 222:
				{
						OLED_Clear();
						OLED_ShowString(1,1,"right");
						right();
						Delay_s(delay);
					break;
				}
				case 6:
				{
					  OLED_Clear();
						OLED_ShowString(1,1,"auto");
						leftfloat();
						Delay_s(2);
						forward();
						Delay_s(2);
						right();
						Delay_s(1);
						forward();
						Delay_s(2);
						Delay_ms(800);
					break;
				}
				default:break ;
			}
//		if(IR_Posture_distinction()==3)
//		{
//			GPIO_SetBits(GPIOB,GPIO_Pin_0);
//			GPIO_SetBits(GPIOA,GPIO_Pin_13);

//			OLED_ShowString(1,1,"forward");
//		  forward();
//		}
//		else if(IR_Posture_distinction()==0)
//		{
//			GPIO_SetBits(GPIOB,GPIO_Pin_0);
//			GPIO_SetBits(GPIOA,GPIO_Pin_13);

//			OLED_ShowString(1,1,"forward");
//		  forward();
//		}
//		else if(IR_Posture_distinction()==1)//1 means left
//		{
//			GPIO_SetBits(GPIOB,GPIO_Pin_0);//front STBY
//			GPIO_SetBits(GPIOA,GPIO_Pin_13);//back STBY
//			
//			OLED_Clear();
//			OLED_ShowString(1,1,"left");
////			Delay_ms(delay);
//			left();
//			
//		}
//		else if(IR_Posture_distinction()==2)//2 means right
//		{
//			GPIO_SetBits(GPIOB,GPIO_Pin_0);
//			GPIO_SetBits(GPIOA,GPIO_Pin_13);
//			
//			OLED_Clear();
//			OLED_ShowString(1,1,"right");
////			Delay_ms(delay);
//			right();
//			
//		}
//		else if(IR_Posture_distinction()==11)//1 means left
//		{
//			GPIO_SetBits(GPIOB,GPIO_Pin_0);//front STBY
//			GPIO_SetBits(GPIOA,GPIO_Pin_13);//back STBY
//			
//			OLED_Clear();
//			OLED_ShowString(1,1,"left");
////			Delay_ms(delay);
//			left();
//			
//		}
//		else if(IR_Posture_distinction()==22)//2 means right
//		{
//			GPIO_SetBits(GPIOB,GPIO_Pin_0);
//			GPIO_SetBits(GPIOA,GPIO_Pin_13);
//			
//			OLED_Clear();
//			OLED_ShowString(1,1,"right");
////			Delay_ms(delay);
//			right();
//			
//		}
//		else if(IR_Posture_distinction()==111)//1 means left
//		{
//			GPIO_SetBits(GPIOB,GPIO_Pin_0);//front STBY
//			GPIO_SetBits(GPIOA,GPIO_Pin_13);//back STBY
//			
//			OLED_Clear();
//			OLED_ShowString(1,1,"left");
//			left();
//			Delay_s(delay);
//		}
//		else if(IR_Posture_distinction()==222)//2 means right
//		{
//			GPIO_SetBits(GPIOB,GPIO_Pin_0);
//			GPIO_SetBits(GPIOA,GPIO_Pin_13);
//			
//			OLED_Clear();
//			OLED_ShowString(1,1,"right");
//			right();
//			Delay_s(delay);
//		}
// 
//	
//	}
	}
}
