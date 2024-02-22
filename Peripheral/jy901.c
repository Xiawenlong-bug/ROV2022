#include "rov.h"

struct SAcc 		   stcAcc;//三轴加速度结构体
struct SGyro 			 stcGyro;//角速度
struct SAngle 		 stcAngle;//角度

JY901_ValTypedef	 JY901={0};//JY901传感器数据结构体
extern uint8_t aRxBuffer;
/**************************************************************
 * @brief 串口4中断调用函数，串口每收到一个数据，调用一次这个函数。
 * @param ucData：接收到的数据
 * @retval
 * @addition
**************************************************************/
void JY901_DataReceive(uint8_t ucData)
{
  static unsigned char ucRxBuffer[250];//存储数据
	static unsigned char ucRxCnt = 0;	//计数存储数据
	
	ucRxBuffer[ucRxCnt++]=ucData;	//将收到的数据存入缓冲区中
	if (ucRxBuffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
	{
		ucRxCnt=0;//重新计数
		return;
	}
	if (ucRxCnt<11) {return;}//数据不满11个，则返回
	else
	{
		//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
		switch(ucRxBuffer[1])
		{

			//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据结构体里面，从而实现数据的解析
			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;//从数组第三个元素开始读取八个字节，前六个字节对应相应类型的数据，后两个字节为温度
			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;//同时将每两个字节转换成一个有符号short类型
			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;
		}
		ucRxCnt=0;//清空缓存区
	}
 
	//数据换算
	JY901.acc_x = (float)stcAcc.a[0]/32768*16;//这里有点疑问的地方是它没有乘g，可能是错了
	JY901.acc_y = (float)stcAcc.a[1]/32768*16;
	JY901.acc_z = (float)stcAcc.a[2]/32768*16;
	JY901.gyro_x = (float)stcGyro.w[0]/32768*2000;
	JY901.gyro_y = (float)stcGyro.w[1]/32768*2000;
	JY901.gyro_z = (float)stcGyro.w[2]/32768*2000;
	JY901.angle_x = (float)stcAngle.Angle[0]/32768*180;
	JY901.angle_y = (float)stcAngle.Angle[1]/32768*180;
	JY901.angle_z = (float)stcAngle.Angle[2]/32768*180;
}


//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	
//	if(huart==&huart4)
//	{
//		HAL_UART_Receive_IT(&huart4, &res, 1);
//		JY901_DataReceive((unsigned char)UART4->DR);//处理数据
//		
//	}
//}
