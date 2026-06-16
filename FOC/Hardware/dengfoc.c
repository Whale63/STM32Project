//#include <math.h>
//#include "stm32f10x.h"
//#include "OLED.h"
//#include "Delay.h"
//#include "dengfoc.h"

//#define _constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))//宏定义实现的一个约束函数,用于限制amt的范围

//#define GPIO_Pin_0 pwmA//TIM2,PA0
//#define GPIO_Pin_6 pwmB//TIM3,PA6
//#define GPIO_Pin_6 pwmC//TIM4,PB6

//#define PI 3.14

//int arr=0;//arr=100-1时，pwm频率是10000hz
//int psc=720-1;
//int ccr=0;
//int frequency=0;

//float voltage_power_supply=12.6;
//float shaft_angle=0,open_loop_timestamp=0;
//float zero_electric_angle=0,Ualpha,Ubeta=0,Ua=0,Ub=0,Uc=0,dc_a=0,dc_b=0,dc_c=0;


//void TIM4_PwmC_Init(void)//pwmC
//{
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//不用寄存器输出，用片上外设PB输出，选复用，推挽较开漏电流更加有驱动能力 
//	GPIO_InitStructure.GPIO_Pin=pwmC;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	
//	
//	TIM_InternalClockConfig(TIM4);//Configures the TIM4 internal Clock
//	
//	TIM_TimeBaseInitTypeDef Tim_TimeBaseInitStructure;
//	Tim_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
//	Tim_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
//	Tim_TimeBaseInitStructure.TIM_Period=arr;//ARR value 100-1
//	Tim_TimeBaseInitStructure.TIM_Prescaler=psc;//PSC value 720-1 100khz
//	Tim_TimeBaseInitStructure.TIM_RepetitionCounter=0;
//	TIM_TimeBaseInit(TIM4,&Tim_TimeBaseInitStructure);//产生中断的时间为10us
//	
//	
//	TIM_OCInitTypeDef Tim_OCInitStructure;
//	
//	TIM_OCStructInit(&Tim_OCInitStructure);//结构体初始化，若结构体没有完整赋值，则最好执行此函数，给结构体所有成员都赋一个默认值避免初值不确定
//																				 

//	Tim_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
//	Tim_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//REFerence high effect
//	Tim_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
//	Tim_OCInitStructure.TIM_Pulse=ccr;//CCR 初值为零，下面用setcompare函数设置ccr值
//	
//	
//	TIM_OC1Init(TIM4,&Tim_OCInitStructure);//PB6

//	
////	TIM_ARRPreloadConfig(TIM4,ENABLE);
////	TIM_CtrlPWMOutputs(TIM4,ENABLE);//高级定时器用
////	TIM_OC1PreloadConfig(TIM4,ENABLE);
////	TIM_OC2PreloadConfig(TIM4,ENABLE);
////	TIM_OC3PreloadConfig(TIM4,ENABLE);
////	TIM_OC4PreloadConfig(TIM4,ENABLE);
//	
//	TIM_Cmd(TIM4,ENABLE);// Enables the TIM4 peripheral.
//	
//	
//}

//void TIM2_PwmA_Init(void)//pwmA
//{
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; 
//	GPIO_InitStructure.GPIO_Pin=pwmA;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	
//	TIM_InternalClockConfig(TIM2);
//	
//	TIM_TimeBaseInitTypeDef Tim_TimeBaseInitStructure;
//	Tim_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
//	Tim_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
//	Tim_TimeBaseInitStructure.TIM_Period=arr;
//	Tim_TimeBaseInitStructure.TIM_Prescaler=psc;
//	Tim_TimeBaseInitStructure.TIM_RepetitionCounter=0;
//	TIM_TimeBaseInit(TIM2,&Tim_TimeBaseInitStructure);
//	
//	
//	TIM_OCInitTypeDef Tim_OCInitStructure;
//													 
//	TIM_OC1Init(TIM2,&Tim_OCInitStructure);//PA0

//	
//	TIM_Cmd(TIM2,ENABLE);
//	
//	
//}

//void TIM3_PwmB_Init(void)//pwmB
//{
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; 
//	GPIO_InitStructure.GPIO_Pin=pwmB;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	
//	TIM_InternalClockConfig(TIM3);
//	
//	TIM_TimeBaseInitTypeDef Tim_TimeBaseInitStructure;
//	Tim_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
//	Tim_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
//	Tim_TimeBaseInitStructure.TIM_Period=arr;
//	Tim_TimeBaseInitStructure.TIM_Prescaler=psc;
//	Tim_TimeBaseInitStructure.TIM_RepetitionCounter=0;
//	TIM_TimeBaseInit(TIM3,&Tim_TimeBaseInitStructure);
//	
//	
//	TIM_OCInitTypeDef Tim_OCInitStructure;
//	
//	TIM_OC1Init(TIM3,&Tim_OCInitStructure);//PA6

//	
//	TIM_Cmd(TIM3,ENABLE);
//	
//	
//}

//void PWM_SetCompare1(ccr)
//{
//	TIM_SetCompare1(TIM2,ccr);
//	TIM_SetCompare1(TIM3,ccr);
//	TIM_SetCompare1(TIM4,ccr);
//}

//void Pwm_Initiation(frequency,ccr)//频率，占空比
//{
//	frequency=frequency;
//	ccr=ccr;
//	arr=frequency*(psc+1)/72000000;
//	
//	TIM4_PwmC_Init();
//	TIM2_PwmA_Init();
//	TIM3_PwmB_Init();
//	PWM_SetCompare1(ccr);
//	OLED_I2C_Init();
//	OLED_Clear();
//	OLED_ShowString(1,1,"pwm stand by");
//	Delay_s(1);
//	
//}


//// 电角度求解
//float _electricalAngle(float shaft_angle, int pole_pairs) //机械角度，极对数
//{
//  return (shaft_angle * pole_pairs);
//}

//// 归一化角度到 [0,2PI]
//float _normalizeAngle(float angle)
//{
//  float a = fmod(angle, 2*PI);   //取余运算用于归一化
//  return a >= 0 ? a : (a + 2*PI);  //防止角度过大溢出死机
//  
//}


//while(1)
//{


//}

	