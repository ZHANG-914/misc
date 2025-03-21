#include "i2c.h"

#ifdef HARDWAREI2C
void I2C_GPIO_Init(void)
{ //I2C�ӿڳ�ʼ��
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C3, ENABLE); //����I2C����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	 //ѡ��˿ں�
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_I2C3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_I2C3);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //ѡ��IO�ӿڹ�����ʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶȣ�2/10/50MHz��
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	 //ѡ��˿ں�
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

int I2C_Configuration(void)
{ //I2C��ʼ��
	I2C_InitTypeDef I2C_InitStructure;
	I2C_GPIO_Init();						   //������GPIO�ӿڵ�״̬
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C; //����ΪI2Cģʽ
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = HostAddress;						  //������ַ���ӻ������ô˵�ַ��
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;								  //����Ӧ��
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; //7λ��ַģʽ
	I2C_InitStructure.I2C_ClockSpeed = BusSpeed;							  //�����ٶ�����
	I2C_Init(I2C3, &I2C_InitStructure);
	I2C_Cmd(I2C3, ENABLE); //����I2C

	return 1;
}

void I2C_SAND_BUFFER(u8 SlaveAddr, u8 WriteAddr, u8 *pBuffer, u16 NumByteToWrite)
{									 //I2C�������ݴ���������ַ���ڲ���ַ���Ĵ�����������
	I2C_GenerateSTART(I2C3, ENABLE); //������ʼλ
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_MODE_SELECT))
		;															 //���EV5
	I2C_Send7bitAddress(I2C3, SlaveAddr, I2C_Direction_Transmitter); //����������ַ
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
		;						   //���EV6
	I2C_SendData(I2C3, WriteAddr); //�ڲ����ܵ�ַ
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		; //��λ�Ĵ����ǿգ����ݼĴ����ѿգ�����EV8���������ݵ�DR��������¼�
	while (NumByteToWrite--)
	{								  //ѭ����������
		I2C_SendData(I2C3, *pBuffer); //��������
		pBuffer++;					  //����ָ����λ
		while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
			; //���EV8
	}
	I2C_GenerateSTOP(I2C3, ENABLE); //����ֹͣ�ź�
}
void I2C_SAND_BYTE(u8 SlaveAddr, u8 writeAddr, u8 pBuffer)
{									 //I2C����һ���ֽڣ��ӵ�ַ���ڲ���ַ�����ݣ�
	I2C_GenerateSTART(I2C3, ENABLE); //���Ϳ�ʼ�ź�
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_MODE_SELECT))
		;															 //�ȴ����
	I2C_Send7bitAddress(I2C3, SlaveAddr, I2C_Direction_Transmitter); //���ʹ�������ַ��״̬��д�룩
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
		;						   //�ȴ����
	I2C_SendData(I2C3, writeAddr); //���ʹ������ڲ��Ĵ�����ַ
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		;						 //�ȴ����
	I2C_SendData(I2C3, pBuffer); //����Ҫд�������
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		;							//�ȴ����
	I2C_GenerateSTOP(I2C3, ENABLE); //���ͽ����ź�
}
void I2C_READ_BUFFER(u8 SlaveAddr, u8 readAddr, u8 *pBuffer, u16 NumByteToRead)
{ //I2C��ȡ���ݴ���������ַ���Ĵ������ڲ���ַ��������
	while (I2C_GetFlagStatus(I2C3, I2C_FLAG_BUSY))
		;
	I2C_GenerateSTART(I2C3, ENABLE); //�����ź�
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_MODE_SELECT))
		;															 //��� EV5
	I2C_Send7bitAddress(I2C3, SlaveAddr, I2C_Direction_Transmitter); //д��������ַ
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
		; //��� EV6
	I2C_Cmd(I2C3, ENABLE);
	I2C_SendData(I2C3, readAddr); //���Ͷ��ĵ�ַ
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		;							 //��� EV8
	I2C_GenerateSTART(I2C3, ENABLE); //�����ź�
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_MODE_SELECT))
		;														  //��� EV5
	I2C_Send7bitAddress(I2C3, SlaveAddr, I2C_Direction_Receiver); //��������ַ����������Ϊ��
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
		; //���EV6
	while (NumByteToRead)
	{
		if (NumByteToRead == 1)
		{										  //ֻʣ�����һ������ʱ���� if ���
			I2C_AcknowledgeConfig(I2C3, DISABLE); //�����һ������ʱ�ر�Ӧ��λ
			I2C_GenerateSTOP(I2C3, ENABLE);		  //���һ������ʱʹ��ֹͣλ
		}
		if (I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_BYTE_RECEIVED))
		{									  //��ȡ����
			*pBuffer = I2C_ReceiveData(I2C3); //���ÿ⺯��������ȡ���� pBuffer
			pBuffer++;						  //ָ����λ
			NumByteToRead--;				  //�ֽ����� 1
		}
	}
	I2C_AcknowledgeConfig(I2C3, ENABLE);
}
u8 I2C_READ_BYTE(u8 SlaveAddr, u8 readAddr)
{ //I2C��ȡһ���ֽ�
	u8 a;
	while (I2C_GetFlagStatus(I2C3, I2C_FLAG_BUSY))
		;							 //I2C�ȴ����߲�æ
	I2C_GenerateSTART(I2C3, ENABLE); //����һ����ʼ�ź�
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_MODE_SELECT))
		;															 //�ȴ��¼�EV5������ʼ�ź��ѷ������
	I2C_Send7bitAddress(I2C3, SlaveAddr, I2C_Direction_Transmitter); //���Ͷ�д��ַ�������ô��䷽��Ϊд��
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
		;						  //�ȴ����豸Ӧ�𣬲���EV6��EV8�¼�
	I2C_Cmd(I2C3, ENABLE);		  //ʹ��I2C����
	I2C_SendData(I2C3, readAddr); //���ʹ��豸�ļĴ�����ַ
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		;							 //�ȴ���Ӧ���ȴ��¼�EV8_2
	I2C_GenerateSTART(I2C3, ENABLE); //����ʼ�ź�
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_MODE_SELECT))
		;														  //�ȴ���ʼ�źŷ�����ϣ������¼�EV5
	I2C_Send7bitAddress(I2C3, SlaveAddr, I2C_Direction_Receiver); //���Ͷ�д��ַ�������ô��䷽��Ϊ��ȡ
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
		;								  //�ȴ����豸Ӧ�𣬲����¼�6
	I2C_AcknowledgeConfig(I2C3, DISABLE); //�ر�Ӧ��λ
	I2C_GenerateSTOP(I2C3, ENABLE);		  //����ֹͣ�ź�
	while (!I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_BYTE_RECEIVED))
		; //�ȴ����ݷ��͹����������¼�EV7
	a = I2C_ReceiveData(I2C3);
	I2C_AcknowledgeConfig(I2C3, ENABLE);
	return a;
}
#endif

