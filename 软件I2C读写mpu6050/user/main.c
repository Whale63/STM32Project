#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyI2C.h"
#include "MPU6050.h"


uint8_t KeyNum;

int main(void)
{
	OLED_Init();
	
	MyI2C_Init();
	MyI2C_Start();
	MyI2C_SendByte(0xD0);//1101  000 0
	uint8_t Ack=MyI2C_RcvAck();
	MyI2C_Stop();
	
	OLED_ShowNum(1,1,Ack,6);
//	Delay_s(1);
//	OLED_Clear();
	   
	while(1)
	{

	}
	
}
