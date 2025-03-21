#include "pwm.h"

/*******************************变量声明*********************************/
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
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;    //计数器自动重装值 	输入捕获通常设置为：0xFFFF
    TIM_TimeBaseStructure.TIM_Prescaler = 84 - 1; //预分频器，psc
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //重复计数设置
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

    TIM_ITConfig(TIM3, TIM_IT_CC1  | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update, ENABLE); //允许更新中断，允许CC1IE捕获中断

    TIM_Cmd(TIM3, ENABLE);
//    //TIM4中断分组初始化
//    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;           //捕获中断
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //从优先级
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

//    TIM_ITConfig(TIM2, TIM_IT_CC1 | TIM_IT_Update | TIM_IT_CC2, ENABLE); //允许更新中断，允许CC1IE捕获中断

//    TIM_Cmd(TIM2, ENABLE);
}

/****************************************************************
 * 功能：输出初始化
 * **************************************************************/
void PWM_OUT_Init(u32 arr, u32 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);    //TIM4 时钟使能
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   //使能 PORTB 时钟
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4); //复用为 TIM4-CH1
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM4);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; //TIM2的四个引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                                     //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                               //速度 50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                                   //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                                     //上拉
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                           //初始化 PA

    TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //定时器分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseStructure.TIM_Period = arr;                     //自动重装载值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //初始化定时器 2
    //初始化 TIM14 Channel1 PWM 模式
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             //PWM 调制模式 1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //输出极性低

    TIM_OC1Init(TIM4, &TIM_OCInitStructure);          //初始化外设 TIM2OC1
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); //使能预装载寄存器
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);          //初始化外设 TIM2OC1
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); //使能预装载寄存器
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);          //初始化外设 TIM2OC1
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); //使能预装载寄存器
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);          //初始化外设 TIM2OC1
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //使能预装载寄存器

    TIM_Cmd(TIM4, ENABLE); //使能 TIM2
}

/****************************************************************
 * 功能：输入中断                                                
 * TIM3_CAPTURE_STA[i]:0,还没捕获到高电平;1,已经捕获到高电平了.    
 * TIM3_CAPTURE_OVF[i]:0,未溢出;>0,溢出.
 * TIM3_CAPTURE_VAL[i][0]:上升沿对应计数器值
 * TIM3_CAPTURE_VAL[i][1]:下降沿对应计数器值
 * PWM_IN_CH[i]:通道i+1的输入PWM位宽
 * ps：tim3/4支持16位输入捕获，tim2/5支持32位输入捕获，需要修改对应参数大小u16/u32与溢出值oxffff/0xffffffff
 * **************************************************************/
u8 TIM3_CAPTURE_STA[4];
u16 TIM3_CAPTURE_OVF[4];
u16 TIM3_CAPTURE_VAL[4][2];

void TIM3_IRQHandler(void)
{
    u8 i;
    // 溢出中断
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
                    //高电平时间过长，发生溢出
                    TIM3_CAPTURE_STA[i] = 0; //结束本次捕获
                    PWM_IN_CH[i] = 0xffff; // 0xffff * 0xffff
                    //todo：其实这样操作让上升沿和下降沿反了，是有问题的
                }
            }
        }
    }
    //通道i+1中断
    for (i = 0; i < 4; i++)
    {
        if (TIM3->SR & (1 << (i + 1)))
        {
            TIM3->SR &= ~((0x0001 << (i + 1))); //清除中断标志
            if (TIM3_CAPTURE_STA[i])
            {
                //已捕获到高电平，说明此时捕获到下降沿
                TIM3_CAPTURE_STA[i] = 0;                                                                       //更改捕获状态
                TIM3_CAPTURE_VAL[i][1] = *(&(TIM3->CCR1) + i);                                                 //读取下降沿对应计数器值
                PWM_IN_CH[i] = TIM3_CAPTURE_VAL[i][1] - TIM3_CAPTURE_VAL[i][0] + TIM3_CAPTURE_OVF[i] * 0xffff; //计算脉冲宽度
                TIM3_CAPTURE_OVF[i] = 0;                                                                       //溢出次数清零
                TIM3->CCER &= ~(0x0001 << (1 + 4 * i));                                                        //CCxP=00 通道上升沿捕获
            }
            else
            {                                                  //捕获到上升沿
                TIM3_CAPTURE_STA[i] = 1;                       //更改捕获状态
                TIM3_CAPTURE_VAL[i][0] = *(&(TIM3->CCR1) + i); //读取上升沿对应计数器值
                TIM3->CCER |= (0x0001 << (1 + 4 * i));         //CCxP=01 通道下降沿捕获
            }
        }
    }
}
