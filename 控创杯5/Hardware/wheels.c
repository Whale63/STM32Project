#include "stm32f10x.h"                  // Device header
#include "pwm.h"                  


void Wheels_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//config PB1,2,10,11 as front wheels'control,PB5and PA12 as back wheels'control
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//configPA3,4,PA12,as one of back wheels'control
	
	TIM4_Pwm_Init();//?
	
}

void forward(void)
{

		/*front*/
	  GPIO_ResetBits(GPIOB,GPIO_Pin_11);//BIN2
		GPIO_SetBits(GPIOB,GPIO_Pin_10);//BIN1
		GPIO_ResetBits(GPIOB,GPIO_Pin_2);//AIN1
		GPIO_SetBits(GPIOB,GPIO_Pin_1);//AIN2
		/*back*/
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);//AIN2
		GPIO_SetBits(GPIOA,GPIO_Pin_10);//AIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_0);//BIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);//BIN2
}
void left(void)//A goes ahead,B goes against
{

		/*front*/
	  GPIO_SetBits(GPIOB,GPIO_Pin_11);//BIN2
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//BIN1
		GPIO_ResetBits(GPIOB,GPIO_Pin_2);//AIN1
		GPIO_SetBits(GPIOB,GPIO_Pin_1);//AIN2
		/*back*/
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);//AIN2
		GPIO_SetBits(GPIOA,GPIO_Pin_10);//AIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);//BIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_1);//BIN2
}
void right(void)//A goes back,B goes ahead 
{

		/*front*/
	  GPIO_ResetBits(GPIOB,GPIO_Pin_11);//BIN2
		GPIO_SetBits(GPIOB,GPIO_Pin_10);//BIN1
		GPIO_SetBits(GPIOB,GPIO_Pin_2);//AIN1
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);//AIN2
		/*back*/
		GPIO_SetBits(GPIOA,GPIO_Pin_11);//AIN2
		GPIO_ResetBits(GPIOA,GPIO_Pin_10);//AIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_0);//BIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);//BIN2
}
void Leftdrift(void)//A front,B back wheels goes forward while B front and A back wheels goes  against
{
	
		/*front*/
	  GPIO_ResetBits(GPIOB,GPIO_Pin_11);//BIN2
		GPIO_SetBits(GPIOB,GPIO_Pin_10);//BIN1
		GPIO_SetBits(GPIOB,GPIO_Pin_2);//AIN1
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);//AIN2
		/*back*/
		GPIO_SetBits(GPIOA,GPIO_Pin_11);//AIN2
		GPIO_ResetBits(GPIOA,GPIO_Pin_10);//AIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_0);//BIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);//BIN2
}
void Rightdrift(void)
{
	
		/*front*/
	  GPIO_SetBits(GPIOB,GPIO_Pin_11);//BIN2
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//BIN1
		GPIO_ResetBits(GPIOB,GPIO_Pin_2);//AIN1
		GPIO_SetBits(GPIOB,GPIO_Pin_1);//AIN2
		/*back*/
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);//AIN2
		GPIO_SetBits(GPIOA,GPIO_Pin_10);//AIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);//BIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_1);//BIN2
}