/*
ѡ��IO�ӿڹ�����ʽ��
GPIO_Mode_AIN ģ������
GPIO_Mode_IN_FLOATING ��������
GPIO_Mode_IPD ��������
GPIO_Mode_IPU ��������
GPIO_Mode_Out_PP �������
GPIO_Mode_Out_OD ��©���
GPIO_Mode_AF_PP �����������
GPIO_Mode_AF_OD ���ÿ�©���
*/

#ifdef SOFTWAREI2C
/****************************************************************
* ���ܣ�I2C��ʼ�������ģ��I2C
* **************************************************************/
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// ʹ��GPIOBʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	// ��©���Open-drain output
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/****************************************************************
* ���ܣ�I2C START
* **************************************************************/
u8 I2C_START(void)
{
	I2C_SDA_H;
	I2C_NOP;

	I2C_SCL_H;
	I2C_NOP;

	if (!I2C_SDA_STATE)
		return I2C_BUS_BUSY;

	I2C_SDA_L;
	I2C_NOP;

	I2C_SCL_L;
	I2C_NOP;

	if (I2C_SDA_STATE)
		return I2C_BUS_ERROR;

	return I2C_READY;
}

/****************************************************************
* ���ܣ�I2C STOP
* **************************************************************/
void I2C_STOP(void)
{
	I2C_SDA_L;
	I2C_NOP;

	I2C_SCL_H;
	I2C_NOP;

	I2C_SDA_H;
	I2C_NOP;
}

