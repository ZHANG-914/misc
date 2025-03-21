#include "pwm.h"



/*******************************变量声明*********************************/
extern float motor1, motor2, motor3, motor4;
extern u16 PWM_IN_CH[4];



/****************************************************************
 * 功能：输入初始化
 * **************************************************************/
void PWM_IN_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    // Enable GPIOA GPIOB and TIM3 TIM4 clock
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);

    // GPIO configuration. Push-pull alternate function
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // GPIO alternate function configuration
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_TIM3);   
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);    
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);    

    // Close TIM3 and TIM4
    TIM_DeInit(TIM3);
    TIM_DeInit(TIM4);
    // TIM3|4 configuration. Prescaler is 84, period is 0xFFFF, and counter mode is up
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler = 84 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    // TIM3 input configuration. Capture on rising edge and filter value is 0x0B
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0B;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0B;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0B;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0B;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    // TIM4 input configuration. Capture on rising edge and filter value is 0x0B
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0B;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0B;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);

    // NVIC initialization
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // TIM3|4 interrupt configuration
    TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
    TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);
    TIM_ITConfig(TIM3, TIM_IT_CC3, ENABLE);
    TIM_ITConfig(TIM3, TIM_IT_CC4, ENABLE);
    TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);
    TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);

    // Enable TIM3|4
    TIM_Cmd(TIM3, ENABLE);
    TIM_Cmd(TIM4, ENABLE);

}



/****************************************************************
 * 功能：输出初始化
 * **************************************************************/
void PWM_OUT_Init(void)
{
    uint16_t arr = 1000 - 1;
    uint16_t psc = 1548 - 1; //54.27hz的PWM

    RCC->APB1ENR |= 1 << 0; //TIM2时钟shin
    TIM2->CR1 &= ~(3 << 5); //边沿对齐模式
    TIM2->CR1 &= ~(1 << 4); //计数器递增计数
    TIM2->SMCR &= ~(7 << 0); //时钟来源设置为内部时钟
    TIM2->ARR = arr; //设定计数器自动重装值
    TIM2->PSC = psc; //预分频器不分频

    TIM2->CCR1 = 0;
    TIM2->CCR2 = 0;
    TIM2->CCR3 = 0;
    TIM2->CCR4 = 0;
    
    //TIM2通道一、二初始化
    RCC->AHB1ENR |= 1 << 0; //使能PORTA时钟
    GPIO_Set(GPIOA, GPIO_Pin_0, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Fast_Speed, GPIO_PuPd_NOPULL);
    GPIO_Set(GPIOA, GPIO_Pin_1, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Fast_Speed, GPIO_PuPd_NOPULL);
    GPIO_AF_Set(GPIOA, 0, 2);
    GPIO_AF_Set(GPIOA, 1, 2);
    TIM2->CCMR1 &= ~(3 << 0); //CH1 设置为输出模式
    TIM2->CCMR1 |= 6 << 4; //CH1 PWM1 模式
    TIM2->CCMR1 |= 1 << 3; //CH1 预装载使能
    TIM2->CCER |= 1 << 0; //OC1 输出使能
    TIM2->CCER &= ~(1 << 1); //OC1 高电平有效
    //TIM2->CCER|=1<<1; //OC1 低电平有效
    TIM2->CCMR1 &= ~(3 << 8); //CH2 设置为输出模式
    TIM2->CCMR1 |= 6 << 12; //CH2 PWM1 模式
    TIM2->CCMR1 |= 1 << 11; //CH2 预装载使能
    TIM2->CCER |= 1 << 4; //OC2 输出使能
    TIM2->CCER &= ~(1 << 5); //OC2 高电平有效
    //TIM2->CCER|=1<<5; //OC2 低电平有效    

    //TIM2通道三、四初始化
    RCC->AHB1ENR |= 1 << 0; //使能PORTA时钟
    GPIO_Set(GPIOA, GPIO_Pin_2, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Fast_Speed, GPIO_PuPd_NOPULL);
    GPIO_Set(GPIOA, GPIO_Pin_3, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Fast_Speed, GPIO_PuPd_NOPULL);
    GPIO_AF_Set(GPIOA, 2, 2);
    GPIO_AF_Set(GPIOA, 3, 2);
    TIM2->CCMR2 &= ~(3 << 0); //CH3 设置为输出模式
    TIM2->CCMR2 |= 6 << 4; //CH3 PWM1 模式
    TIM2->CCMR2 |= 1 << 3; //CH3 预装载使能
    TIM2->CCER |= 1 << 8; //OC3 输出使能
    TIM2->CCER &= ~(1 << 9); //OC3 高电平有效
    //TIM2->CCER|=1<<9; //OC3 低电平有效
    TIM2->CCMR2 &= ~(3 << 8); //CH4 设置为输出模式
    TIM2->CCMR2 |= 6 << 12; //CH4 PWM1 模式
    TIM2->CCMR2 |= 1 << 11; //CH4 预装载使能
    TIM2->CCER |= 1 << 12; //OC4 输出使能
    TIM2->CCER &= ~(1 << 13); //OC4 高电平有效
    //TIM2->CCER|=1<<13; //OC4 低电平有效    

    TIM2->CR1 |= 1 << 7;
    TIM2->CR1 |= 1 << 0;

}



