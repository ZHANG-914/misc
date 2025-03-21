#include "IMU.h"

/*******************************变量声明*********************************/
extern uint8_t gyroOffset, accOffset; //用于零偏校准
extern Acc_t acc, offsetAcc; //原始数据、零偏数据
extern Gyro_t gyro, offsetGyro; //原始数据、零偏数据
extern Mag_t mag; //原始数据
extern Float_t fGyro; //角速度数据（rad）
extern Angle_t angle; //姿态解算-角度值
extern float Temperature; //实际温度
extern OS_EVENT* IICMutex;



/****************************************************************
 * 功能：快速计算开根号的倒数
 * **************************************************************/
float invSqrt(float x)
{
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long*)(&y);
    i = 0x5f3759df - (i >> 1);
    y = *(float*)&i;
    y = y * (1.5f - (halfx * y * y));

    return y;
}



/****************************************************************
 * 功能：零偏校准初始化
 * **************************************************************/
void CalibInit(void)
{
    accOffset = 1;
    gyroOffset = 1;
}



/****************************************************************
 * 功能：检查零偏校准是否完成
 * 0：零偏校准完成
 * 1：零偏校准未完成
 * **************************************************************/
u8 Calib_Status(void)
{
    return accOffset|gyroOffset;
}



/****************************************************************
 * 功能：MPU6050零偏校准
 * **************************************************************/
void MPU6050_Offset(void)
{
    //磁力计无需校准，只需校准加速度计和陀螺仪

    //加速度计校准
    if(accOffset){
        static int32_t ACC_X=0, ACC_Y=0, ACC_Z=0;
        static int32_t count_acc=0;

        if(count_acc == 0){
            offsetAcc.x = 0;
            offsetAcc.y = 0;
            offsetAcc.z = 0;

            ACC_X = 0;
            ACC_Y = 0;
            ACC_Z = 0;

            count_acc = 1;

            return;
        }else{
            count_acc++;
            ACC_X += acc.x;
            ACC_Y += acc.y;
            ACC_Z += acc.z;
        }

        if (count_acc == 101)
        {
            count_acc--;

            offsetAcc.x = ACC_X / count_acc;
            offsetAcc.y = ACC_Y / count_acc;
            offsetAcc.z = ACC_Z / count_acc - 8192; //加速度量程±4G

            count_acc = 0;
            accOffset = 0;
        }
        
    }

    // 陀螺仪校准
    if(gyroOffset){
        static int32_t GYRO_X=0, GYRO_Y=0, GYRO_Z=0;
        static int32_t count_gyro = 0;
        if(count_gyro == 0){
            offsetGyro.x = 0;
            offsetGyro.y = 0;
            offsetGyro.z = 0;

            GYRO_X = 0;
            GYRO_Y = 0;
            GYRO_Z = 0;

            count_gyro = 1;

            return;
        }else{
            count_gyro++;
            GYRO_X += gyro.x;
            GYRO_Y += gyro.y;
            GYRO_Z += gyro.z;            
        }
        if(count_gyro == 101){
            count_gyro--;

            offsetGyro.x = GYRO_X / count_gyro;
            offsetGyro.y = GYRO_Y / count_gyro;
            offsetGyro.z = GYRO_Z / count_gyro;

            count_gyro = 0;
            gyroOffset = 0;
        }
    }
}



/****************************************************************
 * 功能：读取MPU6050数据
 * **************************************************************/