/****************************************************************
* ���ܣ�I2C send ACK
* **************************************************************/
void I2C_SendACK(void)
{
	I2C_SDA_L;
	I2C_NOP;
	I2C_SCL_H;
	I2C_NOP;
	I2C_SCL_L;
	I2C_NOP;
}

/****************************************************************
* ���ܣ�I2C send NACK
* **************************************************************/
void I2C_SendNACK(void)
{
	I2C_SDA_H;
	I2C_NOP;
	I2C_SCL_H;
	I2C_NOP;
	I2C_SCL_L;
	I2C_NOP;
}

/****************************************************************
* ���ܣ�I2C send one byte
* **************************************************************/
u8 I2C_SendByte(u8 i2c_data)
{
	u8 i;

	I2C_SCL_L;
	for (i = 0; i < 8; i++)
	{
		if (i2c_data & 0x80)
			I2C_SDA_H;
		else
			I2C_SDA_L;

		i2c_data <<= 1;
		I2C_NOP;

		I2C_SCL_H;
		I2C_NOP;
		I2C_SCL_L;
		I2C_NOP;
	}

	I2C_SDA_H;
	I2C_NOP;
	I2C_SCL_H;
	I2C_NOP;
	if (I2C_SDA_STATE)
	{
		I2C_SCL_L;
		return I2C_NACK;
	}
	else
	{
		I2C_SCL_L;
		return I2C_ACK;
	}
}

/****************************************************************
* ���ܣ�I2C receive one byte
* **************************************************************/
u8 I2C_ReceiveByte(void)
{
	u8 i, i2c_data;

	I2C_SDA_H;
	I2C_SCL_L;
	i2c_data = 0;

	for (i = 0; i < 8; i++)
	{
		I2C_SCL_H;
		I2C_NOP;
		i2c_data <<= 1;

		if (I2C_SDA_STATE)
			i2c_data |= 0x01;

		I2C_SCL_L;
		I2C_NOP;
	}
	I2C_SendNACK();
	return i2c_data;
}

/****************************************************************
* ���ܣ�I2C receive one byte with ACK
* **************************************************************/
u8 I2C_ReceiveByte_WithACK(void)
{
	u8 i, i2c_data;

	I2C_SDA_H;
	I2C_SCL_L;
	i2c_data = 0;

	for (i = 0; i < 8; i++)
	{
		I2C_SCL_H;
		I2C_NOP;
		i2c_data <<= 1;

		if (I2C_SDA_STATE)
			i2c_data |= 0x01;

		I2C_SCL_L;
		I2C_NOP;
	}
	I2C_SendACK();
	return i2c_data;
}

/****************************************************************
* ���ܣ�I2Cдһ���ֽ�
* **************************************************************/
void I2C_WriteByte(uint8_t DeviceAddr, uint8_t address, uint8_t data)
{
	//ע��DeviceAddrΪԭʼ��ַ����һλ��ĵ�ַ
	I2C_START();
	I2C_SendByte(DeviceAddr);
	I2C_SendByte(address);
	I2C_SendByte(data);
	I2C_STOP();
}

/****************************************************************
* ���ܣ�I2Cдһ���ֽڣ�����Ƭ�ڵ�ַ��
* **************************************************************/
void I2C_NoAddr_WriteByte(uint8_t DeviceAddr, uint8_t data)
{
	//ע��DeviceAddrΪԭʼ��ַ����һλ��ĵ�ַ
	I2C_START();
	I2C_SendByte(DeviceAddr);
	I2C_SendByte(data);
	I2C_STOP();
}

