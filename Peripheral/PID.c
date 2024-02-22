#include "PID.h"
  
EXPECTED Expected_data;
NOW Now_data;
PID pid1,pid2,pid3,pid4,pid5,pid6,pidx,pidy,pidz_out,pidz_in;//后三个是平动
  
//初始化
void PID_Init(PID *pid,float p,float i,float d)
{
	pid->kp = p;
	pid->ki = i;
	pid->kd = d;
}

void PID_limit_Init(PID *pid,float i_max,float i_min,float out_max,float out_min)
{
	pid->maxIntegral = i_max;
	pid->minIntegral = i_min;
	pid->maxOutput = out_max;
	pid->minOutput = out_min;	
}

void PID_RESET(PID *pid)
{
	pid->error = 0;
	pid->lastError = 0;
	pid->integral = 0;
	pid->output = 0;	
}

//计算
void PID_SingleCalc(PID *pid,float WANT,float NOW)
{
	float output;
	//更新数据
	pid->lastError = pid->error;
	pid->error = WANT - NOW;
	//计算微分
	output = (pid->error-pid->lastError) * pid->kd;
	//计算比例
	output += pid->error * pid->kp;
	//计算积分
	pid->integral += pid->error * pid->ki;
	if(pid->integral > pid->maxIntegral)
		pid->integral = pid->maxIntegral;
	if(pid->integral < pid->minIntegral)
		pid->integral = pid->minIntegral;	
	
	output += pid->integral;
	if(output > pid->maxOutput)
		output = pid->maxOutput;
	if(output < pid->minOutput)
		output = pid->minOutput;
	
	pid->output = output;
}

//在这块调参
void PID_SET()
{
	//外环
	PID_Init(&pid1,0,0,0);//x轴角度环
	PID_Init(&pid2,0,0,0);//y轴角度环
	PID_Init(&pid3,0,0,0);//z轴角度环
	
	//内环
	PID_Init(&pid4,0,0,0);//x轴角速度环
	PID_Init(&pid5,0,0,0);//y轴角速度环
	PID_Init(&pid6,0,0,0);//z轴角速度环
	
	//平动
	PID_Init(&pidx,0,0,0);
	PID_Init(&pidy,0,0,0);
	PID_Init(&pidz_out,0,0,0);
	PID_Init(&pidz_in,0,0,0);
	
	//设置积分限幅、输出限幅
	PID_limit_Init(&pid1,0,0,0,0);
	PID_limit_Init(&pid2,0,0,0,0);
	PID_limit_Init(&pid3,0,0,0,0);
	PID_limit_Init(&pid4,0,0,0,0);
	PID_limit_Init(&pid5,0,0,0,0);	
	PID_limit_Init(&pid6,0,0,0,0);
	PID_limit_Init(&pidx,0,0,0,0);
	PID_limit_Init(&pidy,0,0,0,0);
	PID_limit_Init(&pidz_out,0,0,0,0);
	PID_limit_Init(&pidz_in,0,0,0,0);
}

void PID_RESET_ALL()
{
	PID_RESET(&pid1);
	PID_RESET(&pid2);
	PID_RESET(&pid3);
	PID_RESET(&pid4);
	PID_RESET(&pid5);
	PID_RESET(&pid6);
	PID_RESET(&pidx);
	PID_RESET(&pidy);
	PID_RESET(&pidz_out);
	PID_RESET(&pidz_in);
}

void PID_Update_Data()//更新当前参数
{
	Now_data.Angle_x = JY901.angle_x;
	Now_data.Angle_y = JY901.angle_y;
	Now_data.Angle_z = JY901.angle_z;

	Now_data.AngleSpeed_x = JY901.gyro_x;
	Now_data.AngleSpeed_y = JY901.gyro_y;
	Now_data.AngleSpeed_z = JY901.gyro_z;

	Now_data.Acc_x = JY901.acc_x;
	Now_data.Acc_y = JY901.acc_y;
	Now_data.Acc_z = JY901.acc_z;
	
	Now_data.Depth = MS5837.depth;
	Now_data.temp = MS5837.temp;
	
}

void outer_PID_calculate()//计算串级pid外环
{
	PID_Update_Data();
	PID_SingleCalc(&pid1,Expected_data.Angle_x,Now_data.Angle_x);
	PID_SingleCalc(&pid2,Expected_data.Angle_y,Now_data.Angle_y);
	PID_SingleCalc(&pid3,Expected_data.Angle_z,Now_data.Angle_z);
	PID_SingleCalc(&pidz_out,Expected_data.Depth,Now_data.Depth);
}

void inner_PID_calculate()//计算串级pid内环
{
	PID_Update_Data();
	PID_SingleCalc(&pid4,pid1.output,JY901.gyro_x);
	PID_SingleCalc(&pid5,pid2.output,JY901.gyro_y);
	PID_SingleCalc(&pid6,pid3.output,JY901.gyro_z);
	PID_SingleCalc(&pidz_in,pidz_out.output,zspeed);
	
	PID_SingleCalc(&pidx,Expected_data.Speed_x,xspeed);
	PID_SingleCalc(&pidy,Expected_data.Speed_y,yspeed);
	
	setting.atx=pidx.output;
	setting.aty=pidy.output;
	setting.atz=pidz_in.output;
	
	setting.ax=pid4.output;
	setting.ay=pid5.output;
	setting.az=pid6.output;
}

/*********************************************END OF FILE**********************/
