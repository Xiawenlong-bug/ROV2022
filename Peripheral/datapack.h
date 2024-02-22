#ifndef _DATAPACK_H
#define _DATAPACK_H
#include "rov.h"

/*--------------------------数据包长度-------------------------*/
#define TX_JY901_BUFF_LEN 				36			//向上位机发送JY901姿态传感器数据包
#define TX_MS5837_BUFF_LEN 				16			//向上位机发送MS5837深度传感器数据包
#define TX_MOTOR_PWM_BUFF_LEN			24			//向上位机发送各推进器占空比数据包
#define RX_HANDLE_BUFF_LEN				16			//下位机接收的手柄参数
/*--------------------------数据头-------------------------*/
#define TX_StartBit_JY901					0xAA		//向上位机传输JY901姿态传感器数据
#define	TX_StartBit_MS5837				0xAB		//向上位机传输MS5837深度传感器数据
#define	TX_StartBit_PWM						0xAC		//向上位机传输MS5837深度传感器数据
#define RX_StartBit_HANDLE  			0xAD		//下位机接收的手柄数据


/*---------------------下位机到上位机----------------------*/
// JY901 参数数据共用体
typedef union 
{  
	struct
		{
			float AccelerationX;		//X轴加速度  
			float AccelerationY;     	//Y轴加速度  
			float AccelerationZ;     	//Z轴加速度  

			float AngleSpeedX;       //X轴角速度      
			float AngleSpeedY;       //Y轴角速度              
			float AngleSpeedZ;       //Z轴角速度

			float PitchAngle;        //俯仰角
			float YawAngle;        	 //偏航角
			float RollAngle;         //翻滚角
		}motiondata;
	uint8_t TX_JY901_BUFF[TX_JY901_BUFF_LEN];
}TX_JY901_Buff_Union;

//MS5837 深度传感器共用体
typedef union 
{
	struct
		{
			float Pressure;          		//压力
			float Depth;             		//深度
			float Temperature;       	  //温度
			float Offset;            		//水深修正补偿值
		}ms5837data;
	uint8_t TX_MS5837_BUFF[TX_MS5837_BUFF_LEN];
}TX_MS5837_Buff_Union;

//推进器
typedef union 
{
	struct
		{
			float pwm_motor1;          		
			float pwm_motor2;             		
			float pwm_motor3;       	  
			float pwm_motor4; 
			float pwm_motor5;       	  
			float pwm_motor6; 
		}motorpwmdata;
	uint8_t TX_PWM_BUFF[TX_MOTOR_PWM_BUFF_LEN];
}TX_PWM_Buff_Union;

void PackDataUp(uint8_t startbit);
#endif
