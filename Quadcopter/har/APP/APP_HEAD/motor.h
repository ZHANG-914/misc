#ifndef MOTOR_H
#define MOTOR_H

//输入捕获定时器（TIM3）频率为 1MHz ,即 1/1M 秒计数器加1，
//则一次上升沿捕获到下降沿捕获的时间为 x/1M 秒，x为两次捕获计数器值相减
//又遥控器接收器的PWM频率为 54.27Hz ，即一个PWM持续时间为 1/54.27 秒
//假设此时输入的占空比为D，则 D / 54.27 = x / 1M => x = 1000000D / 54.27
//又因为PWM输出定时器（TIM3）arr为20000，为了输出的占空比和输入的一样，则所需的CCRx值为 20000D
//于是 x * PWM_IN_TO_OUT = 20000D => PWM_IN_TO_OUT = 20000D * 54.27 / 1000000D = 1.0854
#define PWM_IN_TO_OUT 1

void MOTOR_init(void);
void MOTOR_lock(void);
void MOTOR_max(void);
void MOTOR_CONTROL(void);
#endif
