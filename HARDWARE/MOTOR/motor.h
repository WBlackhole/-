#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"

/************************************************
*  函数名称：MOTOR_Init
*  功能说明：GPIO初始化
*  参数说明：
*  函数返回：无
*  修改时间：
*************************************************/
void MOTOR_Init(void);

/************************************************************
*  函数名称：Car_X（X是小车不同的运动状态）
*  功能说明：共有其中麦轮车运动状态。依次是：
			前进、停止、右行、左行、后退、向右转圈、向左转圈
*  参数说明：
*  函数返回：无
*  修改时间：
*************************************************************/
void Car_Go(void);
void Car_Stop(void);
void Car_Right(void);
void Car_Left(void);	
void Car_Back(void);									
void Car_Turn_Right(void);
void Car_Turn_Left(void);

#endif

