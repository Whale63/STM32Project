#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "key.h"
#include "buzzer.h"


uint8_t KeyNum;

int main(void)
{
	LED_Init();
	Key_Init();
	Buzzer_Init();
	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum==1)
		{
		LED1_ON();
		LED2_OFF();

		}
		if(KeyNum==5)
		{
		LED1_OFF();
		LED2_ON();

		}	
		if(KeyNum==8)
		{
		Buzzer_ON();
		}
		
		
		
//		Delay_ms(500);
//		LED1_OFF();
//		LED2_ON();
//		Delay_ms(500);	
	}
}
