#include "stm32f10x.h"                  // Device header
#include "pwm.h"
#include "Delay.h"
#include "ultrasonic.h"


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


//	if((sensor[0]==1)&&(sensor[1]==1&&sensor[2]==1)&&(sensor[3]==1))//this bar is to pass the crossing gently
//		{		
//			posture=3;
//			PWM_SetCompare(70);
//		}
	if((sensor[0]==0)&&(sensor[1]==1&&sensor[2]==1)&&(sensor[3]==0)&&(Distance()==0))//if the posture is correct
		{		
			posture=0;
			PWM_SetCompare(80);
		}
	else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(Distance()==0))
		{
			posture=0;//0 is ok
			PWM_SetCompare(70);
		}
	else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==0)&&(Distance()==0))
		{
			posture=0;
			PWM_SetCompare(70);
		}
	else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0))
		{
			posture=11;//11 means a little bit right
			PWM_SetCompareB(20);
			PWM_SetCompareA(70);
		}

	else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==1))
		{
			posture=22;//22 means a little bit left
			PWM_SetCompareB(70);
			PWM_SetCompareA(20);
		}
	else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0))
		{
			posture=111;//111 means very right
			PWM_SetCompareB(10);
			PWM_SetCompareA(60);
		}
	else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1))
		{
			posture=222;//222 means very left
			PWM_SetCompareB(60);
			PWM_SetCompareA(10);
		}
	else if((sensor[0]==0)&&(sensor[1]==1&&sensor[2]==1)&&(sensor[3]==0)&&(Distance()==1))
		{		
			posture=6;//6 means block on the way, turn to AUTO mode
			PWM_SetCompare(60);
		}
	else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(Distance()==1))
		{
			posture=6;
			PWM_SetCompare(60);
		}
	else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==0)&&(Distance()==1))
		{
			posture=6;
			PWM_SetCompare(60);
		}
		
	return posture;

}