void GY86_Read(Type_t type)
{
    uint8_t dataBuf[14];
    INT8U err;

    //MPU6050
    OSMutexPend(IICMutex, 0, &err);
    I2C_READ_BUFFER(MPU6050_Addr_Real, MPU6050_ACCEL_XOUT_H, dataBuf, 14);
    OSMutexPost(IICMutex);

        acc.x = ((((int16_t)dataBuf[0]) << 8) | dataBuf[1]) - offsetAcc.x;
        acc.y = ((((int16_t)dataBuf[2]) << 8) | dataBuf[3]) - offsetAcc.y;
        acc.z = ((((int16_t)dataBuf[4]) << 8) | dataBuf[5]) - offsetAcc.z;
        gyro.x = ((((int16_t)dataBuf[8]) << 8) | dataBuf[9]) - offsetGyro.x;
        gyro.y = ((((int16_t)dataBuf[10]) << 8) | dataBuf[11]) - offsetGyro.y;
        gyro.z = ((((int16_t)dataBuf[12]) << 8) | dataBuf[13]) - offsetGyro.z;
        
        //角速度单位转换
        fGyro.x = (float)(gyro.x * RAW_TO_RAD);
        fGyro.y = (float)(gyro.y * RAW_TO_RAD);
        fGyro.z = (float)(gyro.z * RAW_TO_RAD);
    

    //HMC5883L
    OSMutexPend(IICMutex, 0, &err);
    //必须连续读完这六个数据，否则会导致隔很长一段时间才出新数据
    I2C_READ_BUFFER(HMC5883L_Addr_Real, HMC5883L_XOUT_MSB, dataBuf, 6);
        OSMutexPost(IICMutex);

        mag.x = (dataBuf[0] << 8) | dataBuf[1];
        mag.y = (dataBuf[4] << 8) | dataBuf[5];
        mag.z = (dataBuf[2] << 8) | dataBuf[3];

        // 读取的原数据为补码形式，这里完成转换
        if (mag.x > 0x7fff)
            mag.x -= 0xffff;
        if (mag.y > 0x7fff)
            mag.y -= 0xffff;
        if (mag.z > 0x7fff)
            mag.z -= 0xffff;
     

    MPU6050_Offset();   
}



/*******************************四元数参数*********************************/
float Kp = 2.0f; // 比例常数
float Ki = 0.005f; // 积分常数
float halfT = 0.0005f; //采样周期的一半，实际halfT由定时器求出
//float T = 0.001f; // 采样周期为1ms
float q0 = 1, q1 = 0, q2 = 0, q3 = 0; // 四元数
float exInt = 0, eyInt = 0, ezInt = 0; // 误差积分累计值


/****************************************************************
 * 功能：四元数初始化
 * **************************************************************/
//void Quat_Init(void)
//{
//    int16_t initMx, initMy, initMz;
//    float initYaw, initPitch, initRoll;

//    uint8_t dataBuf[14];

//    if(i2cread(HMC5883L_Addr_Real, HMC5883L_XOUT_MSB, 6, dataBuf)){
//        initMx = (dataBuf[0] << 8)| dataBuf[1];
//        initMy = (dataBuf[4] << 8)| dataBuf[5];
//        initMz = (dataBuf[2] << 8)| dataBuf[3];

//        if (initMx > 0x7fff)
//            initMx -= 0xffff;
//        if (initMy > 0x7fff)
//            initMy -= 0xffff;
//        if (initMz > 0x7fff)
//            initMz -= 0xffff;
//    }

    //初始欧拉角
//    initPitch = 0;
//    initRoll = 0;
//    initYaw = atan2(initMx * cos(initRoll) + initMy * sin(initRoll) * sin(initPitch) + initMz * sin(initRoll) * cos(initPitch), 
//                    initMy * cos(initPitch) - initMz * sin(initPitch));

    //四元数计算
//    q0 = cos(0.5f * initRoll) * cos(0.5f * initPitch) * cos(0.5f * initYaw) + sin(0.5f * initRoll) * sin(0.5f * initPitch) * sin(0.5f * initYaw); // w
//    q1 = cos(0.5f * initRoll) * sin(0.5f * initPitch) * cos(0.5f * initYaw) - sin(0.5f * initRoll) * cos(0.5f * initPitch) * sin(0.5f * initYaw); // x Pitch
//    q2 = sin(0.5f * initRoll) * cos(0.5f * initPitch) * cos(0.5f * initYaw) + cos(0.5f * initRoll) * sin(0.5f * initPitch) * sin(0.5f * initYaw); // y Roll
//    q3 = cos(0.5f * initRoll) * cos(0.5f * initPitch) * sin(0.5f * initYaw) - sin(0.5f * initRoll) * sin(0.5f * initPitch) * cos(0.5f * initYaw); // z Yaw    
//}








