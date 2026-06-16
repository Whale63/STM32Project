#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "countsensor.h"



int main(void)
{
	OLED_Init();
	CountSensor_Init();
	OLED_ShowChar(1,1,'A');
	OLED_ShowString(2,1,"I love u my mum");
	
	while(1)
	{
		OLED_ShowNum(3,1,CountSensor_Count,4);
	
	}
	
}
