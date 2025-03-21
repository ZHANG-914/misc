#ifndef __IIC_H_
#define __IIC_H_

#include "includes.h"

#ifdef HARDWAREI2C

#define HostAddress 0xC0 //总线主机的器件地址
#define BusSpeed 100000  //总线速度（不高于400000）

int I2C_Configuration(void);
void I2C_SAND_BUFFER(u8 SlaveAddr, u8 WriteAddr, u8 *pBuffer, u16 NumByteToWrite);
void I2C_SAND_BYTE(u8 SlaveAddr, u8 writeAddr, u8 pBuffer);
void I2C_READ_BUFFER(u8 SlaveAddr, u8 readAddr, u8 *pBuffer, u16 NumByteToRead);
u8 I2C_READ_BYTE(u8 SlaveAddr, u8 readAddr);
#endif

#ifdef SOFTWAREI2C
// I2C SCL/SDA 引脚定义
#define I2C_SCL GPIO_Pin_9
#define I2C_SDA GPIO_Pin_8

// I2C SCL/SDA 设置高低电平
#define I2C_SCL_L GPIO_ResetBits(GPIOB, I2C_SCL)
#define I2C_SCL_H GPIO_SetBits(GPIOB, I2C_SCL)
#define I2C_SDA_L GPIO_ResetBits(GPIOB, I2C_SDA)
#define I2C_SDA_H GPIO_SetBits(GPIOB, I2C_SDA)

// I2C SDA 状态
#define I2C_SDA_STATE GPIO_ReadInputDataBit(GPIOB, I2C_SDA)

// I2C 状态
#define I2C_READY 0x00
#define I2C_BUS_BUSY 0x01
#define I2C_BUS_ERROR 0x02

// I2C ACK/NACK
#define I2C_NACK 0x00
#define I2C_ACK 0x01

// I2C nop （空操作，用以延时）
#define I2C_NOP delay_us(1)

// 函数定义
void IIC_Init(void);

void I2C_WriteByte(uint8_t DeviceAddr, uint8_t address, uint8_t data);
void I2C_NoAddr_WriteByte(uint8_t DeviceAddr, uint8_t data);

uint8_t I2C_ReadByte(uint8_t DeviceAddr, uint8_t address);
uint16_t I2C_Read_2Bytes(uint8_t DeviceAddr, uint8_t address);
uint32_t I2C_Read_3Bytes(uint8_t DeviceAddr, uint8_t address);

u8 i2cwrite(u8 dev_addr, u8 reg_addr, u8 i2c_len, u8 *i2c_data_buf);
u8 i2cread(u8 dev_addr, u8 reg_addr, u8 i2c_len, u8 *i2c_data_buf);
#endif
#endif
