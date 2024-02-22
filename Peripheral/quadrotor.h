#ifndef __QUADROTOR_H
#define __QUADROTOR_H

#include <math.h>
#define halfpai (3.141592654/2)

//�����궨 
#define m0 1.0 //kg  �����������൱������pwmֵ��һ��ϵ�� 
#define d0 0.2 //m   5 6�ƽ��������ĵľ���
#define r0 0.3 //m   1 2 3 4�ƽ��������ĵľ��� 
#define G0 0.2 //N   �����븡���ĺ��� �������� ��ͼ��Ӧ 

typedef struct _in{
	float atx;//m/s^2   x�����ļ��ٶ� 
	float aty;//m/s^2   y�����ļ��ٶ� 
	float atz;//m/s^2   z�����ļ��ٶ� 
	float angle;//���ļ��ٶȵķ���� 
	float ax;//x��Ǽ��ٶ� roll 
	float ay;//y��Ǽ��ٶ� pitch 
	float az;//z��Ǽ��ٶ� yaw 
}in;


typedef struct _out{
	float f1,f2,f3,f4,f5,f6;//��Ӧ�ƽ���pwm 
}out;

extern in setting;
extern out pwm;

extern float xspeed;
extern float yspeed;
extern float zspeed;
extern float offset_xspeed;
extern float offset_yspeed;
extern float offset_zspeed;



#endif 
