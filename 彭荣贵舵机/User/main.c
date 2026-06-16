#include "stm32f10x.h"


//////////////////////////////////////////////////////////////////////////////////	 
//未经作者许可，不得用于其它任何用途
//STM32f103c8t6开发板
//作者：Whale Zhang  QQ:3056512049
//修改：WhaleZhang 13939381056
//修改日期:2024/06/23
//版本：V5.0
//版权所有，盗版必究。
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	

/*  main.c  */

void RCC_Config(void);
void GPIO_Config(void);
void TIM2_PWM_Config(void);

int main(void)
{
    RCC_Config();     // 时钟配置
    GPIO_Config();    // GPIO 复用推挽输出
    TIM2_PWM_Config();// PWM 时基和占空比配置

    while (1)
    {
        /* 主循环可空转，也可动态修改占空比 */
    }
}

/*-------------------------------------------------
 * 1. 时钟配置：外部 8 MHz -> PLL 9 倍频 -> 72 MHz
 *------------------------------------------------*/
void RCC_Config(void)
{
    RCC_DeInit();
    RCC_HSEConfig(RCC_HSE_ON);
    while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); // 8*9 = 72 MHz
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08);

    /* APB1 = 36 MHz（TIM2 时钟 72 MHz 因为 TIMCLK = 2*PCLK1） */
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,  ENABLE);
}

/*-------------------------------------------------
 * 2. GPIO 配置：PA0 -> TIM2_CH1 (AFIO remap 关闭)
 *------------------------------------------------*/
void GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;          // PA0
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;     // 复用推挽
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*-------------------------------------------------
 * 3. TIM2 PWM 配置：50 Hz，50 % 占空比
 *    72 MHz / (PSC+1) = 1 MHz -> 周期 20 000 -> 50 Hz
 *------------------------------------------------*/
void TIM2_PWM_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef        TIM_OCInitStructure;

    /* 时基：计数频率 = 72 MHz / 72 = 1 MHz -> 1 us 计数一次 */
    TIM_TimeBaseStructure.TIM_Period        = 20000 - 1;    // 20 ms = 50 Hz
    TIM_TimeBaseStructure.TIM_Prescaler     = 72 - 1;       // 72 MHz / 72 = 1 MHz
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* PWM1 模式，占空比 = CCR / (ARR+1) */
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       = 10000;            // 50 % 占空比
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);        // 启动 TIM2
}

