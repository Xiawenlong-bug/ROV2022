#ifndef __PID_H
#define __PID_H

#include "JY901.h"


typedef struct _PID
{
	float kp,ki,kd;
	float error,lastError;//误差、上次误差
	float integral,maxIntegral,minIntegral;//积分、积分限幅
	float output,maxOutput,minOutput;//输出、输出限幅
}PID;

//pid结构体：全局变量
typedef struct _EXPECTED
{
		float Angle_x;
		float Angle_y;
		float Angle_z;
		float AngleSpeed_x;
		float AngleSpeed_y;
		float AngleSpeed_z;
		float Acc_x;
		float Acc_y;
		float Acc_z;		
		float Depth;
		float temp;
		float Speed_x;
	  float Speed_y;
	  float Speed_z;
}EXPECTED;

typedef struct _NOW
{
		float Angle_x;
		float Angle_y;
		float Angle_z;
		float AngleSpeed_x;
		float AngleSpeed_y;
		float AngleSpeed_z;
		float Acc_x;
		float Acc_y;
		float Acc_z;		
		float Depth;
		float temp;
		float Speed_x;
	  float Speed_y;
	  float Speed_z;
}NOW;

extern PID pid1,pid2,pid3,pid4,pid5,pid6,pidx,pidy,pidz_out,pidz_in;
extern NOW Now_data;
extern EXPECTED Expected_data;

void PID_Init(PID *pid,float p,float i,float d);
void PID_limit_Init(PID *pid,float i_max,float i_min,float out_max,float out_min);
void PID_RESET(PID *pid);
void PID_SingleCalc(PID *pid,float WANT,float NOW);
void PID_SET(void);
void PID_RESET_ALL(void);
void PID_Update_Data(void);
void outer_PID_calculate(void);
void inner_PID_calculate(void);

#endif
