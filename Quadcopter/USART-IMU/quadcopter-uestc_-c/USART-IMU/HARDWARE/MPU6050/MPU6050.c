#include "MPU6050.h"
#include "usart.h"
#include "imu.h"

extern Acc_t offsetAcc; //ԭʼ���ݡ���ƫ����
extern Gyro_t offsetGyro; //ԭʼ���ݡ���ƫ����

int MPU6050_Init(void){  //��ʼ��MPU6050

	I2C_SAND_BYTE(MPU6050_ADD,MPU6050_RA_PWR_MGMT_1,0x80);//�������״̬
	delay_ms(1000); //�ȴ���������
	I2C_SAND_BYTE(MPU6050_ADD,MPU6050_RA_PWR_MGMT_1,0x00);//�������״̬
	I2C_SAND_BYTE(MPU6050_ADD,MPU6050_RA_SMPLRT_DIV,0x07);//�����ǲ�����
	I2C_SAND_BYTE(MPU6050_ADD,MPU6050_RA_CONFIG,0x06);
	I2C_SAND_BYTE(MPU6050_ADD,MPU6050_RA_ACCEL_CONFIG,0x00);//���ü��ٶȴ�����������16Gģʽ
	I2C_SAND_BYTE(MPU6050_ADD,MPU6050_RA_GYRO_CONFIG,0x18);//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
	
	return 1;
}

MPU6050_t MPU6050_READ(MPU6050_t mpu6050){ //����X��Y��Z������ٶ�/������ԭʼ���� //n[0]��AX��n[1]��AY��n[2]��AZ��n[3]��GX��n[4]��GY��n[5]��GZ 
//		u8 i;
    u8 dataBuf[14]; 
//		u16 n[6];
    I2C_READ_BUFFER(MPU6050_ADD, MPU6050_RA_ACCEL_XOUT_H, dataBuf, 14); //�������������ݵ�ַ�������˼��ٶȺ������ǹ�12�ֽ�
//    for(i=0; i<3; i++) 	//���ϼ��ٶ�
//      n[i]=((t[2*i] << 8) + t[2*i+1]);
//    for(i=4; i<7; i++)	//����������
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
 

