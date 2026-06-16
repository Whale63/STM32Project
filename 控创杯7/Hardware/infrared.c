#include "stm32f10x.h"                  // Device header
#include "pwm.h"
#include "Delay.h"
#include "ultrasonic.h"
#include "OLED.h"

#define HIGH 400
#define COMMON 300
#define MEDIUM 250
#define LOW 200
#define WEAK 100

//int Buzzer_Init(void)
//{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

//	GPIO_Init(GPIOA,&GPIO_InitStructure);

//}



int duty=600;
int dutyB=600;
int dutyA=600;
int flag=-1;

int status=0;
int get_sensor_status() 
{
		
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0)
	{
	  status=0;
	}
	else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1)	
	{
	  status=1;
	}			
		return status;
}
	
int counter()
{
	int f1,f2;
	f1=f2=0;
	f1=get_sensor_status();
	Delay_ms(500);
	f2=get_sensor_status();
	if(f1!=f2)
	{
		flag++;
	}

	OLED_Printf(0, 20, OLED_6X8,"flag=%d",flag);
	OLED_Update();
	
	
  return 0;
}
   

void IR_Posture_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIOB_InitStructure;
	GPIOB_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//to gain digital signal back
	GPIOB_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIOB_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOB_InitStructure);
	
	GPIO_InitTypeDef GPIOA_InitStructure;
	GPIOA_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//to gain digital signal back
	GPIOA_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIOA_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOA_InitStructure);

}

int IR_Posture_distinction(void)//if the ir sensor reads LINES,it gives digital output '0',else it returns '1'
{
	IR_Posture_Init();
	
	int posture=0;
	int sensor[8]={0,0,0,0,0,0,0,0};

	sensor[0]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12);//X1 PB12 
	sensor[1]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);//X2 PB13
	sensor[2]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);//X3 PB14
	sensor[3]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);//X4 PB15
	sensor[4]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);//X5 PA8 
	sensor[5]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9);//X6 PA9
	sensor[6]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10);//X7 PA10
	sensor[7]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11);//X8 PA11


//	if((sensor[0]==1)&&(sensor[1]==1&&sensor[2]==1)&&(sensor[3]==1))//this bar is to pass the crossing gently
//		{		
//			posture=3;
//			PWM_SetCompare(70);
//		}
	if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)&&(sensor[7]==1))//if the posture is correct
		{		
			posture=0;//0 is ok
			PWM_SetCompare(duty=HIGH);

		}	
	else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)&&(sensor[7]==1))//if the posture is correct
		{		
			posture=0;//0 is ok
			PWM_SetCompare(duty=HIGH);

		}
	else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)&&(sensor[7]==1))
		{
			posture=2;//this status is a little left
			PWM_SetCompareB(dutyB=COMMON);
			PWM_SetCompareA(dutyA=COMMON);
		}	
	else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)&&(sensor[7]==1))
		{
			posture=2;//2 means a little bit left
			PWM_SetCompareB(dutyB=COMMON);
			PWM_SetCompareA(dutyA=LOW);
		}	
	else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)&&(sensor[6]==1)&&(sensor[7]==1))
		{
			posture=22;//22 means  left
			PWM_SetCompareB(dutyB=LOW);
			PWM_SetCompareA(dutyA=LOW);
		}
	else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)&&(sensor[7]==1))
		{
			posture=22;//22 means  left
			PWM_SetCompareB(dutyB=COMMON);
			PWM_SetCompareA(dutyA=COMMON);
		}
	else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)&&(sensor[6]==1)&&(sensor[7]==1))
		{
			posture=222;//22 means  left
			PWM_SetCompareB(dutyB=MEDIUM);
			PWM_SetCompareA(dutyA=MEDIUM);
		}
	else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==1)&&(sensor[7]==1))
		{
			posture=222;//22 means  left
			PWM_SetCompareB(dutyB=MEDIUM);
			PWM_SetCompareA(dutyA=MEDIUM);
		}
	else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)&&(sensor[6]==1)&&(sensor[7]==1))
		{
			posture=2222;//22 means  left
			PWM_SetCompareB(dutyB=MEDIUM);
			PWM_SetCompareA(dutyA=MEDIUM);
		}	
	else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==1)&&(sensor[7]==1))
		{
			posture=2222;//22 means  left
			PWM_SetCompareB(dutyB=MEDIUM);
			PWM_SetCompareA(dutyA=MEDIUM);
		}	
	else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==1))
		{
			posture=2222;//222 means  left
			PWM_SetCompareB(dutyB=MEDIUM);
			PWM_SetCompareA(dutyA=LOW);
		}
	else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==1))
		{
			posture=2222;//222 means  left
			PWM_SetCompareB(dutyB=MEDIUM);
			PWM_SetCompareA(dutyA=MEDIUM);
		}
	else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==0))
		{
			posture=2222;//2222 means very left
			PWM_SetCompareB(dutyB=MEDIUM);
			PWM_SetCompareA(dutyA=MEDIUM);
		}
	else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==0))
		{
			posture=2222;//2222 means very left
			PWM_SetCompareB(dutyB=MEDIUM);
			PWM_SetCompareA(dutyA=MEDIUM);
		}
	else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==0)&&(sensor[7]==0))
		{
			posture=2222;//2222 means very left
			PWM_SetCompareB(dutyB=MEDIUM);
			PWM_SetCompareA(dutyA=MEDIUM);
		}
	else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==1))
		{
			posture=2222;//2222 means very left
			PWM_SetCompareB(dutyB=MEDIUM);
			PWM_SetCompareA(dutyA=MEDIUM);
		}

	else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)&&(sensor[7]==1))//if the posture is correct
		{		
			posture=10;//10 is  blank going
			PWM_SetCompare(duty=COMMON);
		}





//	else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)&&(sensor[6]==1)&&(sensor[7]==1))
//		{
//			posture=222;//2 means a little bit left
//			PWM_SetCompareB(dutyB=75);
//			PWM_SetCompareA(dutyA=30);
//		}

		
//	else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)&&(sensor[7]==0))
//		{
//			posture=222;//222 means very left
//			PWM_SetCompareB(dutyB=65);
//			PWM_SetCompareA(dutyA=15);
//		}

	return posture;

}
