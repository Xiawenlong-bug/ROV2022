#ifndef _I2C_SIMU_H_
#define _I2C_SIMU_H_

#include "rov.h"

typedef struct
{
	GPIO_TypeDef * SCL_GPIO_Port;
	GPIO_TypeDef * SDA_GPIO_Port;
	uint32_t SCL_GPIO_CLK;
	uint32_t SDA_GPIO_CLK;
	uint32_t SCL_Pin;
	uint32_t SDA_Pin;
}IIC_STRUCT;

//extern IIC_STRUCT IIC1;

#define SCL_H(a)        a.SCL_GPIO_Port->BSRR = a.SCL_Pin 
#define SCL_L(a)        a.SCL_GPIO_Port->BRR  = a.SCL_Pin 

#define SDA_H(a)       	a.SDA_GPIO_Port->BSRR = a.SDA_Pin
#define SDA_L(a)        a.SDA_GPIO_Port->BRR  = a.SDA_Pin

#define SCL_read(a)     a.SCL_GPIO_Port->IDR  & a.SCL_Pin 
#define SDA_read(a)     a.SDA_GPIO_Port->IDR  & a.SDA_Pin

#define I2C_WR	0		/* Ð´¿ØÖÆbit */
#define I2C_RD	1		/* ¶Á¿ØÖÆbit */



void I2C_Simu_Port_Init(IIC_STRUCT *I2C);
void I2C_delay(void);
void I2C_delay_ms(uint32_t time);
void I2C_Ack(IIC_STRUCT I2C);
void I2C_NoAck(IIC_STRUCT I2C);
uint8_t I2C_Start(IIC_STRUCT I2C);
void I2C_Stop(IIC_STRUCT I2C);
uint8_t I2C_WaitAck(IIC_STRUCT I2C);
void I2C_WriteByte(IIC_STRUCT I2C,uint8_t WriteByte);
uint8_t I2C_ReadByte(IIC_STRUCT I2C);
uint8_t I2C_Single_Write(IIC_STRUCT I2C,unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
uint8_t I2C_Single_Read(IIC_STRUCT I2C,unsigned char SlaveAddress,unsigned char REG_Address);
uint8_t I2C_CheckDevice(IIC_STRUCT I2C,uint8_t adress);
uint8_t I2C_WriteBuffer(IIC_STRUCT I2C,uint8_t addr, uint8_t * data,uint8_t len);
uint8_t I2C_ReadBuffer(IIC_STRUCT I2C,uint8_t addr, uint8_t* pBuffer, uint8_t readAddr, uint16_t NumByteToRead);

#endif

