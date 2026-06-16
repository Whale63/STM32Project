#include "stm32f10x.h"                  // Device header
#include "pwm.h"
#include "Delay.h"

#define delay1 0



void IR_Posture_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//to gain digital signal back
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

}

int IR_Posture_distinction(void)//if the ir sensor reads LINES,it gives digital output '0',else it returns '1'
{
	IR_Posture_Init();
	
	int posture;
	int sensor[4]={0,0,0,0};

	sensor[0]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12);//left  1 PB12 
	sensor[1]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);//left  2 PB13
	sensor[2]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);//right 1 PB14
	sensor[3]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);//right 2 PB15


	if((sensor[0]==1)&&(sensor[1]==1&&sensor[2]==1)&&(sensor[3]==1))//if the posture is correct
		{		
			posture=3;
			PWM_SetCompare(70);
//			Delay_ms(delay1);
		}
	if((sensor[0]==0)&&(sensor[1]==1&&sensor[2]==1)&&(sensor[3]==0))//if the posture is correct
		{		
			posture=0;
			PWM_SetCompare(80);
//			Delay_ms(delay1);
		}
	else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0))
		{
			posture=0;//1 means a little bit right
			PWM_SetCompare(80);
//			Delay_ms(delay1);
		}
	else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==0))
		{
			posture=0;//2 means a little bit right
			PWM_SetCompare(60);
//			Delay_ms(delay1);
		}
	else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0))
		{
			posture=11;//1 means very right
			PWM_SetCompare(50);
//			Delay_ms(delay1);
		}

	else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==1))
		{
			posture=22;//2 means very left
			PWM_SetCompare(50);
//			Delay_ms(delay1);
		}
	else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0))
		{
			posture=111;//1 means  right
			PWM_SetCompare(50);
		}
	else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1))
		{
			posture=222;//1 means  left
			PWM_SetCompare(50);
		}
		
	return posture;

}
	
