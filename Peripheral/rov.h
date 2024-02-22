#ifndef  __ROV_H
#define  __ROV_H


/*******************************System_Includes *******************************/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"//jy901数据解析
#include "stdio.h" //printf重定向
#include "I2C.h"   //软件I2C
/********************************RTOS_Includes*******************************/
#include <rtthread.h>

/********************************Peripheral_Includes*************************/
#include "jy901.h"
#include "MS5837.h"
#include "quadrotor.h"
#include "datapack.h"
/******************************** User_Typedef*******************************/
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;


#endif
