#include "GY86.h"
#include "i2c.h"

extern Acc_t offsetAcc;	  //原始数据、零偏数据
extern Gyro_t offsetGyro; //原始数据、零偏数据

int HMC_Init(void)
{

	I2C_SAND_BYTE(HMC_ADD, HMC_CONFIGA, 0x50); //01010000/采样平均数4，输出速率15，正常测量配置
	I2C_SAND_BYTE(HMC_ADD, HMC_CONFIGB, 0xE0); //11100000/将增益调至最小
	I2C_SAND_BYTE(HMC_ADD, HMC_MODE, 0x00);	   //00000000/设置为连续模式

	return 1;
}

int GY86_Init(void)
{
	//		u8 a[2];
	int mpu6050 = MPU6050_Init();
	I2C_SAND_BYTE(MPU_ADD, MPU_CFG, 0x02);	//将MPU的CFG寄存器的第二位设置为1，其他位在使用MPU时配置
	I2C_SAND_BYTE(MPU_ADD, MPU_CTRL, 0x00); //将MPU的CTRL寄存器的第六位设置为0，与上面一步共同开启bypass模式
	OSTimeDly(111);
	int hmc = HMC_Init(); //HMC初始化

	if (mpu6050 && hmc)
		return 1;
	else
		return 0;
}

Mag_t READ_HMCALL(Mag_t mag)
{
	//		u8 i;
	u8 dataBuf[14];
	//		u16 n[3];
	I2C_READ_BUFFER(HMC_ADD, HMC_DATA_XMSB, dataBuf, 6);
	//		for(i=0;i<3;i++)
	//		{
	//				n[i]=(t[2*i]<<8)+t[2*i+1];
	//		}

	mag.z = (dataBuf[0] << 8) | dataBuf[1];
	mag.x = -((dataBuf[2] << 8) | dataBuf[3]);
	mag.y = (dataBuf[4] << 8) | dataBuf[5];

	if (mag.x > 0x7fff)
		mag.x -= 0xffff;
	if (mag.y > 0x7fff)
		mag.y -= 0xffff;
	if (mag.z > 0x7fff)
		mag.z -= 0xffff;

	return mag;
}

int MPU6050_Init(void)
{ //初始化MPU6050

	I2C_SAND_BYTE(MPU6050_ADD, MPU6050_RA_PWR_MGMT_1, 0x80); //解除休眠状态
	OSTimeDly(1000);										 //等待器件就绪
	I2C_SAND_BYTE(MPU6050_ADD, MPU6050_RA_PWR_MGMT_1, 0x00); //解除休眠状态
	I2C_SAND_BYTE(MPU6050_ADD, MPU6050_RA_SMPLRT_DIV, 0x07); //陀螺仪采样率
	I2C_SAND_BYTE(MPU6050_ADD, MPU6050_RA_CONFIG, 0x06);
	I2C_SAND_BYTE(MPU6050_ADD, MPU6050_RA_ACCEL_CONFIG, 0x00); //配置加速度传感器工作在16G模式
	I2C_SAND_BYTE(MPU6050_ADD, MPU6050_RA_GYRO_CONFIG, 0x18);  //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)

	return 1;
}

MPU6050_t MPU6050_READ(MPU6050_t mpu6050)
{	//读出X、Y、Z三轴加速度/陀螺仪原始数据 //n[0]是AX，n[1]是AY，n[2]是AZ，n[3]是GX，n[4]是GY，n[5]是GZ
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

	mpu6050.acc_z = ((((int16_t)dataBuf[0]) << 8) | dataBuf[1]) - offsetAcc.z;
	mpu6050.acc_x = -(((((int16_t)dataBuf[2]) << 8) | dataBuf[3]) - offsetAcc.x);
	mpu6050.acc_y = ((((int16_t)dataBuf[4]) << 8) | dataBuf[5]) - offsetAcc.y;
	mpu6050.gyro_z = ((((int16_t)dataBuf[8]) << 8) | dataBuf[9]) - offsetGyro.z;
	mpu6050.gyro_x = -(((((int16_t)dataBuf[10]) << 8) | dataBuf[11]) - offsetGyro.x);
	mpu6050.gyro_y = ((((int16_t)dataBuf[12]) << 8) | dataBuf[13]) - offsetGyro.y;

	MPU6050_Offset();

	return mpu6050;
}
