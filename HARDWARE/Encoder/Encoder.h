#ifndef __ENCODER_H
#define __ENCODER_H

typedef struct
{
	
	float KP;
	float KI;
	float KD;
	
}PID;

#define Speed_PID_KP	1
#define Speed_PID_KI	10
#define Speed_PID_KD	0
#define MPU_PID_KP		-50		//左/右行PID控制器的P值  值修改意见：谨慎修改！
#define MPU_PID_KI		0		//左/右行PID控制器的I值 	值修改意见：谨慎修改！值不可大（小于1）
#define MPU_PID_KD		0		//左/右行PID控制器的D值  值修改意见：谨慎修改！值不可大（小于5）

//小车左/右行时因为重心等因素导致的小车斜向运动的电机基础速度调整值
//#define Motor_different_Left 2000	//小车A轮和D轮基础速度
//#define Motor_different_Right 2000	//小车B轮和C轮基础速度	
//值修改意见：如果小车左行时向斜上运动，加大Motor_different_Left（改变幅度大些），减小Motor_different_Right（改变幅度小些）。反之，亦反之。

/************************************************
*  函数名称：pid_Car_X（X=Left/Right）
*  功能说明：应用层-PID左行/右行
			利用硬件层MPU6050陀螺仪传回的数据对小车
			左行/右行进行修正，保证小车车身正
*  参数说明：无
*  函数返回：无
*************************************************/
void pid_Car_Left(void);
void pid_Car_Right(void);
float pid_MPU6050_control(float target,float input);


#endif

