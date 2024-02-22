#ifndef __QUADROTOR_H
#define __QUADROTOR_H

#include <math.h>
#define halfpai (3.141592654/2)

//参数标定 
#define m0 1.0 //kg  船的质量，相当于所有pwm值加一个系数 
#define d0 0.2 //m   5 6推进器到中心的距离
#define r0 0.3 //m   1 2 3 4推进器到中心的距离 
#define G0 0.2 //N   重力与浮力的合力 方向向下 与图对应 

typedef struct _in{
	float atx;//m/s^2   x轴质心加速度 
	float aty;//m/s^2   y轴质心加速度 
	float atz;//m/s^2   z轴质心加速度 
	float angle;//质心加速度的方向角 
	float ax;//x轴角加速度 roll 
	float ay;//y轴角加速度 pitch 
	float az;//z轴角加速度 yaw 
}in;


typedef struct _out{
	float f1,f2,f3,f4,f5,f6;//对应推进器pwm 
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
