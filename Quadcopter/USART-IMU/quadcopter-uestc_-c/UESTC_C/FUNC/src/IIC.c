#include "iic.h"

void I2C_GPIO_Init(void){ //I2C接口初始化
		GPIO_InitTypeDef  GPIO_InitStructure; 	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);       
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE); //启动I2C功能  
		GPIO_InitStructure.GPIO_Pin = I2C_SCL | I2C_SDA; //选择端口号 
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_I2C1);	
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_I2C1);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //选择IO接口工作方式  
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_InitStructure.GPIO_PuPd= GPIO_PuPd_NOPULL;
	
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置IO接口速度（2/10/50MHz）    
	  GPIO_Init(I2CPORT, &GPIO_InitStructure);
}

int I2C_Configuration(void){ //I2C初始化
	I2C_InitTypeDef  I2C_InitStructure;
	I2C_GPIO_Init(); //先设置GPIO接口的状态
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;//设置为I2C模式
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = HostAddress; //主机地址（从机不得用此地址）
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;//允许应答
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; //7位地址模式
	I2C_InitStructure.I2C_ClockSpeed = BusSpeed; //总线速度设置 	
	I2C_Init(I2C1,&I2C_InitStructure);
	I2C_Cmd(I2C1,ENABLE);//开启I2C		

	return 1;
}

void I2C_SAND_BUFFER(u8 SlaveAddr,u8 WriteAddr,u8* pBuffer,u16 NumByteToWrite){ //I2C发送数据串（器件地址，内部地址，寄存器，数量）
	I2C_GenerateSTART(I2C1,ENABLE);//产生起始位
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)); //清除EV5
	I2C_Send7bitAddress(I2C1,SlaveAddr,I2C_Direction_Transmitter);//发送器件地址
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//清除EV6
	I2C_SendData(I2C1,WriteAddr); //内部功能地址
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));//移位寄存器非空，数据寄存器已空，产生EV8，发送数据到DR既清除该事件
	while(NumByteToWrite--){ //循环发送数据	
		I2C_SendData(I2C1,*pBuffer); //发送数据
		pBuffer++; //数据指针移位
		while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));//清除EV8
	}
	I2C_GenerateSTOP(I2C1,ENABLE);//产生停止信号
}
void I2C_SAND_BYTE(u8 SlaveAddr,u8 writeAddr,u8 pBuffer){ //I2C发送一个字节（从地址，内部地址，内容）
	I2C_GenerateSTART(I2C1,ENABLE); //发送开始信号
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)); //等待完成	
	I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Transmitter); //发送从器件地址及状态（写入）
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); //等待完成	
	I2C_SendData(I2C1,writeAddr); //发送从器件内部寄存器地址
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //等待完成	
	I2C_SendData(I2C1,pBuffer); //发送要写入的内容
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //等待完成	
	I2C_GenerateSTOP(I2C1,ENABLE); //发送结束信号
}
void I2C_READ_BUFFER(u8 SlaveAddr,u8 readAddr,u8* pBuffer,u16 NumByteToRead){ //I2C读取数据串（器件地址，寄存器，内部地址，数量）
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1,ENABLE);//开启信号
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));	//清除 EV5
	I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Transmitter); //写入器件地址
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//清除 EV6
	I2C_Cmd(I2C1,ENABLE);
	I2C_SendData(I2C1,readAddr); //发送读的地址
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //清除 EV8
	I2C_GenerateSTART(I2C1,ENABLE); //开启信号
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)); //清除 EV5
	I2C_Send7bitAddress(I2C1,SlaveAddr,I2C_Direction_Receiver); //将器件地址传出，主机为读
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)); //清除EV6
	while(NumByteToRead){
		if(NumByteToRead == 1){ //只剩下最后一个数据时进入 if 语句
			I2C_AcknowledgeConfig(I2C1,DISABLE); //最后有一个数据时关闭应答位
			I2C_GenerateSTOP(I2C1,ENABLE);	//最后一个数据时使能停止位
		}
		if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)){ //读取数据
			*pBuffer = I2C_ReceiveData(I2C1);//调用库函数将数据取出到 pBuffer
			pBuffer++; //指针移位
			NumByteToRead--; //字节数减 1 
		}
	}
	I2C_AcknowledgeConfig(I2C1,ENABLE);
}
u8 I2C_READ_BYTE(u8 SlaveAddr,u8 readAddr){ //I2C读取一个字节
	u8 a;
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));   //I2C等待总线不忙
	I2C_GenerateSTART(I2C1,ENABLE);							//产生一个起始信号
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));     //等待事件EV5，即起始信号已发送完毕
	I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Transmitter);   //发送读写地址，并设置传输方向为写入
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));    //等待从设备应答，产生EV6，EV8事件
	I2C_Cmd(I2C1,ENABLE);      //使能I2C总线
	I2C_SendData(I2C1,readAddr);    //发送从设备的寄存器地址
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));  //等待响应，等待事件EV8_2
	I2C_GenerateSTART(I2C1,ENABLE); //重起始信号
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));   //等待起始信号发送完毕，产生事件EV5
	I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Receiver);   //发送读写地址，并设置传输方向为读取
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));	 //等待从设备应答，产生事件6
	I2C_AcknowledgeConfig(I2C1,DISABLE); //关闭应答位
	I2C_GenerateSTOP(I2C1,ENABLE);	//发送停止信号
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED));  //等待数据发送过来，产生事件EV7
	a = I2C_ReceiveData(I2C1);
	I2C_AcknowledgeConfig(I2C1,ENABLE);
	return a;
}


 


