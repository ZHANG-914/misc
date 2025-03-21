#include "BSP.h"
#include "GY86.h"
#include "ano_dt.h"
#include "BSP.h"
#include "IMU.h"
#include "motor.h"
#include "pid.h"
#include "gy86.h"
#include "pid.h"
#include "pwm.h"
#include "usart.h"
#include "i2c.h"

extern PID_type PID_angle_roll;
extern PID_type PID_angle_pitch;
extern PID_type PID_angle_yaw;
extern PID_type PID_rate_roll;
extern PID_type PID_rate_pitch;
extern PID_type PID_rate_yaw;

void BSP_Init(void)
{
    Systick_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    PWM_OUT_Init(20000, 84 - 1);
    PWM_IN_Init();

    AHRS_Time_Init();
    I2C_Configuration();
    GY86_Init();
    uart6_init(115200);
    uart1_init(115200);
}

void Systick_init(void)
{
    u32 reload;
    u8 SYSCLK = 84;
    SysTick->CTRL &= (uint32_t)0xFFFFFFFB;
    //    fac_us=SYSCLK/8;						//不论是否使用OS,fac_us都需要使用
    reload = SYSCLK / 8;                       //每秒钟的计数次数 单位为M
    reload *= 1000000 / OS_TICKS_PER_SEC;      //根据delay_ostickspersec设定溢出时间
                                               //reload为24位寄存器,最大值:16777216,在168M下,约合0.7989s左右
                                               //    fac_ms=1000/OS_TICKS_PER_SEC;		//代表OS可以延时的最少单位
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; //开启SYSTICK中断
    SysTick->LOAD = reload;                    //每1/delay_ostickspersec秒中断一次
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  //开启SYSTICK
}
