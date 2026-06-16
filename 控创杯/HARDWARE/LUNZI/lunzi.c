#include "lunzi.h"
#include "stm32f10x.h"
#include "pwm.h"


void lunzi_Init(void)//对相应的IO口进行初始化,PA0-3
{

	  GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA的时钟
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能GPIOB的时钟
	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//输出模式为推挽输出，电平可高可低
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_7;//PA0-3管脚IO口//2换为4//PA7为后电机控制脚
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//管脚传输速度
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//输出模式为推挽输出，电平可高可低
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;//PB0-2管脚IO口
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//管脚传输速度
	  GPIO_Init(GPIOB,&GPIO_InitStructure);
		TIM2_PWM_Init(7199,0);
		TIM4_PWM_Init(7199,0);
}

void stop(void)//小车两个电机反转，因为越过终点线时，单纯停止电机工作，小车会因为惯性停不下来，所以短时间的反转，能抵消惯性，从而使小车迅速停下来
{
	  /*四个管脚设置不同的电平(1为高电平0为低电平)，作为TB6612的逻辑输入，用以控制电机转动状态。 */
	  /*打个比方，四个管脚IO分别设置成0 1 0 1，电机反转，那么反过来设置成1 0 1 0时，电机正转*/
	

		/*前轮*/
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);//PA0低电平   0//AIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_1);//PA1高电平	     1//AIN2
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PA4低电平	   0//BIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_3);//PA3高电平     1//BIN2
		/*后轮*/
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);//PA7低电平   0//AIN2
		GPIO_SetBits(GPIOA,GPIO_Pin_1);//PB0高电平	     1//AIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PB1低电平	   0//BIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_3);//PB2高电平      1//BIN2
}
void forward(void)//小车两个电机正转
{

		/*前轮*/
	  GPIO_SetBits(GPIOA,GPIO_Pin_0);//PA0高电平	     1//AIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);//PA1低电平   0//AIN2
		GPIO_SetBits(GPIOA,GPIO_Pin_2);//PA4高电平	     1//BIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);//PA3低电平   0//BIN2
		/*后轮*/
		GPIO_SetBits(GPIOA,GPIO_Pin_0);//PA7高电平     0//AIN2
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);//PB0低电平	   1//AIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_2);//PB1高电平	     0//BIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);//PB2低电平   1//BIN2
}
void left(void)//小车前后电机1正转2反转,左旋转
{
	
		/*前轮*/
		GPIO_SetBits(GPIOA,GPIO_Pin_0);//PA0高电平     1//AIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);//PA1低电平	   0//AIN2
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PA4低电平	   0//BIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_3);//PA3高电平     1//BIN2
		/*后轮*/
		GPIO_SetBits(GPIOA,GPIO_Pin_0);//PA7高电平   	 1//AIN2
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);//PB0低电平	   0//AIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PB1低电平	   0//BIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_3);//PB2高电平     1//BIN2
}
void right(void)//小车前后电机1反转2正转，右旋转
{
	
		/*前轮*/
		GPIO_SetBits(GPIOA,GPIO_Pin_0);//PA0低电平     0//AIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);//PA1高电平	   1//AIN2
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PA4高电平	   1//BIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_3);//PA3低电平     0//BIN2
		/*后轮*/
		GPIO_SetBits(GPIOA,GPIO_Pin_0);//PA7低电平     0//AIN2
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);//PB0高电平	   1//AIN1
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PB1高电平	   1//BIN1
		GPIO_SetBits(GPIOA,GPIO_Pin_3);//PB2低电平     0//BIN2
}






