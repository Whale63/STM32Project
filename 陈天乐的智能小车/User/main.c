#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"

uint8_t KeyNum;
int8_t Speed;

int main(void)
{
	OLED_Init();
//	Motor_Init();
	Motor1_Init( );
	Motor2_Init( );
	Key_Init();
	
	while (1)
	{
 Speed=100;
Motor_SetSpeed(Speed);
//		if(HW_1== 0 && HW_2== 0 && HW_3== 0 && HW_4== 0)
//		{ 
//			run();
//			Delay_ms(50);
//		}
//		else if(HW_1== 0 && HW_2== 1 && HW_3== 0 && HW_4== 0)
//		{ 
//			right();
//			Delay_ms(150);
//		}
//		else if(HW_1== 1 && HW_2== 0 && HW_3== 0 && HW_4== 0)
//		{ 
//			right();
//			Delay_ms(250);
//		}
//		else if(HW_1== 1 && HW_2== 1 && HW_3== 0 && HW_4== 0)
//		{ 
//			right();
//			Delay_ms(300);
//		}
//		else if(HW_1== 0 && HW_2== 0 && HW_3== 1 && HW_4== 0)
//		{ 
//			left();
//			Delay_ms(150);
//		}
//		else if(HW_1== 0 && HW_2== 0 && HW_3== 0 && HW_4== 1)
//		{ 
//			left();
//			Delay_ms(250);
//		}
//		else if(HW_1== 0 && HW_2== 0 && HW_3== 1 && HW_4== 1)
//		{ 
//			left();
//			Delay_ms(300);
//		}

	}
}
