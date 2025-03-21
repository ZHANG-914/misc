#include "BSP.h"

void BSP_Init(void){
	SysTick_Init();
	DELAY_Init(84);
	USART6_Init(84,115200);
	I2C_Configuration();
	while(MPU6050_Init()!=1);//若MPU6050初始化不成功，则程序不向下运行;
	HMC5883L_Init();
    //MS561101BA_Init();
//	Quat_Init();
	PWM_OUT_Init();
	PWM_IN_Init();
	PID_Init();
	PID_Time_Init();
	AHRS_Time_Init();
}

void SysTick_Init(void){
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.SYSCLK_Frequency/OS_TICKS_PER_SEC);
}