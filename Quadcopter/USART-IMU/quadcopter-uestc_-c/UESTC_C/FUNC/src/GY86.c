#include "GY86.h"



/****************************************************************
 * 功能：MPU6050初始化
 * **************************************************************/
int MPU6050_Init(void)
{
    // 检查MPU6050是否正常
    if(I2C_READ_BYTE(MPU6050_Addr, MPU6050_WHO_AM_I) != MPU6050_Device_ID){
        return 0;
    }

    I2C_SAND_BYTE(MPU6050_Addr, MPU6050_PWR_MGMT_1, 0x00); //解除休眠状态,使用内部8MHz振荡器
    I2C_SAND_BYTE(MPU6050_Addr, MPU6050_SMPLRT_DIV, 0x00); //采样分频 (采样频率 = 陀螺仪输出频率 / (1+DIV)，采样频率1000hz）
    I2C_SAND_BYTE(MPU6050_Addr, MPU6050_CONFIG, 0x06); //设置低通滤波
    I2C_SAND_BYTE(MPU6050_Addr, MPU6050_GYRO_CONFIG, 0x18); //陀螺仪满量程+-2000度/秒 (最低分辨率 = 2^15/2000 = 16.4LSB/度/秒
    I2C_SAND_BYTE(MPU6050_Addr, MPU6050_ACCEL_CONFIG, 0x08); //加速度满量程+-4g   (最低分辨率 = 2^15/4g = 8192LSB/g )
    I2C_SAND_BYTE(MPU6050_Addr, MPU6050_INT_PIN_CFG, 0x02); //打开旁路模式
    I2C_SAND_BYTE(MPU6050_Addr, MPU6050_USER_CTRL, 0x00); //关闭主模式

    return 1;

}



/****************************************************************
 * 功能：HMC5883L初始化
 * **************************************************************/
void HMC5883L_Init(void)
{
    // 设置标准数据输出速率75HZ
    I2C_SAND_BYTE(HMC5883L_Addr, HMC5883L_CONFIG_A, 0x18);
    // 设置传感器磁场范围±1.3Ga
    I2C_SAND_BYTE(HMC5883L_Addr, HMC5883L_CONFIG_B, 0x20);
    // 打开continuous measurement模式
    I2C_SAND_BYTE(HMC5883L_Addr, HMC5883L_MODE, 0x00);
}



/****************************************************************
 * 功能：获取MPU6050数据
 * **************************************************************/
uint16_t GetData_MPU6050(uint8_t REG_Address)
{
    uint8_t H, L;
    H = I2C_READ_BYTE(MPU6050_Addr, REG_Address);
    L = I2C_READ_BYTE(MPU6050_Addr, REG_Address + 1);
    return (H << 8) | L; //合成数据
}



/****************************************************************
 * 功能：获取HMC5883L数据
 * **************************************************************/
uint16_t GetData_HMC5883L(uint8_t REG_Address)
{
    uint8_t H, L;    
    H = I2C_READ_BYTE(HMC5883L_Addr, REG_Address);
    L = I2C_READ_BYTE(HMC5883L_Addr, REG_Address + 1);
    return (H << 8) | L; //合成数据
}









