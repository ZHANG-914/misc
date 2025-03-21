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
    //    fac_us=SYSCLK/8;						//�����Ƿ�ʹ��OS,fac_us����Ҫʹ��
    reload = SYSCLK / 8;                       //ÿ���ӵļ������� ��λΪM
    reload *= 1000000 / OS_TICKS_PER_SEC;      //����delay_ostickspersec�趨���ʱ��
                                               //reloadΪ24λ�Ĵ���,���ֵ:16777216,��168M��,Լ��0.7989s����
                                               //    fac_ms=1000/OS_TICKS_PER_SEC;		//����OS������ʱ�����ٵ�λ
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; //����SYSTICK�ж�
    SysTick->LOAD = reload;                    //ÿ1/delay_ostickspersec���ж�һ��
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  //����SYSTICK
}
