#include "stm32f10x.h"
#include "pwm.h"
#include "infrared.h"
#include "Delay.h"
#include "wheels.h"
#include "OLED.h"
#include "key.h"

//////////////////////////////////////////////////////////////////////////////////	 
//未经作者许可，不得用于其它任何用途
//STM32f103c8t6开发板
//作者：Whale Zhang  QQ:3056512049
//修改：WhaleZhang 13939381056
//修改日期:2024/06/23
//版本：V5.0
//版权所有，盗版必究。
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	



	extern int flag;
	int mode=0;
//	int*p=&mode;
	int flag_H=0;	
	
int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	TIM4_Pwm_Init();
	IR_Posture_Init();
	Wheels_Init();
	OLED_Init();
//	TIM2_Init();
//	Ultrasonic_Init();
	
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
 
	while (1)
{
		

//		if(Key_GetNum()==1)

//		{
//			mode++;
//			if(mode>4)
//				{
//					mode = 0;
//				}
//		}
//		if(Key_GetNum()==2){flag_H = mode;flag=0;OLED_Printf(0, 40, OLED_6X8,"ok%d",mode);OLED_Update();Delay_ms(100);}
//		OLED_Printf(0, 20, OLED_6X8,"mode:%d",mode);
//		OLED_Update();
//		if(flag_H==0){GPIO_ResetBits(GPIOB,GPIO_Pin_0);}//stby=0
//		
//		if(flag_H==1)
//		{
//			if((IR_Posture_distinction()==0||IR_Posture_distinction()==10)&&flag==0)
//			{
//	//			OLED_ShowString(0, 0, "forward", OLED_6X8);
//				GPIO_SetBits(GPIOB,GPIO_Pin_0);
//				forward();
//				Delay_ms(300);
//				
//			}
//			counter();
//			if(flag>=1)
//			{
//				stop();

//			}
		
//		}

//		if(flag_H==2)
//		{
			if(flag<4)
		{
		if(IR_Posture_distinction()==0)
		{
			OLED_ShowString(0, 0, "forward", OLED_6X8);
			OLED_Update();
		  forward();
		}
		else if(IR_Posture_distinction()==10)
		{
			OLED_ShowString(0, 0, "forward", OLED_6X8);
			OLED_Update();
		  forward();
		}
//		else if(IR_Posture_distinction()==11)//11 means left
//		{
////			OLED_Clear();
//			OLED_ShowString(0, 0, "left", OLED_6X8);
//			OLED_Update();
//			forward();
//		}
		else if(IR_Posture_distinction()==22)//22 means right
		{
//			OLED_Clear();
			OLED_ShowString(0, 0, "right", OLED_6X8);	
			OLED_Update();
			forward();
		}
//		else if(IR_Posture_distinction()==111)//111 means very left
//		{	
//		//			OLED_Clear();
//			OLED_ShowString(0, 0, "left", OLED_6X8);	
//			OLED_Update();
//			forward();
//		}
		else if(IR_Posture_distinction()==222)//222 means very right
		{
//			OLED_Clear();
			OLED_ShowString(0, 0, "right", OLED_6X8);		
			OLED_Update();
			forward();
		}
//		else if(IR_Posture_distinction()==1111)//1111 means very left
//		{	
////			OLED_Clear();
//			OLED_ShowString(0, 0, "left", OLED_6X8);	
//			OLED_Update();
//			forward();
//		}
		else if(IR_Posture_distinction()==2222)//2222 means very right
		{
//			OLED_Clear();
			OLED_ShowString(0, 0, "right", OLED_6X8);		
			OLED_Update();
			forward();
		}

			
	
		counter();
		
		if((IR_Posture_distinction()==10)&&(flag%2==0)&&(flag!=0))
			{
				right();
				Delay_ms(500);

			}
		}
		if(flag>=4)
			{
				stop();

			}
		
//		}
//		
//		if(flag_H==3)
//		{
//			if(flag<4)
//			{
//				if(IR_Posture_distinction()==0)
//				{
//					OLED_ShowString(0, 0, "forward", OLED_6X8);	
//					OLED_Update();
//					forward();
//				}
//				if(IR_Posture_distinction()==10)
//				{
//					if(flag%2==0)//flag为偶
//					{
//						Delay_ms(300);
//						right();
//						Delay_s(1);
//						forward();
//						Delay_s(6);
//						
//					}	
//					if(flag%2==1)
//					{
//						Delay_ms(300);
//						left();
//						Delay_s(1);
//						forward();
//						Delay_s(6);
//					}
//		//			OLED_ShowString(0, 0, "forward", OLED_6X8);
////					forward();
//				}
//				else if(IR_Posture_distinction()==11)//11 means left
//				{
////					OLED_Clear();
//					OLED_ShowString(0, 0, "left", OLED_6X8);
//					OLED_Update();
//					forward();
//				}
//				else if(IR_Posture_distinction()==22)//22 means right
//				{
////					OLED_Clear();
//					OLED_ShowString(0, 0, "right", OLED_6X8);		
//					OLED_Update();
//					forward();
//				}
//				else if(IR_Posture_distinction()==111)//111 means very left
//				{	
////					OLED_Clear();
//					OLED_ShowString(0, 0, "left", OLED_6X8);
//					OLED_Update();
//					forward();
//				}
//				else if(IR_Posture_distinction()==222)//222 means very right
//				{
////					OLED_Clear();
//					OLED_ShowString(0, 0, "right", OLED_6X8);	
//					OLED_Update();
//					forward();
//				}
		//		else if(IR_Posture_distinction()==1111)//1111 means very left
		//		{	
		////			OLED_Clear();
		//			OLED_ShowString(0, 0, "left", OLED_6X8);	
		//			OLED_Update();
		//			forward();
		//		}
		//		else if(IR_Posture_distinction()==2222)//2222 means very right
		//		{
		////			OLED_Clear();
		//			OLED_ShowString(0, 0, "right", OLED_6X8);		
		//			OLED_Update();
		//			forward();
		//		}
//					Delay_ms(600);
//					counter();
//				}
//			counter();
//			
//		}


//		
//		if(flag_H==4)
//		{
//			if(flag<16)
//			{
//				if(IR_Posture_distinction()==0)
//				{
//					OLED_ShowString(0, 0, "forward", OLED_6X8);	
//					OLED_Update();
//					forward();
//				}
//				if(IR_Posture_distinction()==10)
//				{
//					if(flag%2==0)//flag为偶
//					{
//						Delay_ms(300);
//						right();
//						Delay_s(1);
//						forward();
//						Delay_s(6);
//						
//					}	
//					if(flag%2==1)
//					{
//						Delay_ms(300);
//						left();
//						Delay_s(1);
//						forward();
//						Delay_s(6);
//					}
//		//			OLED_ShowString(0, 0, "forward", OLED_6X8);
////					forward();
//				}
//				else if(IR_Posture_distinction()==11)//11 means left
//				{
////					OLED_Clear();
//					OLED_ShowString(0, 0, "left", OLED_6X8);
//					OLED_Update();
//					forward();
//				}
//				else if(IR_Posture_distinction()==22)//22 means right
//				{
////					OLED_Clear();
//					OLED_ShowString(0, 0, "right", OLED_6X8);	
//					OLED_Update();
//					forward();
//				}
//				else if(IR_Posture_distinction()==111)//111 means very left
//				{	
////					OLED_Clear();
//					OLED_ShowString(0, 0, "left", OLED_6X8);	
//					OLED_Update();
//					forward();
//				}
//				else if(IR_Posture_distinction()==222)//222 means very right
//				{
////					OLED_Clear();
//					OLED_ShowString(0, 0, "right", OLED_6X8);		
//					OLED_Update();
//					forward();
//				}
		//		else if(IR_Posture_distinction()==1111)//1111 means very left
		//		{	
		////			OLED_Clear();
		//			OLED_ShowString(0, 0, "left", OLED_6X8);	
		//			OLED_Update();
		//			forward();
		//		}
		//		else if(IR_Posture_distinction()==2222)//2222 means very right
		//		{
		////			OLED_Clear();
		//			OLED_ShowString(0, 0, "right", OLED_6X8);		
		//			OLED_Update();
		//			forward();
		//		}
//					Delay_ms(600);
//					counter();
//				}
//			counter();
//		}
		
//	}
}

}
