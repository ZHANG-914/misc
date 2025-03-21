#include "tim.h"

/****************************************************************
 * ���ܣ���ȡ��̬�������ʱ��
 * **************************************************************/
void AHRS_Time_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    //ʹ��TIM2ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    //�ر�TIM2�Խ�������
    TIM_DeInit(TIM2);

    //pscΪ84��arrΪ0xFFFF�����ϼ���
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler = 84 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // ʹ��TIM2
    TIM_Cmd(TIM2, ENABLE);
}