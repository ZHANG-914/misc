#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "GY86.h"
#include "MPU6050.h"
#include "imu.h"
#include "ANO_DT.h"


/*******************************变量声明*********************************/
uint8_t gyroOffset, accOffset; //用于零偏校准

Float_t fGyro; //角速度数据（rad）
Angle_t angle; //姿态解算-角度值
Acc_t acc, offsetAcc; //原始数据、零偏数据
Gyro_t gyro, offsetGyro; //原始数据、零偏数据
Mag_t mag; //原始数据
MPU6050_t mpu6050;

int main(void)
{ 

//	u8 t;
//	u8 len;	
//	u16 times=0;  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(115200);	//串口初始化波特率为115200
	AHRS_Time_Init();
	
	int i2c = I2C_Configuration();
	int gy86 = GY86_Init();
//	Quat_Init();
	CalibInit();
	
	
	while(i2c && gy86)
	{
//		if(USART_RX_STA&0x8000)
//		{					   
//			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
//			printf("\r\n您发送的消息为:\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART_SendData(USART1, USART_RX_BUF[t]);         //向串口1发送数据
//				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
//			}
//			printf("\r\n\r\n");//插入换行
//			USART_RX_STA=0;
//		}else
//		{
//			printf("gy86_init\r\n");
			mag = READ_HMCALL(mag);
			mpu6050 = MPU6050_READ(mpu6050);


//			printf("HMC5883L_DATA %d %d %d\r\n", mag.x, mag.y, mag.z);
//			printf("AX:%d  AY:%d  AZ:%d\r\nGX:%d  GY:%d  GZ:%d\r\n",mpu6050.acc_x,mpu6050.acc_y,mpu6050.acc_z,mpu6050.gyro_x,mpu6050.gyro_y,mpu6050.gyro_z);

			if (!Calib_Status()) { //零偏校准结束
//						ANO_DT_Send_Senser(mpu6050.acc_x,mpu6050.acc_y,mpu6050.acc_z,mpu6050.gyro_x * RAW_TO_ANGLE,mpu6050.gyro_y * RAW_TO_ANGLE,mpu6050.gyro_z * RAW_TO_ANGLE,mag.x, mag.y, mag.z);
						ANO_DT_Send_Senser(mpu6050.acc_x,mpu6050.acc_y,mpu6050.acc_z,mpu6050.gyro_x,mpu6050.gyro_y,mpu6050.gyro_z ,mag.x, mag.y, mag.z);
//						AHRSupdate(mpu6050.gyro_x * RAW_TO_RAD , mpu6050.gyro_y * RAW_TO_RAD , mpu6050.gyro_z * RAW_TO_RAD , mpu6050.acc_x , mpu6050.acc_y , mpu6050.acc_z , mag.x, mag.y, mag.z);
						IMUupdate(mpu6050.gyro_x * RAW_TO_RAD , mpu6050.gyro_y * RAW_TO_RAD , mpu6050.gyro_z * RAW_TO_RAD , mpu6050.acc_x , mpu6050.acc_y , mpu6050.acc_z , mag.x, mag.y, mag.z);
						ANO_DT_Send_Status(angle.roll, angle.pitch, angle.yaw);
//						printf("HMC5883L_DATA %d %d %d\r\n", mag.x, mag.y, mag.z);
//						printf("AX:%d  AY:%d  AZ:%d\r\nGX:%d  GY:%d  GZ:%d\r\n",mpu6050.acc_x,mpu6050.acc_y,mpu6050.acc_z,mpu6050.gyro_x,mpu6050.gyro_y,mpu6050.gyro_z);
//						printf("roll:%f  pitch:%f  yaw:%f\r\n", angle.roll, angle.pitch, angle.yaw); 
        }
//			delay_ms(500);
//		}
	}
}

