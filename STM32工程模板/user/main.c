#include "stm32f10x.h"                  // Device header

int main()
{
//	IS_RCC_APB2_PERIPH
//	RCC_APB2
	RCC->APB2ENR=0x00000010;
	GPIOB->CRH=0X00300000;
	GPIOB->ODR=0X11111111;
	while(1)
{


}
}
