#ifndef _JY901_H
#define _JY901_H
#include "rov.h"

//传感器数据结构类型声明
typedef struct 
{

	float acc_x;//角速度
	float acc_y;
	float acc_z;
	
	float gyro_x;//加速度
	float gyro_y;
	float gyro_z;	
	
	float angle_x;//角度
	float angle_y;
	float angle_z;//用来存储当前传感器数据
	
}JY901_ValTypedef;
extern JY901_ValTypedef JY901;

//三轴加速度
struct SAcc
{
	short a[3];//每个short类型两个字节，因此可以将读取的数据高低字节转换成一个有符号short类型
	short T;
};
extern struct SAcc stcAcc;


//三轴角速度
struct SGyro
{
	short w[3];
	short T;
};
extern struct SGyro stcGyro;

//三轴角度
struct SAngle
{
	short Angle[3];
	short T;
};
extern struct SAngle stcAngle;
extern	JY901_ValTypedef JY901;
extern void JY901_DataReceive(uint8_t ucData);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif
