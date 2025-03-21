#include "MPU6050.h"
#include "usart.h"
#include "imu.h"

extern Acc_t offsetAcc; //原始数据、零偏数据
extern Gyro_t offsetGyro; //原始数据、零偏数据

int MPU6050_Init(void){  //初始化MPU6050

	I2C_SAND_BYTE(MPU6050_ADD,MPU6050_RA_PWR_MGMT_1,0x80);//解除休眠状态
	delay_ms(1000); //等待器件就绪
	I2C_SAND_BYTE(MPU6050_ADD,MPU6050_RA_PWR_MGMT_1,0x00);//解除休眠状态
	I2C_SAND_BYTE(MPU6050_ADD,MPU6050_RA_SMPLRT_DIV,0x07);//陀螺仪采样率
	I2C_SAND_BYTE(MPU6050_ADD,MPU6050_RA_CONFIG,0x06);
	I2C_SAND_BYTE(MPU6050_ADD,MPU6050_RA_ACCEL_CONFIG,0x00);//配置加速度传感器工作在16G模式
	I2C_SAND_BYTE(MPU6050_ADD,MPU6050_RA_GYRO_CONFIG,0x18);//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
	
	return 1;
}

MPU6050_t MPU6050_READ(MPU6050_t mpu6050){ //读出X、Y、Z三轴加速度/陀螺仪原始数据 //n[0]是AX，n[1]是AY，n[2]是AZ，n[3]是GX，n[4]是GY，n[5]是GZ 
//		u8 i;
    u8 dataBuf[14]; 
//		u16 n[6];
    I2C_READ_BUFFER(MPU6050_ADD, MPU6050_RA_ACCEL_XOUT_H, dataBuf, 14); //读出连续的数据地址，包括了加速度和陀螺仪共12字节
//    for(i=0; i<3; i++) 	//整合加速度
//      n[i]=((t[2*i] << 8) + t[2*i+1]);
//    for(i=4; i<7; i++)	//整合陀螺仪
//      n[i-1]=((t[2*i] << 8) + t[2*i+1]);      

//		mpu6050.acc_x = n[0];
//		mpu6050.acc_y = n[1];
//		mpu6050.acc_z = n[2];
//		mpu6050.gyro_x = n[3];
//		mpu6050.gyro_y = n[4];
//		mpu6050.gyro_z = n[5];
	
		mpu6050.acc_x = ((((int16_t)dataBuf[0]) << 8) | dataBuf[1]) - offsetAcc.x;
    mpu6050.acc_y = ((((int16_t)dataBuf[2]) << 8) | dataBuf[3]) - offsetAcc.y;
    mpu6050.acc_z = ((((int16_t)dataBuf[4]) << 8) | dataBuf[5]) - offsetAcc.z;
    mpu6050.gyro_x = ((((int16_t)dataBuf[8]) << 8) | dataBuf[9]) - offsetGyro.x;
    mpu6050.gyro_y = ((((int16_t)dataBuf[10]) << 8) | dataBuf[11]) - offsetGyro.x;
    mpu6050.gyro_z = ((((int16_t)dataBuf[12]) << 8) | dataBuf[13]) - offsetGyro.x;
		
		MPU6050_Offset();   
		
		return mpu6050;
}
 

