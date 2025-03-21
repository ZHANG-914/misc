#include "includes.h"
#include "app_cfg.h"
#include "math.h"

#include "ano_dt.h"
#include "BSP.h"
#include "IMU.h"
#include "motor.h"
#include "pid.h"
#include "gy86.h"
#include "pid.h"
#include "pwm.h"
#include "BLUETOOTH.h"

/**********************************姿态解算相关******************************************************/
uint8_t gyroOffset, accOffset, pressOffset; //用于零偏校准
Float_t fGyro;                              //角速度数据（rad）
Angle_t angle;                              //姿态解算-角度值
Acc_t acc, offsetAcc;                       //原始数据、零偏数据
Gyro_t gyro, offsetGyro;                    //原始数据、零偏数据
Mag_t mag;                                  //原始数据
MPU6050_t mpu6050;
/*******************************************************************************************************/

/***********************************PID相关*********************************************************/

/*******************************************************************************************************/

/*************************************串口中断发送***********************************************************/
u8 sendBuf[50]; //发送数据缓存
/*******************************************************************************************************/

/***********************************PWM输入捕获******************************************************/
u16 PWM_IN_CH[4]; //PWM输入通道带宽
/*******************************************************************************************************/

/***********************************PWM输出比较*********************************************************/
float motor1, motor2, motor3, motor4; //四个电机速度:左前顺时针，右前逆时针，左后逆时针，右后顺时针
/*******************************************************************************************************/

/**********************************操作系统相关*********************************************************/
// 任务优先级定义
#define TASK_STARTUP_PRIO 4
#define MUTEX_IIC_PRIO 5
#define TASK_ANGEL_PRIO 6
#define TASK_PID_PRIO 7
#define TASK_COM_PRIO 8
// 任务栈大小定义
#define TASK_STARTUP_STK_SIZE 1024
#define TASK_COM_STK_SIZE 512
#define TASK_ANGEL_STK_SIZE 512
#define TASK_PID_STK_SIZE 512
// 栈内存分配
static OS_STK Task_Startup_STK[TASK_STARTUP_STK_SIZE];
static OS_STK Task_COM_STK[TASK_COM_STK_SIZE];
static OS_STK Task_Angel_STK[TASK_ANGEL_STK_SIZE];
static OS_STK Task_PID_STK[TASK_PID_STK_SIZE];
// 函数定义
static void Task_Startup(void *p_arg);
static void Task_COM(void *p_arg);
static void Task_Angel(void *p_arg);
static void Task_PID(void *p_arg);
//IIC互斥锁
OS_EVENT *IICMutex;
/*******************************************************************************************************/

int main(void)
{
    OSInit();
    OSTaskCreate(Task_Startup, (void *)0, &Task_Startup_STK[TASK_STARTUP_STK_SIZE - 1], TASK_STARTUP_PRIO);
    OSStart();
    return 0;
}

//启动任务
//static void Task_Startup(void *p_arg)
//{
//		INT8U err;
//    BSP_Init();
//    //最低占空比启动电机
//    MOTOR_init();
//    CalibInit(); //打开零偏校准

//    // Create functional task
//    IICMutex = OSMutexCreate(MUTEX_IIC_PRIO, &err);
//    OSTaskCreate(Task_COM, (void *)0, &Task_COM_STK[TASK_COM_STK_SIZE - 1], TASK_COM_PRIO);
//    OSTaskCreate(Task_Angel, (void *)0, &Task_Angel_STK[TASK_ANGEL_STK_SIZE - 1], TASK_ANGEL_PRIO);
//    OSTaskCreate(Task_PID, (void *)0, &Task_PID_STK[TASK_PID_STK_SIZE - 1], TASK_PID_PRIO);

//    // Delete itself
//    OSTaskDel(OS_PRIO_SELF);
//}

////通信任务
//static void Task_COM(void *p_arg)
//{
//    //    int32_t temp;
//    while (1)
//    {
//        if (!Calib_Status())
//        { //零偏校准结束
//            ANO_DT_Send_Senser(mpu6050.acc_x, mpu6050.acc_y, mpu6050.acc_z, mpu6050.gyro_x, mpu6050.gyro_y, mpu6050.gyro_z, mag.x, mag.y, mag.z);
//            ANO_DT_Send_Status(angle.roll, angle.pitch, angle.yaw); //发送姿态数据帧
//        }
//        OSTimeDly(100);
//    }
//}


static void Task_Startup(void *p_arg)
{
    char tmp[20];
    BSP_Init();
    MOTOR_init();
    CalibInit(); //打开零偏校准
    while (1)
    {
        OSTimeDly(1);
        mag = READ_HMCALL(mag);
        mpu6050 = MPU6050_READ(mpu6050); //读取加速度、角速度、磁场强度
        // ANO_DT_Send_Senser(mpu6050.acc_x, mpu6050.acc_y, mpu6050.acc_z, mpu6050.gyro_x, mpu6050.gyro_y, mpu6050.gyro_z, mag.x, mag.y, mag.z);

        if (!Calib_Status())
        {
            IMUupdate(mpu6050.gyro_x * RAW_TO_RAD, mpu6050.gyro_y * RAW_TO_RAD, mpu6050.gyro_z * RAW_TO_RAD, mpu6050.acc_x, mpu6050.acc_y, mpu6050.acc_z, mag.x, mag.y, mag.z);
            // ANO_DT_Send_Status(angle.roll, angle.pitch, angle.yaw); //发送姿态数据帧

            
        }
        // OSTimeDly(1000);
        // USARTSendString(USART6," 1:");
        // ShortTo0xString(tmp, PWM_IN_CH[0]);
        // USARTSendString(USART6,tmp);

        // USARTSendString(USART6," 2:");
        // ShortTo0xString(tmp, PWM_IN_CH[1]);
        // USARTSendString(USART6,tmp);

        // USARTSendString(USART6," 3:");
        // ShortTo0xString(tmp, PWM_IN_CH[2]);
        // USARTSendString(USART6,tmp);

        // USARTSendString(USART6," 4:");
        // ShortTo0xString(tmp, PWM_IN_CH[3]);
        // USARTSendString(USART6,tmp);
    }
}
