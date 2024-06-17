#ifndef __ENCODER_H
#define __ENCODER_H

#define MPU_PID_KP		-50
#define MPU_PID_KI		0
#define MPU_PID_KD		0

/************************************************
*  函数名称：pid_Car_X（X=Left/Right）
*  功能说明：应用层-PID左行/右行
			利用硬件层MPU6050陀螺仪传回的数据对小车
			左行/右行进行修正，保证小车车身正
*  参数说明：无
*  函数返回：无
*************************************************/
void pid_Car_Left(int Yaw);
void pid_Car_Right(int Yaw);

#endif