/*
选择IO接口工作方式：
GPIO_Mode_AIN 模拟输入
GPIO_Mode_IN_FLOATING 浮空输入
GPIO_Mode_IPD 下拉输入
GPIO_Mode_IPU 上拉输入
GPIO_Mode_Out_PP 推挽输出
GPIO_Mode_Out_OD 开漏输出
GPIO_Mode_AF_PP 复用推挽输出
GPIO_Mode_AF_OD 复用开漏输出
*/

///****************************************************************
// * 功能：I2C初始化，软件模拟I2C
// * **************************************************************/
//void IIC_Init(void) 
//{
//    GPIO_InitTypeDef GPIO_InitStructure;

//    // 使能GPIOB时钟
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

//    // 开漏输出Open-drain output
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//    GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//    GPIO_Init(GPIOB, &GPIO_InitStructure);    
//}



///****************************************************************
// * 功能：I2C START
// * **************************************************************/
//u8 I2C_START(void)
//{
//    I2C_SDA_H;
//    I2C_NOP;

//    I2C_SCL_H;
//    I2C_NOP;

//    if (!I2C_SDA_STATE)
//        return I2C_BUS_BUSY;

//    I2C_SDA_L;
//    I2C_NOP;

//    I2C_SCL_L;
//    I2C_NOP;

//    if (I2C_SDA_STATE)
//        return I2C_BUS_ERROR;

//    return I2C_READY;
//}



///****************************************************************
// * 功能：I2C STOP
// * **************************************************************/
//void I2C_STOP(void)
//{
//    I2C_SDA_L;
//    I2C_NOP;

//    I2C_SCL_H;
//    I2C_NOP;

//    I2C_SDA_H;
//    I2C_NOP;
//}



///****************************************************************
// * 功能：I2C send ACK
// * **************************************************************/
//void I2C_SendACK(void)
//{
//    I2C_SDA_L;
//    I2C_NOP;
//    I2C_SCL_H;
//    I2C_NOP;
//    I2C_SCL_L;
//    I2C_NOP;
//}



///****************************************************************
// * 功能：I2C send NACK
// * **************************************************************/
//void I2C_SendNACK(void)
//{
//    I2C_SDA_H;
//    I2C_NOP;
//    I2C_SCL_H;
//    I2C_NOP;
//    I2C_SCL_L;
//    I2C_NOP;
//}



///****************************************************************
// * 功能：I2C send one byte
// * **************************************************************/
//u8 I2C_SendByte(u8 i2c_data)
//{
//    u8 i;

//    I2C_SCL_L;
//    for (i = 0; i < 8; i++) {
//        if (i2c_data & 0x80)
//            I2C_SDA_H;
//        else
//            I2C_SDA_L;

//        i2c_data <<= 1;
//        I2C_NOP;

//        I2C_SCL_H;
//        I2C_NOP;
//        I2C_SCL_L;
//        I2C_NOP;
//    }

//    I2C_SDA_H;
//    I2C_NOP;
//    I2C_SCL_H;
//    I2C_NOP;
//    if (I2C_SDA_STATE) {
//        I2C_SCL_L;
//        return I2C_NACK;
//    } else {
//        I2C_SCL_L;
//        return I2C_ACK;
//    }
//}



///****************************************************************
// * 功能：I2C receive one byte
// * **************************************************************/
//u8 I2C_ReceiveByte(void)
//{
//    u8 i, i2c_data;

//    I2C_SDA_H;
//    I2C_SCL_L;
//    i2c_data = 0;

//    for (i = 0; i < 8; i++) {
//        I2C_SCL_H;
//        I2C_NOP;
//        i2c_data <<= 1;

//        if (I2C_SDA_STATE)
//            i2c_data |= 0x01;

//        I2C_SCL_L;
//        I2C_NOP;
//    }
//    I2C_SendNACK();
//    return i2c_data;
//}



///****************************************************************
// * 功能：I2C receive one byte with ACK
// * **************************************************************/
//u8 I2C_ReceiveByte_WithACK(void)
//{
//    u8 i, i2c_data;

//    I2C_SDA_H;
//    I2C_SCL_L;
//    i2c_data = 0;

