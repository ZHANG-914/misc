#include"pid_para.h"
#include "math.h"
#include"imu.h"
#include "control.h"

static float rMat[3][3];/*旋转矩阵*/
float exInt = 0.0f;
float eyInt = 0.0f;
float ezInt = 0.0f;		/*积分误差累计*/
float Kp = 0.4f;		/*比例增益*/
float Ki = 0.001f;		/*积分增益*/
static float q0 = 1.0f;	/*四元数*/
static float q1 = 0.0f;
static float q2 = 0.0f;
static float q3 = 0.0f;	



/*计算旋转矩阵*/
void imuComputeRotationMatrix(void)
{
    float q1q1 = q1 * q1;
    float q2q2 = q2 * q2;
    float q3q3 = q3 * q3;

    float q0q1 = q0 * q1;
    float q0q2 = q0 * q2;
    float q0q3 = q0 * q3;
    float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q2q3 = q2 * q3;

    rMat[0][0] = 1.0f - 2.0f * q2q2 - 2.0f * q3q3;
    rMat[0][1] = 2.0f * (q1q2 + -q0q3);
    rMat[0][2] = 2.0f * (q1q3 - -q0q2);

    rMat[1][0] = 2.0f * (q1q2 - -q0q3);
    rMat[1][1] = 1.0f - 2.0f * q1q1 - 2.0f * q3q3;
    rMat[1][2] = 2.0f * (q2q3 + -q0q1);

    rMat[2][0] = 2.0f * (q1q3 + -q0q2);
    rMat[2][1] = 2.0f * (q2q3 - -q0q1);
    rMat[2][2] = 1.0f - 2.0f * q1q1 - 2.0f * q2q2;
}

float invSqrt(float x)	/*快速开平方求倒*/
{
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

void imuUpdate(Axis3f acc, Axis3f gyro, Attitude *attitude , float dt)	/*数据融合 互补滤波*/
{
	float normalise;
	float ex, ey, ez;
	float halfT = 0.5f * dt;
//	float accBuf[3] = {0.f};
//	Axis3f tempacc = acc;
	
	gyro.x = gyro.x * DEG2RAD;	/* 度转弧度 */
	gyro.y = gyro.y * DEG2RAD;
	gyro.z = gyro.z * DEG2RAD;

	/* 加速度计输出有效时,利用加速度计补偿陀螺仪*/
	if((acc.x != 0.0f) || (acc.y != 0.0f) || (acc.z != 0.0f))
	{
		/*单位化加速计测量值*/
		normalise = invSqrt(acc.x * acc.x + acc.y * acc.y + acc.z * acc.z);
		acc.x *= normalise;
		acc.y *= normalise;
		acc.z *= normalise;

		/*加速计读取的方向与重力加速计方向的差值，用向量叉乘计算*/
		ex = (acc.y * rMat[2][2] - acc.z * rMat[2][1]);
		ey = (acc.z * rMat[2][0] - acc.x * rMat[2][2]);
		ez = (acc.x * rMat[2][1] - acc.y * rMat[2][0]);
		
		/*误差累计，与积分常数相乘*/
		exInt += Ki * ex * dt ;  
		eyInt += Ki * ey * dt ;
		ezInt += Ki * ez * dt ;
		
		/*用叉积误差来做PI修正陀螺零偏，即抵消陀螺读数中的偏移量*/
		gyro.x += Kp * ex + exInt;
		gyro.y += Kp * ey + eyInt;
		gyro.z += Kp * ez + ezInt;
	}
	/* 一阶近似算法，四元数运动学方程的离散化形式和积分 */
	float q0Last = q0;
	float q1Last = q1;
	float q2Last = q2;
	float q3Last = q3;
	q0 += (-q1Last * gyro.x - q2Last * gyro.y - q3Last * gyro.z) * halfT;
	q1 += ( q0Last * gyro.x + q2Last * gyro.z - q3Last * gyro.y) * halfT;
	q2 += ( q0Last * gyro.y - q1Last * gyro.z + q3Last * gyro.x) * halfT;
	q3 += ( q0Last * gyro.z + q1Last * gyro.y - q2Last * gyro.x) * halfT;
	
	/*单位化四元数*/
	normalise = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= normalise;
	q1 *= normalise;
	q2 *= normalise;
	q3 *= normalise;
	
	imuComputeRotationMatrix();	/*计算旋转矩阵*/
	
	/*计算roll pitch yaw 欧拉角*/
	attitude->pitch = -asinf(rMat[2][0]) * RAD2DEG; 
	attitude->roll = atan2f(rMat[2][1], rMat[2][2]) * RAD2DEG;
	attitude->yaw = atan2f(rMat[1][0], rMat[0][0]) * RAD2DEG;
	
//	if (!isGravityCalibrated)	/*未校准*/
//	{		
////		accBuf[0] = tempacc.x* rMat[0][0] + tempacc.y * rMat[0][1] + tempacc.z * rMat[0][2];	/*accx*/
////		accBuf[1] = tempacc.x* rMat[1][0] + tempacc.y * rMat[1][1] + tempacc.z * rMat[1][2];	/*accy*/
//		accBuf[2] = tempacc.x* rMat[2][0] + tempacc.y * rMat[2][1] + tempacc.z * rMat[2][2];	/*accz*/
//		calBaseAcc(accBuf);		/*计算静态加速度*/				
//	}
}
