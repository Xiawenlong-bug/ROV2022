#ifndef _JY901_H
#define _JY901_H
#include "rov.h"

//���������ݽṹ��������
typedef struct 
{

	float acc_x;//���ٶ�
	float acc_y;
	float acc_z;
	
	float gyro_x;//���ٶ�
	float gyro_y;
	float gyro_z;	
	
	float angle_x;//�Ƕ�
	float angle_y;
	float angle_z;//�����洢��ǰ����������
	
}JY901_ValTypedef;
extern JY901_ValTypedef JY901;

//������ٶ�
struct SAcc
{
	short a[3];//ÿ��short���������ֽڣ���˿��Խ���ȡ�����ݸߵ��ֽ�ת����һ���з���short����
	short T;
};
extern struct SAcc stcAcc;


//������ٶ�
struct SGyro
{
	short w[3];
	short T;
};
extern struct SGyro stcGyro;

//����Ƕ�
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
