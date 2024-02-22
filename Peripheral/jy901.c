#include "rov.h"

struct SAcc 		   stcAcc;//������ٶȽṹ��
struct SGyro 			 stcGyro;//���ٶ�
struct SAngle 		 stcAngle;//�Ƕ�

JY901_ValTypedef	 JY901={0};//JY901���������ݽṹ��
extern uint8_t aRxBuffer;
/**************************************************************
 * @brief ����4�жϵ��ú���������ÿ�յ�һ�����ݣ�����һ�����������
 * @param ucData�����յ�������
 * @retval
 * @addition
**************************************************************/
void JY901_DataReceive(uint8_t ucData)
{
  static unsigned char ucRxBuffer[250];//�洢����
	static unsigned char ucRxCnt = 0;	//�����洢����
	
	ucRxBuffer[ucRxCnt++]=ucData;	//���յ������ݴ��뻺������
	if (ucRxBuffer[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		ucRxCnt=0;//���¼���
		return;
	}
	if (ucRxCnt<11) {return;}//���ݲ���11�����򷵻�
	else
	{
		//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
		switch(ucRxBuffer[1])
		{

			//memcpyΪ�������Դ����ڴ濽��������������"string.h"�������ջ��������ַ����������ݽṹ�����棬�Ӷ�ʵ�����ݵĽ���
			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;//�����������Ԫ�ؿ�ʼ��ȡ�˸��ֽڣ�ǰ�����ֽڶ�Ӧ��Ӧ���͵����ݣ��������ֽ�Ϊ�¶�
			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;//ͬʱ��ÿ�����ֽ�ת����һ���з���short����
			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;
		}
		ucRxCnt=0;//��ջ�����
	}
 
	//���ݻ���
	JY901.acc_x = (float)stcAcc.a[0]/32768*16;//�����е����ʵĵط�����û�г�g�������Ǵ���
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
//		JY901_DataReceive((unsigned char)UART4->DR);//��������
//		
//	}
//}
