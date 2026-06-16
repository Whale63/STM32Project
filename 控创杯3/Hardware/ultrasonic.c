#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

int Counter;
int CN1,CN2;
uint8_t number;

void TIM2_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_InternalClockConfig(TIM2);//use intenal clk,Configures the TIM2 internal Clock
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//no div
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65535;//arr
	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1;//psc
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); 
	
	
		NVIC_InitTypeDef TIM_NVIC;
    TIM_NVIC.NVIC_IRQChannel=TIM2_IRQn;                             //指定Tim2的中断通道
    TIM_NVIC.NVIC_IRQChannelCmd=ENABLE;
    TIM_NVIC.NVIC_IRQChannelPreemptionPriority=0;                   //抢占优先级
    TIM_NVIC.NVIC_IRQChannelSubPriority=1;                          //响应优先级
    NVIC_Init(&TIM_NVIC);
}

void TIM2_ON(void)
{
	TIM_Cmd(TIM2,ENABLE);
}

void TIM2_OFF(void)
{
	TIM_Cmd(TIM2,DISABLE);
}
void TIM2_IRQHandler(void){
    if(SET==TIM_GetITStatus(TIM2,TIM_FLAG_Update)){
        number++;                                   //每次中断将次数++
        TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
    }
}


//参数初始化

void Ultrasonic_Init(void)
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//脉冲触发端口 Trig=PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//回波接收端口 Echo=PA4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
	
	
	EXTI_InitTypeDef EXTI_InitStructure;
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI4_IRQHandler(void)
{
//	Delay_us(50);
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
	{	
		TIM2->CNT = 0;
		TIM2_ON();//开始计时
		CN1 = TIM_GetCounter(TIM2);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4));//PA4为高电平时一直循环下去
		CN2 = TIM_GetCounter(TIM2);
		TIM2_OFF();
//		Counter =CN2-CN1;//获得计数差
		Counter =TIM2->CNT;
				if(number){
						Counter = number*65535+Counter;
						number = 0;
				}
	}
			EXTI_ClearITPendingBit(EXTI_Line4);//清除标志位

}

void Ultrasonic_Start(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3);//A3置1大于10us
	Delay_us(15);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
//	Delay_us(100);

}

void Ultrasonic_Stop(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);//A3置1大于10us
}
                         
int Distance(void)
{
	int i=0,Sum=0,Dec=0;
	int CNT_Average;
	float Distance1;
//	Ultrasonic_Init();
	for(i=0;i<5;i++)//均值滤波
	{
		Ultrasonic_Start();
			Sum+=Counter;
	}
	
	Ultrasonic_Stop();
	CNT_Average=Sum/5;
	Distance1=CNT_Average* 0.017;//340m/s*deltaCN(or called Counter)*Tcounter/2,THE UNIT is cm
	Dec=(17*Sum/5)%100;//100取余得到小数点后值
	OLED_ShowNum(1,7,Distance1,6);
	OLED_ShowChar(1,14,'.');
	OLED_ShowNum(1,15,Dec,2);
	Delay_ms(100);//?
	Sum=0;//更新Sum
	if (Distance1<=20.0)
	{
	return 1;
	}
	else
		return 0;
}
