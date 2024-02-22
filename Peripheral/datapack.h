#ifndef _DATAPACK_H
#define _DATAPACK_H
#include "rov.h"

/*--------------------------���ݰ�����-------------------------*/
#define TX_JY901_BUFF_LEN 				36			//����λ������JY901��̬���������ݰ�
#define TX_MS5837_BUFF_LEN 				16			//����λ������MS5837��ȴ��������ݰ�
#define TX_MOTOR_PWM_BUFF_LEN			24			//����λ�����͸��ƽ���ռ�ձ����ݰ�
#define RX_HANDLE_BUFF_LEN				16			//��λ�����յ��ֱ�����
/*--------------------------����ͷ-------------------------*/
#define TX_StartBit_JY901					0xAA		//����λ������JY901��̬����������
#define	TX_StartBit_MS5837				0xAB		//����λ������MS5837��ȴ���������
#define	TX_StartBit_PWM						0xAC		//����λ������MS5837��ȴ���������
#define RX_StartBit_HANDLE  			0xAD		//��λ�����յ��ֱ�����


/*---------------------��λ������λ��----------------------*/
// JY901 �������ݹ�����
typedef union 
{  
	struct
		{
			float AccelerationX;		//X����ٶ�  
			float AccelerationY;     	//Y����ٶ�  
			float AccelerationZ;     	//Z����ٶ�  

			float AngleSpeedX;       //X����ٶ�      
			float AngleSpeedY;       //Y����ٶ�              
			float AngleSpeedZ;       //Z����ٶ�

			float PitchAngle;        //������
			float YawAngle;        	 //ƫ����
			float RollAngle;         //������
		}motiondata;
	uint8_t TX_JY901_BUFF[TX_JY901_BUFF_LEN];
}TX_JY901_Buff_Union;

//MS5837 ��ȴ�����������
typedef union 
{
	struct
		{
			float Pressure;          		//ѹ��
			float Depth;             		//���
			float Temperature;       	  //�¶�
			float Offset;            		//ˮ����������ֵ
		}ms5837data;
	uint8_t TX_MS5837_BUFF[TX_MS5837_BUFF_LEN];
}TX_MS5837_Buff_Union;

//�ƽ���
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
