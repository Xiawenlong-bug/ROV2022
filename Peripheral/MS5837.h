#ifndef __MS5837_H
#define __MS5837_H
#include "rov.h"

#define 		MS5837_ADDRESS				0xec
#define 		MS5837_ReadBuffer			I2C_ReadBuffer
#define			MS5837_WriteBuffer		I2C_WriteBuffer
#define			MS5837_ReadByte				I2C_Single_Read
#define			MS5837_WriteByte			I2C_Single_Write



void MS5837_Init(void) ;
void MS5837_Read(void) ;
float MS5837_pressure(float conversion) ;
float MS5837_temperature(void) ;
float MS5837_depth(void) ;
void MS5837_SetOffset(float offset);




/********************************************MS5837数据结构体********************************************/
typedef struct 
{
	float depth;
	float temp;
	float pressure;
	float offset;
}MS5837_ValueTypeDef;//深度传感器数据结构体

extern MS5837_ValueTypeDef MS5837;

#endif
