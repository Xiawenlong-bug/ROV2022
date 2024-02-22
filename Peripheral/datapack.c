#include "datapack.h"

void PackDataUp(uint8_t startbit)
{
	uint8_t i;
	uint8_t checkbit=(0x00)^startbit;	//校验位
	
	TX_JY901_Buff_Union 		TX_JY901_Data;
	TX_MS5837_Buff_Union 		TX_MS5837_Data;	
	TX_PWM_Buff_Union				TX_PWM_Data;
	switch(startbit)
	{
		case(TX_StartBit_JY901):
		{
			//将相关数据赋值给共用体内相应成员
			TX_JY901_Data.motiondata.AccelerationX	 = JY901.acc_x;//加速度
			TX_JY901_Data.motiondata.AccelerationY	 = JY901.acc_y;
			TX_JY901_Data.motiondata.AccelerationZ	 = JY901.acc_z;
			TX_JY901_Data.motiondata.AngleSpeedX = JY901.gyro_x;//角速度
  		TX_JY901_Data.motiondata.AngleSpeedY = JY901.gyro_y;
			TX_JY901_Data.motiondata.AngleSpeedZ = JY901.gyro_z;
			TX_JY901_Data.motiondata.PitchAngle	 = JY901.angle_x;//角度
			TX_JY901_Data.motiondata.YawAngle	   = JY901.angle_y;
			TX_JY901_Data.motiondata.RollAngle	 = JY901.angle_z;
			HAL_UART_Transmit(&huart1, (uint8_t *)startbit, 1, 0xffff);   
			for(i=0;i<TX_JY901_BUFF_LEN;i++)
			{
				HAL_UART_Transmit(&huart1, (uint8_t *)TX_JY901_Data.TX_JY901_BUFF[i], 1, 0xffff);
				checkbit ^=TX_JY901_Data.TX_JY901_BUFF[i];//同时将每个字节加到校验码上
				
			}
			HAL_UART_Transmit(&huart1, (uint8_t *)checkbit, 1, 0xffff);	
			break;	
		}
		case(TX_StartBit_MS5837):
		{
			//将相关数据赋值给共用体内相应成员			TX_MS5837_Data.ms5837data.depth		 = MS5837_Val.depth;
			TX_MS5837_Data.ms5837data.Temperature		 = MS5837.temp;
			TX_MS5837_Data.ms5837data.Pressure = MS5837.pressure;
			TX_MS5837_Data.ms5837data.Offset	 = MS5837.offset;
			
			//数据打包发送
			HAL_UART_Transmit(&huart1, (uint8_t *)startbit, 1, 0xffff); 
			for(i=0;i<TX_MS5837_BUFF_LEN;i++)
			{
				HAL_UART_Transmit(&huart1, (uint8_t *)TX_MS5837_Data.TX_MS5837_BUFF[i], 1, 0xffff);
				checkbit ^=TX_MS5837_Data.TX_MS5837_BUFF[i];//同时将每个字节加到校验码上
			}		
			HAL_UART_Transmit(&huart1, (uint8_t *)checkbit, 1, 0xffff);
			break;
		}
		case(TX_StartBit_PWM):
		{
//			TX_PWM_Data.motorpwmdata.pwm_motor1=pwm.f1;
//			TX_PWM_Data.motorpwmdata.pwm_motor2=pwm.f2;
//			TX_PWM_Data.motorpwmdata.pwm_motor3=pwm.f3;
//			TX_PWM_Data.motorpwmdata.pwm_motor4=pwm.f4;
//			TX_PWM_Data.motorpwmdata.pwm_motor5=pwm.f5;
//			TX_PWM_Data.motorpwmdata.pwm_motor6=pwm.f6;
			//数据打包发送
			HAL_UART_Transmit(&huart1, (uint8_t *)startbit, 1, 0xffff); 
			for(i=0;i<TX_MOTOR_PWM_BUFF_LEN;i++)
			{
				HAL_UART_Transmit(&huart1, (uint8_t *)TX_PWM_Data.TX_PWM_BUFF[i], 1, 0xffff);
				checkbit ^=TX_PWM_Data.TX_PWM_BUFF[i];//同时将每个字节加到校验码上
			}		
			HAL_UART_Transmit(&huart1, (uint8_t *)checkbit, 1, 0xffff);
			break;
		}		
		
	}
	
	
}

