#include "pwm.h"

/*******************************��������*********************************/
extern u16 PWM_IN_CH[4];

/****************************************************************
 * ���ܣ������ʼ��
 * **************************************************************/
void PWM_IN_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    // Enable GPIOA GPIOB and TIM3 TIM4 clock
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);

    // GPIO configuration. Push-pull alternate function
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6  | GPIO_Pin_7 | GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // GPIO alternate function configuration
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);

    // reset TIM2 and TIM3
    TIM_DeInit(TIM2);
    TIM_DeInit(TIM3);
    // TIM3|2 configuration. Prescaler is 84, period is 0xFFFF, and counter mode is up
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;    //�������Զ���װֵ 	���벶��ͨ������Ϊ��0xFFFF
    TIM_TimeBaseStructure.TIM_Prescaler = 84 - 1; //Ԥ��Ƶ����psc
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //�ظ���������
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // TIM3 input configuration. Capture on rising edge and filter value is 0x0B
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    // TIM2 input configuration. Capture on rising edge and filter value is 0x0B
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);

    // NVIC initialization

	
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_ITConfig(TIM3, TIM_IT_CC1  | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update, ENABLE); //��������жϣ�����CC1IE�����ж�

    TIM_Cmd(TIM3, ENABLE);
//    //TIM4�жϷ����ʼ��
//    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;           //�����ж�
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //�����ȼ�
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

//    TIM_ITConfig(TIM2, TIM_IT_CC1 | TIM_IT_Update | TIM_IT_CC2, ENABLE); //��������жϣ�����CC1IE�����ж�

//    TIM_Cmd(TIM2, ENABLE);
}

/****************************************************************
 * ���ܣ������ʼ��
 * **************************************************************/
void PWM_OUT_Init(u32 arr, u32 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);    //TIM4 ʱ��ʹ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   //ʹ�� PORTB ʱ��
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4); //����Ϊ TIM4-CH1
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM4);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; //TIM2���ĸ�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                                     //���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                               //�ٶ� 50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                                   //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                                     //����
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                           //��ʼ�� PA

    TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_Period = arr;                     //�Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //��ʼ����ʱ�� 2
    //��ʼ�� TIM14 Channel1 PWM ģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             //PWM ����ģʽ 1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //������Ե�

    TIM_OC1Init(TIM4, &TIM_OCInitStructure);          //��ʼ������ TIM2OC1
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ��Ԥװ�ؼĴ���
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);          //��ʼ������ TIM2OC1
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ��Ԥװ�ؼĴ���
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);          //��ʼ������ TIM2OC1
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ��Ԥװ�ؼĴ���
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);          //��ʼ������ TIM2OC1
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ��Ԥװ�ؼĴ���

    TIM_Cmd(TIM4, ENABLE); //ʹ�� TIM2
}

/****************************************************************
 * ���ܣ������ж�                                                
 * TIM3_CAPTURE_STA[i]:0,��û���񵽸ߵ�ƽ;1,�Ѿ����񵽸ߵ�ƽ��.    
 * TIM3_CAPTURE_OVF[i]:0,δ���;>0,���.
 * TIM3_CAPTURE_VAL[i][0]:�����ض�Ӧ������ֵ
 * TIM3_CAPTURE_VAL[i][1]:�½��ض�Ӧ������ֵ
 * PWM_IN_CH[i]:ͨ��i+1������PWMλ��
 * ps��tim3/4֧��16λ���벶��tim2/5֧��32λ���벶����Ҫ�޸Ķ�Ӧ������Сu16/u32�����ֵoxffff/0xffffffff
 * **************************************************************/
u8 TIM3_CAPTURE_STA[4];
u16 TIM3_CAPTURE_OVF[4];
u16 TIM3_CAPTURE_VAL[4][2];

void TIM3_IRQHandler(void)
{
    u8 i;
    // ����ж�
    if (TIM3->SR & TIM_IT_Update)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        for (i = 0; i < 4; i++)
        {
            if (TIM3_CAPTURE_STA[i])
            {
                TIM3_CAPTURE_OVF[i]++;
                if (TIM3_CAPTURE_OVF[i] == 0xffff)
                {
                    //�ߵ�ƽʱ��������������
                    TIM3_CAPTURE_STA[i] = 0; //�������β���
                    PWM_IN_CH[i] = 0xffff; // 0xffff * 0xffff
                    //todo����ʵ���������������غ��½��ط��ˣ����������
                }
            }
        }
    }
    //ͨ��i+1�ж�
    for (i = 0; i < 4; i++)
    {
        if (TIM3->SR & (1 << (i + 1)))
        {
            TIM3->SR &= ~((0x0001 << (i + 1))); //����жϱ�־
            if (TIM3_CAPTURE_STA[i])
            {
                //�Ѳ��񵽸ߵ�ƽ��˵����ʱ�����½���
                TIM3_CAPTURE_STA[i] = 0;                                                                       //���Ĳ���״̬
                TIM3_CAPTURE_VAL[i][1] = *(&(TIM3->CCR1) + i);                                                 //��ȡ�½��ض�Ӧ������ֵ
                PWM_IN_CH[i] = TIM3_CAPTURE_VAL[i][1] - TIM3_CAPTURE_VAL[i][0] + TIM3_CAPTURE_OVF[i] * 0xffff; //����������
                TIM3_CAPTURE_OVF[i] = 0;                                                                       //�����������
                TIM3->CCER &= ~(0x0001 << (1 + 4 * i));                                                        //CCxP=00 ͨ�������ز���
            }
            else
            {                                                  //����������
                TIM3_CAPTURE_STA[i] = 1;                       //���Ĳ���״̬
                TIM3_CAPTURE_VAL[i][0] = *(&(TIM3->CCR1) + i); //��ȡ�����ض�Ӧ������ֵ
                TIM3->CCER |= (0x0001 << (1 + 4 * i));         //CCxP=01 ͨ���½��ز���
            }
        }
    }
}
