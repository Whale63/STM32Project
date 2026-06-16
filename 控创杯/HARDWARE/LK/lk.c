#include "lk.h"
#include "sys.h"
#include "delay.h"
extern int sensor[4];//引用主函数main定义的数组，才能在本文件内使用sensor[x]该变量

int error=0;//小车的位置偏移量 误差(error),位置偏移越大，误差越大，偏移越小，误差越小

int a=0;//小车基础速度的标志变量，a越小时，基础速度越大

int posture;//红外传回，控制轮子运动状态

void hongwai_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA的时钟
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能GPIOB的时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能复用功能的时钟
	
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//IO管脚模式配置为浮空输入，这样就能获取传感器传回来的数字信号(高低电平)
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);//PA4,PA5,PA6,PA7管脚的初始化
	
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入模式
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB,&GPIO_InitStructure);//PB0,PB1,PB3,PB4,PB5管脚的初始化
	  
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出模式
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB,&GPIO_InitStructure);//PB5,PB6管脚的初始化，TB6612电机驱动板的使能端
	
	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//关闭STM32f103c8t6的JTAGD功能，使PB3和PB4用作普通的IO管脚//必须开启复用功能的时钟才能关闭该功能
}

void read_sensor(void)//红外传感器识别到黑线返回数字信号低电平0，未识别到黑线返回高电平1
{
	      /*将位置从最左按顺序到最右的传感器返回的数字信号依次存入数组sensor[0至3]里*/
				sensor[0]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);//左一pa5
				sensor[1]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);//左二pa6
				sensor[2]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);//右二pb3
				sensor[3]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);//右一pb4
				

	      if((sensor[0]==1)&&(sensor[1]==0&&sensor[2]==0)&&(sensor[3]==1))
				{	/*识别到黑线在中间*/	
				  error=0;a=0;
					posture=0;
				}
								
				else if((sensor[0]==1)&&(sensor[0]==0)&&(sensor[0]==1)&&(sensor[3]==1))
				{/*小车位置有点偏右*/
					error=-1;a=3;//误差为-1，舵机和轮子差速进行微小控制  //a=3,小车减速
					posture=1;
				}
				
				else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==1))
				{/*小车位置有点偏左*/
					error=1;a=3;//误差为1，舵机和轮子差速进行微小控制  //a=3,小车减速
					posture=2;
				}
				
										
				else if((sensor[0]==1)&&(sensor[0]==0)&&(sensor[0]==1)&&(sensor[3]==1))
				{/*小车位置偏右*/
					error=-8;a=6;//误差为-8，舵机和轮子差速进行微小控制  //a=6,小车减速厉害
					posture=1;
				}
				
				else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==1))
				{/*小车位置偏左*/
					error=8;a=6;//误差为8，舵机和轮子差速进行微小控制  //a=6,小车减速厉害
					posture=2
					;
				}
				

       
}
