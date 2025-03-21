#ifndef IMU_H
#define IMU_H

#include "includes.h"
#include "math.h"

#define PI 3.1415927f
//�Ƕȵ�λ���ת��
#define RAD_TO_ANGLE 57.2957795f //����ת�Ƕ�
#define RAW_TO_ANGLE 0.0610351f //ԭʼ����ת�Ƕȣ���Ӧ��2000��/s
#define RAW_TO_RAD 0.0010653f //ԭʼ����ת���ȣ���Ӧ��2000��/s

#define FILTER_NUM 2

typedef enum {
    ACC_GYRO_MAG = 0,
    TEMP_PRESS
} Type_t;


/* MPU6050 */
typedef struct
{
    s16 acc_x;
    s16 acc_y;
    s16 acc_z;
		s16 gyro_x;
    s16 gyro_y;
    s16 gyro_z;
} MPU6050_t;


/* MPU6050--���ٶȼƽṹ�� */
typedef struct
{
    s16 x;
    s16 y;
    s16 z;
} Acc_t;

/* MPU6050--�����ǽṹ�� */
typedef struct
{
    s16 x;
    s16 y;
    s16 z;
} Gyro_t;

/* HMC5883L--�����ƽṹ�� */
typedef struct
{
    s16 x;
    s16 y;
    s16 z;
} Mag_t;

/* float�ṹ�� */
typedef struct
{
    float x;
    float y;
    float z;
} Float_t;

/* ��̬����--�Ƕ�ֵ */
typedef struct
{
    float yaw;
    float roll;
    float pitch;
} Angle_t;

// ��������
float invSqrt(float x);
void CalibInit(void);
u8 Calib_Status(void);
void MPU6050_Offset(void);
void GY86_Read(Type_t type);
void Quat_Init(void);
void AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void AHRS_Time_Init(void);
float Get_AHRS_Time(void);
//void Apply_Deadband(float* value, float deadBand);

#endif