//    for (i = 0; i < 8; i++) {
//        I2C_SCL_H;
//        I2C_NOP;
//        i2c_data <<= 1;

//        if (I2C_SDA_STATE)
//            i2c_data |= 0x01;

//        I2C_SCL_L;
//        I2C_NOP;
//    }
//    I2C_SendACK();
//    return i2c_data;
//}



///****************************************************************
// * 功能：I2C写一个字节
// * **************************************************************/
//void I2C_WriteByte(uint8_t DeviceAddr, uint8_t address, uint8_t data)
//{
//    //注意DeviceAddr为原始地址左移一位后的地址
//    I2C_START();
//    I2C_SendByte(DeviceAddr);
//    I2C_SendByte(address);
//    I2C_SendByte(data);
//    I2C_STOP();
//}



///****************************************************************
// * 功能：I2C写一个字节（不带片内地址）
// * **************************************************************/
//void I2C_NoAddr_WriteByte(uint8_t DeviceAddr, uint8_t data)
//{
//    //注意DeviceAddr为原始地址左移一位后的地址
//    I2C_START();
//    I2C_SendByte(DeviceAddr);
//    I2C_SendByte(data);
//    I2C_STOP();
//}



///****************************************************************
// * 功能：I2C读一个字节
// * **************************************************************/
//uint8_t I2C_ReadByte(uint8_t DeviceAddr, uint8_t address)
//{
//    //注意DeviceAddr为原始地址左移一位后的地址
//    uint8_t i;
//    I2C_START();
//    I2C_SendByte(DeviceAddr);
//    I2C_SendByte(address);
//    I2C_START();
//    I2C_SendByte(DeviceAddr + 1);
//    i = I2C_ReceiveByte();
//    I2C_STOP();
//    return i;
//}



///****************************************************************
// * 功能：I2C读俩个字节
// * **************************************************************/
//uint16_t I2C_Read_2Bytes(uint8_t DeviceAddr, uint8_t address)
//{
//    //注意DeviceAddr为原始地址左移一位后的地址
//    uint8_t data_temp1, data_temp2;
//    uint16_t data_16;

//    I2C_START();
//    I2C_SendByte(DeviceAddr);
//    I2C_SendByte(address);
//    I2C_START();
//    I2C_SendByte(DeviceAddr + 1);
//    data_temp1 = I2C_ReceiveByte_WithACK();
//    data_temp2 = I2C_ReceiveByte();
//    I2C_STOP();

//    data_16 = (data_temp1 << 8) | data_temp2;
//    return data_16;
//}



///****************************************************************
// * 功能：I2C读三个字节
// * **************************************************************/
//uint32_t I2C_Read_3Bytes(uint8_t DeviceAddr, uint8_t address)
//{
//    //注意DeviceAddr为原始地址左移一位后的地址
//    uint8_t data_temp1, data_temp2, data_temp3;
//    uint32_t data_32;

//    I2C_START();
//    I2C_SendByte(DeviceAddr);
//    I2C_SendByte(address);
//    I2C_START();
//    I2C_SendByte(DeviceAddr + 1);
//    data_temp1 = I2C_ReceiveByte_WithACK();
//    data_temp2 = I2C_ReceiveByte_WithACK();
//    data_temp3 = I2C_ReceiveByte();
//    I2C_STOP();

//    data_32 = (data_temp1 << 16) | (data_temp2 << 8) | data_temp3;
//    return data_32;
//}



///****************************************************************
// * 功能：I2C写多个字节
// * **************************************************************/
//u8 i2cwrite(u8 dev_addr, u8 reg_addr, u8 i2c_len, u8* i2c_data_buf)
//{
//    //注意dev_addr为原始规定数据，未左移
//    u8 i;
//    I2C_START();
//    I2C_SendByte(dev_addr << 1 | I2C_Direction_Transmitter);
//    I2C_SendByte(reg_addr);
//    for (i = 0; i < i2c_len; i++)
//        I2C_SendByte(i2c_data_buf[i]);

//    I2C_STOP();
//    return 0x00;
//}



///****************************************************************
// * 功能：I2C读多个字节
// * **************************************************************/
//u8 i2cread(u8 dev_addr, u8 reg_addr, u8 i2c_len, u8* i2c_data_buf)
//{
//    //注意dev_addr为原始规定数据，未左移
//    I2C_START();
//    I2C_SendByte(dev_addr << 1 | I2C_Direction_Transmitter);
//    I2C_SendByte(reg_addr);
//    I2C_START();
//    I2C_SendByte(dev_addr << 1 | I2C_Direction_Receiver);

//    while (i2c_len) {
//        if (i2c_len == 1)
//            *i2c_data_buf = I2C_ReceiveByte();
//        else
//            *i2c_data_buf = I2C_ReceiveByte_WithACK();
//        i2c_data_buf++;
//        i2c_len--;
//    }
//    I2C_STOP();
//    return 0x00;
//}







