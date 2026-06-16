#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "Key.h"

uint8_t KeyNum;		//定义用于接收按键键码的变量
uint16_t Speed=2000;		//定义速度变量

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	PWM_Init();
	Key_Init();			//按键初始化
	
	PWM_SetCompare1(4000);
	Delay_ms(8000);
	PWM_SetCompare1(2000);
	Delay_ms(2000);
	OLED_Clear();
	OLED_ShowString(1, 1, "ok");
	Delay_ms(1000);


	
	/*显示静态字符串*/
	OLED_Clear();
	OLED_ShowString(1, 1, "Speed%:");		//1行1列显示字符串Speed:
	
	while (1)
	{
		KeyNum = Key_GetNum();				//获取按键键码
		if (KeyNum == 1)					//按键1按下
		{
			Speed += 100;
		}			
		if (KeyNum == 2)					//按键1按下
		{
			Speed -= 100;	
		}
		if (Speed > 4000)				//5
		{
			Speed =3000;				//速度变量变为-100

		}
	
		PWM_SetCompare1(Speed);
		OLED_ShowSignedNum(1, 8, Speed, 4);	//OLED显示速度变量
	}
}                                                                                     
