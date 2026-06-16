#include "stm32f10x.h"                  // Device header
#include "pwm.h" 
#include "Delay.h"


void Wheels_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//config PB1,2,10,11 as front wheels'control
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//configPA3,4,5,6,as back wheels'control
//	
	Pwm_Init();//?
	
}

extern int duty,dutyB,dutyA;

void forward(void)
{

		/*front*/
	  GPIO_ResetBits(GPIOB,GPIO_Pin_11);//BIN2
		GPIO_SetBits(GPIOB,GPIO_Pin_10);//BIN1
		GPIO_ResetBits(GPIOB,GPIO_Pin_2);//AIN1
		GPIO_SetBits(GPIOB,GPIO_Pin_1);//AIN2

		/*back*/
		GPIO_SetBits(GPIOA,GPIO_Pin_4);//CIN2
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);//CIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_5);//DIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);//DIN2		
		PWM_SetCompare(duty);
//			PWM_SetCompareB(duty+135);
//		PWM_SetCompareA(duty);
}
	
//void turn(void)
//{

//		/*front*/
//	  GPIO_ResetBits(GPIOB,GPIO_Pin_11);//BIN2
//		GPIO_SetBits(GPIOB,GPIO_Pin_10);//BIN1
//		GPIO_ResetBits(GPIOB,GPIO_Pin_2);//AIN1
//		GPIO_SetBits(GPIOB,GPIO_Pin_1);//AIN2

////		Delay_ms(300);
////		PWM_SetCompare(0);

////		/*back*/
//		GPIO_ResetBits(GPIOA,GPIO_Pin_4);//CIN2
//		GPIO_SetBits(GPIOA,GPIO_Pin_3);//CIN1
//		GPIO_SetBits(GPIOA,GPIO_Pin_5);//DIN1
//		GPIO_ResetBits(GPIOA,GPIO_Pin_0);//DIN2		
//		PWM_SetCompareB(dutyB);
//		PWM_SetCompareA(dutyA);
//}

void stop(void)
{

		/*front*/
//	  GPIO_ResetBits(GPIOB,GPIO_Pin_11);//BIN2
//		GPIO_SetBits(GPIOB,GPIO_Pin_10);//BIN1
//		GPIO_ResetBits(GPIOB,GPIO_Pin_2);//AIN1
//		GPIO_SetBits(GPIOB,GPIO_Pin_1);//AIN2
			PWM_SetCompare(0);
}

void left(void)//A goes ahead,B goes against
{

		/*front*/
	  GPIO_SetBits(GPIOB,GPIO_Pin_11);//BIN2
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//BIN1
		GPIO_ResetBits(GPIOB,GPIO_Pin_2);//AIN1
		GPIO_SetBits(GPIOB,GPIO_Pin_1);//AIN2
		
		/*back*/
		GPIO_SetBits(GPIOA,GPIO_Pin_4);//CIN2
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);//CIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);//DIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_0);//DIN2
		PWM_SetCompareB(dutyB);
		PWM_SetCompareA(dutyA);
}
void right(void)//A goes back,B goes ahead 
{

		/*front*/
	  GPIO_ResetBits(GPIOB,GPIO_Pin_11);//BIN2
		GPIO_SetBits(GPIOB,GPIO_Pin_10);//BIN1
		GPIO_SetBits(GPIOB,GPIO_Pin_2);//AIN1
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);//AIN2

		/*back*/
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);//CIN2
		GPIO_SetBits(GPIOA,GPIO_Pin_3);//CIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_5);//DIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);//DIN2		
		PWM_SetCompareB(dutyB);
		PWM_SetCompareA(dutyA);
}
//void Leftdrift(void)//A front,B back wheels goes forward while B front and A back wheels goes  against
//{
//	
//		/*front*/
//	  GPIO_ResetBits(GPIOB,GPIO_Pin_11);//BIN2
//		GPIO_SetBits(GPIOB,GPIO_Pin_10);//BIN1
//		GPIO_SetBits(GPIOB,GPIO_Pin_2);//AIN1
//		GPIO_ResetBits(GPIOB,GPIO_Pin_1);//AIN2
//		/*back*/
//		GPIO_SetBits(GPIOA,GPIO_Pin_11);//AIN2
//		GPIO_ResetBits(GPIOA,GPIO_Pin_10);//AIN1
//		GPIO_SetBits(GPIOA,GPIO_Pin_0);//BIN1
//		GPIO_ResetBits(GPIOA,GPIO_Pin_1);//BIN2
//}
//void Rightdrift(void)
//{
//	
//		/*front*/
//	  GPIO_SetBits(GPIOB,GPIO_Pin_11);//BIN2
//		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//BIN1
//		GPIO_ResetBits(GPIOB,GPIO_Pin_2);//AIN1
//		GPIO_SetBits(GPIOB,GPIO_Pin_1);//AIN2
//		/*back*/
//		GPIO_ResetBits(GPIOA,GPIO_Pin_11);//AIN2
//		GPIO_SetBits(GPIOA,GPIO_Pin_10);//AIN1
//		GPIO_ResetBits(GPIOA,GPIO_Pin_0);//BIN1
//		GPIO_SetBits(GPIOA,GPIO_Pin_1);//BIN2
//}

