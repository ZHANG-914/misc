#ifndef PWM_H
#define PWM_H
#include "includes.h"

void PWM_IN_Init(void);
void PWM_OUT_Init(u32 arr, u32 psc);
void TIM5_PWM_IN_IRQ(void);

#endif