/****************************************************************
 * 功能：获取halfT时间
 * **************************************************************/
float Get_AHRS_Time(void)
{
    float temp = 0;
    static uint32_t now = 0;

    // 获取计数器值
    now = TIM2->CNT;
    // 清空计数器值
    TIM2->CNT = 0;
    // 计数器值转换为时间并除以2
    temp = (float)now / 2000000.0f;

    return temp;
}



/****************************************************************
 * 功能：AHRS姿态解算算法
 * **************************************************************/
void AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz)
{
    float norm;
    float hx, hy, hz, bx, bz;
    float vx, vy, vz, wx, wy, wz;
    float ex, ey, ez;


    // auxiliary variables to reduce number of repeated operations
    float q0q0 = q0*q0;
    float q0q1 = q0*q1;
    float q0q2 = q0*q2;
    float q0q3 = q0*q3;
    float q1q1 = q1*q1;
    float q1q2 = q1*q2;
    float q1q3 = q1*q3;
    float q2q2 = q2*q2;   
    float q2q3 = q2*q3;
    float q3q3 = q3*q3;          
        
    // 加速度计和磁力计归一化
    norm = invSqrt(ax*ax + ay*ay + az*az);       
    ax = ax * norm;
    ay = ay * norm;
    az = az * norm;
    norm = invSqrt(mx*mx + my*my + mz*mz);          
    mx = mx * norm;
    my = my * norm;
    mz = mz * norm;         
        
    // compute reference direction of flux
    // 计算地理坐标系下磁力坐标(地理南北极)
    hx = 2*mx*(0.5f - q2q2 - q3q3) + 2*my*(q1q2 - q0q3) + 2*mz*(q1q3 + q0q2);
    hy = 2*mx*(q1q2 + q0q3) + 2*my*(0.5f - q1q1 - q3q3) + 2*mz*(q2q3 - q0q1);
    hz = 2*mx*(q1q3 - q0q2) + 2*my*(q2q3 + q0q1) + 2*mz*(0.5f - q1q1 - q2q2); 
    // (地磁南北极)因为地磁南北极与地理南北极有偏差
    bx = sqrt((hx*hx) + (hy*hy));
    bz = hz;        
        
    // estimated direction of gravity and flux (v and w)
    vx = 2*(q1q3 - q0q2);
    vy = 2*(q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;
    wx = 2*bx*(0.5f - q2q2 - q3q3) + 2*bz*(q1q3 - q0q2);
    wy = 2*bx*(q1q2 - q0q3) + 2*bz*(q0q1 + q2q3);
    wz = 2*bx*(q0q2 + q1q3) + 2*bz*(0.5f - q1q1 - q2q2);  
        
    // error is sum of cross product between reference direction of fields and direction measured by sensors
    ex = (ay*vz - az*vy) + (my*wz - mz*wy);
    ey = (az*vx - ax*vz) + (mz*wx - mx*wz);
    ez = (ax*vy - ay*vx) + (mx*wy - my*wx);
        
    // integral error scaled integral gain
    exInt = exInt + ex*Ki;
    eyInt = eyInt + ey*Ki;
    ezInt = ezInt + ez*Ki;
        
    // adjusted gyroscope measurements
    gx = gx + Kp*ex + exInt;
    gy = gy + Kp*ey + eyInt;
    gz = gz + Kp*ez + ezInt;

    //由定时器获取采样周期的一半
    halfT = Get_AHRS_Time();
        
    // integrate quaternion rate and normalise
    q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
    q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
    q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
    q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;  
        
    // normalise quaternion
    norm = invSqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
    q0 = q0 * norm;
    q1 = q1 * norm;
    q2 = q2 * norm;
    q3 = q3 * norm;

    //四元数转欧拉角
    angle.yaw = atan2(2*q1*q2 + 2*q0*q3, -2*q2*q2 - 2*q3*q3 + 1)*RAD_TO_ANGLE;  //YAW
    angle.pitch = asin(-2*q1*q3 + 2*q0*q2)*RAD_TO_ANGLE;  //PITCH
    angle.roll = atan2(2*q2*q3 + 2*q0*q1, -2*q1*q1 - 2*q2*q2 + 1)*RAD_TO_ANGLE;  //ROLL
}

void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz)
{
    float norm;
    float hx, hy, hz, bx, bz;
    float wx, wy, wz;
    float vx, vy, vz;
    float ex, ey, ez;

    // 先把这些用得到的值算好
    float q0q0 = q0*q0;
    float q0q1 = q0*q1;
    float q0q2 = q0*q2;
    float q0q3 = q0*q3;
    float q1q1 = q1*q1;
    float q1q2 = q1*q2;
    float q1q3 = q1*q3;
    float q2q2 = q2*q2;
    float q2q3 = q2*q3;
    float q3q3 = q3*q3;

    if(ax*ay*az==0)
        return;

    if(mx*my*mz == 0)
        return;

    norm = sqrt(ax*ax + ay*ay + az*az);       //acc数据归一化
    ax = ax / norm;
    ay = ay / norm;
    az = az / norm;

    norm = sqrt(mx*mx + my*my + mz*mz);       //mag数据归一化
    mx = mx / norm;
    my = my / norm;
    mz = mz / norm;

    //  mx = 0;
    //  my = 0;
    //  mz = 0;

    hx = 2 * mx * (0.5 - q2q2 - q3q3) + 2 * my * (q1q2 - q0q3) + 2 * mz * (q1q3 + q0q2);  
    hy = 2 * mx * (q1q2 + q0q3) + 2 * my * (0.5 - q1q1 - q3q3) + 2 * mz * (q2q3 - q0q1);  
    hz = 2 * mx * (q1q3 - q0q2) + 2 * my * (q2q3 + q0q1) + 2 * mz * (0.5 - q1q1 -q2q2);          
    bx = sqrt((hx*hx) + (hy*hy));  
    bz = hz;

    // estimated direction of gravity and flux (v and w)              估计重力方向和流量/变迁
    vx = 2*(q1q3 - q0q2);                                             //四元素中xyz的表示
    vy = 2*(q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3 ;

    wx = 2 * bx * (0.5 - q2q2 - q3q3) + 2 * bz * (q1q3 - q0q2);  
    wy = 2 * bx * (q1q2 - q0q3) + 2 * bz * (q0q1 + q2q3);  
    wz = 2 * bx * (q0q2 + q1q3) + 2 * bz * (0.5 - q1q1 - q2q2); 

    // error is sum of cross product between reference direction of fields and direction measured by sensors
    //  ex = (ay*vz - az*vy) ;                                               //向量外积在相减得到差分就是误差
    //  ey = (az*vx - ax*vz) ;
    //  ez = (ax*vy - ay*vx) ;

    ex = (ay*vz - az*vy) + (my*wz - mz*wy);  
    ey = (az*vx - ax*vz) + (mz*wx - mx*wz);  
    ez = (ax*vy - ay*vx) + (mx*wy - my*wx);

    exInt = exInt + ex * Ki;                                //对误差进行积分
    eyInt = eyInt + ey * Ki;
    ezInt = ezInt + ez * Ki;

    // adjusted gyroscope measurements
    gx = gx + Kp*ex + exInt;                                              //将误差PI后补偿到陀螺仪，即补偿零点漂移
    gy = gy + Kp*ey + eyInt;
    gz = gz + Kp*ez + ezInt;                                          //这里的gz由于没有观测者进行矫正会产生漂移，表现出来的就是积分自增或自减


		halfT = Get_AHRS_Time();
		
    // integrate quaternion rate and normalise                           //四元素的微分方程
    q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
    q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
    q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
    q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;

    // normalise quaternion
    norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
    q0 = q0 / norm;
    q1 = q1 / norm;
    q2 = q2 / norm;
    q3 = q3 / norm;

    angle.yaw = atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2*q2 - 2 * q3* q3 + 1)* 57.3; // yaw
    angle.pitch  = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; // pitch
    angle.roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
}