/****************************************************************
 * 功能：输入中断                                                
 * TIM3_CAPTURE_STA[i]:0,还没捕获到高电平;1,已经捕获到高电平了.    
 * TIM3_CAPTURE_OVF[i]:0,未溢出;1,溢出.
 * TIM3_CAPTURE_VAL[i][0]:上升沿对应计数器值
 * TIM3_CAPTURE_VAL[i][1]:下降沿对应计数器值
 * PWM_IN_CH[i]:通道i+1的输入PWM位宽
 * **************************************************************/
u8  TIM3_CAPTURE_STA[4];
u16 TIM3_CAPTURE_OVF[4];
u16 TIM3_CAPTURE_VAL[4][2];

void TIM3_PWM_IN_IRQ(void)
{
    u8 i;
    //通道i+1中断
    for (i = 0; i < 4; i++) {
        if (TIM3->SR & (1 << (i + 1))) {
            TIM3->SR &= ~((0x0001 << (i + 1))); //清除中断标志
            if (TIM3_CAPTURE_STA[i]) { //已捕获到高电平，说明此时捕获到下降沿
                TIM3_CAPTURE_STA[i] = 0; //更改捕获状态
                TIM3_CAPTURE_VAL[i][1] = *(&(TIM3->CCR1) + i); //读取下降沿对应计数器值
                PWM_IN_CH[i] = TIM3_CAPTURE_VAL[i][1] - TIM3_CAPTURE_VAL[i][0] + TIM3_CAPTURE_OVF[i] * 0xffff; //计算脉冲宽度
                TIM3_CAPTURE_OVF[i] = 0; //溢出次数清零
                TIM3->CCER &= ~(0x0001 << (1 + 4 * i)); //CCxP=00 通道上升沿捕获
            } else { //捕获到上升沿
                TIM3_CAPTURE_STA[i] = 1; //更改捕获状态
                TIM3_CAPTURE_VAL[i][0] = *(&(TIM3->CCR1) + i); //读取上升沿对应计数器值
                TIM3->CCER |= (0x0001 << (1 + 4 * i)); //CCxP=01 通道下降沿捕获
            }
        }
    }
}



/****************************************************************
 * 功能：输出中断
 * **************************************************************/
void PWM_OUT(void)
{
    TIM2->CCR1 = motor2 * PWM_IN_TO_OUT;
    TIM2->CCR2 = motor4 * PWM_IN_TO_OUT;
    TIM2->CCR3 = motor3 * PWM_IN_TO_OUT;
    TIM2->CCR4 = motor1 * PWM_IN_TO_OUT;
}