#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"



uint8_t KeyNum;

int main(void)
{
	OLED_Init();
	while(1)
	{
	OLED_ShowChar(1,1,'A');
		OLED_ShowString(2,1,"I love u my mum");
	
	}
	
}