/****************************************************************
* ���ܣ�I2C��һ���ֽ�
* **************************************************************/
uint8_t I2C_ReadByte(uint8_t DeviceAddr, uint8_t address)
{
	//ע��DeviceAddrΪԭʼ��ַ����һλ��ĵ�ַ
	uint8_t i;
	I2C_START();
	I2C_SendByte(DeviceAddr);
	I2C_SendByte(address);
	I2C_START();
	I2C_SendByte(DeviceAddr + 1);
	i = I2C_ReceiveByte();
	I2C_STOP();
	return i;
}

/****************************************************************
* ���ܣ�I2C�������ֽ�
* **************************************************************/
uint16_t I2C_Read_2Bytes(uint8_t DeviceAddr, uint8_t address)
{
	//ע��DeviceAddrΪԭʼ��ַ����һλ��ĵ�ַ
	uint8_t data_temp1, data_temp2;
	uint16_t data_16;

	I2C_START();
	I2C_SendByte(DeviceAddr);
	I2C_SendByte(address);
	I2C_START();
	I2C_SendByte(DeviceAddr + 1);
	data_temp1 = I2C_ReceiveByte_WithACK();
	data_temp2 = I2C_ReceiveByte();
	I2C_STOP();

	data_16 = (data_temp1 << 8) | data_temp2;
	return data_16;
}

/****************************************************************
* ���ܣ�I2C�������ֽ�
* **************************************************************/
uint32_t I2C_Read_3Bytes(uint8_t DeviceAddr, uint8_t address)
{
	//ע��DeviceAddrΪԭʼ��ַ����һλ��ĵ�ַ
	uint8_t data_temp1, data_temp2, data_temp3;
	uint32_t data_32;

	I2C_START();
	I2C_SendByte(DeviceAddr);
	I2C_SendByte(address);
	I2C_START();
	I2C_SendByte(DeviceAddr + 1);
	data_temp1 = I2C_ReceiveByte_WithACK();
	data_temp2 = I2C_ReceiveByte_WithACK();
	data_temp3 = I2C_ReceiveByte();
	I2C_STOP();

	data_32 = (data_temp1 << 16) | (data_temp2 << 8) | data_temp3;
	return data_32;
}

/****************************************************************
* ���ܣ�I2Cд����ֽ�
* **************************************************************/
u8 i2cwrite(u8 dev_addr, u8 reg_addr, u8 i2c_len, u8 *i2c_data_buf)
{
	//ע��dev_addrΪԭʼ�涨���ݣ�δ����
	u8 i;
	I2C_START();
	I2C_SendByte(dev_addr << 1 | I2C_Direction_Transmitter);
	I2C_SendByte(reg_addr);
	for (i = 0; i < i2c_len; i++)
		I2C_SendByte(i2c_data_buf[i]);

	I2C_STOP();
	return 0x00;
}

/****************************************************************
* ���ܣ�I2C������ֽ�
* **************************************************************/
u8 i2cread(u8 dev_addr, u8 reg_addr, u8 i2c_len, u8 *i2c_data_buf)
{
	//ע��dev_addrΪԭʼ�涨���ݣ�δ����
	I2C_START();
	I2C_SendByte(dev_addr << 1 | I2C_Direction_Transmitter);
	I2C_SendByte(reg_addr);
	I2C_START();
	I2C_SendByte(dev_addr << 1 | I2C_Direction_Receiver);

	while (i2c_len)
	{
		if (i2c_len == 1)
			*i2c_data_buf = I2C_ReceiveByte();
		else
			*i2c_data_buf = I2C_ReceiveByte_WithACK();
		i2c_data_buf++;
		i2c_len--;
	}
	I2C_STOP();
	return 0x00;
}
#endif
