#include "tim.h"

/****************************************************************
 * 功能：获取姿态解算采样时间
 * **************************************************************/
void AHRS_Time_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    //使能TIM2时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    //关闭TIM2以进行配置
    TIM_DeInit(TIM2);

    //psc为84，arr为0xFFFF，向上计数
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler = 84 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // 使能TIM2
    TIM_Cmd(TIM2, ENABLE);
}