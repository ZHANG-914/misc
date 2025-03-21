#include "usart.h"
#include "GY86.h"
#include "MPU6050.h"


int HMC_Init(void)
{

		I2C_SAND_BYTE(HMC_ADD,HMC_CONFIGA,0x50);   //01010000/采样平均数4，输出速率15，正常测量配置
		I2C_SAND_BYTE(HMC_ADD,HMC_CONFIGB,0xE0);   //11100000/将增益调至最小
		I2C_SAND_BYTE(HMC_ADD,HMC_MODE,0x00);    //00000000/设置为连续模式
	
		return 1;
}


int GY86_Init(void)
{
//		u8 a[2];
		int mpu6050 = MPU6050_Init();
		I2C_SAND_BYTE(MPU_ADD,MPU_CFG,0x02);     //将MPU的CFG寄存器的第二位设置为1，其他位在使用MPU时配置
		I2C_SAND_BYTE(MPU_ADD,MPU_CTRL,0x00);     //将MPU的CTRL寄存器的第六位设置为0，与上面一步共同开启bypass模式
		delay_ms(111);
		int hmc = HMC_Init();				//HMC初始化
	
		if(mpu6050 && hmc)
			return 1;
		else
			return 0;
}


Mag_t READ_HMCALL(Mag_t mag)
{
//		u8 i;
		u8 dataBuf[14];
//		u16 n[3];
		I2C_READ_BUFFER(HMC_ADD,HMC_DATA_XMSB,dataBuf,6);
//		for(i=0;i<3;i++)
//		{
//				n[i]=(t[2*i]<<8)+t[2*i+1];
//		}
		
    mag.x = (dataBuf[0] << 8) | dataBuf[1];
    mag.y = (dataBuf[4] << 8) | dataBuf[5];
    mag.z = (dataBuf[2] << 8) | dataBuf[3];
	
        if (mag.x > 0x7fff)
            mag.x -= 0xffff;
        if (mag.y > 0x7fff)
            mag.y -= 0xffff;
        if (mag.z > 0x7fff)
            mag.z -= 0xffff;
		
		return mag;
}

