#include "main.h"
#include "Encoder.h"

#define Speed_base 2000	//小车基础速度

extern float pitch,roll,yaw; 	//欧拉角

// PID计算函数
float pid_MPU6050_control(float target,float input)
{
	//定义误差
	static float error,last_error,integral_error;
		
	//定义输出
	float PWM;

	// 计算误差
    error = target - input;
	//更新积分
    integral_error+= error;
	
	PWM= MPU_PID_KP * error + MPU_PID_KI* integral_error + MPU_PID_KD * (error-last_error);
	
	// 更新上一次误差
	last_error = error;
	
    return PWM;
}

void pid_Car_Left(int Yaw)
{
	float speed_difference;

	Car_Left();

	while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0){}
	speed_difference=pid_MPU6050_control(Yaw,yaw);
	if(speed_difference>=0)//左偏
	{
		MOTOR_PWM_Out(Speed_base,Speed_base,Speed_base+speed_difference,Speed_base+speed_difference);
	
	}
	else
	{
		MOTOR_PWM_Out(Speed_base-speed_difference,Speed_base-speed_difference,Speed_base,Speed_base);			
	}
}

void pid_Car_Right(int Yaw)
{
	float speed_difference; 

	Car_Right();
	
	while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0){}
	speed_difference=pid_MPU6050_control(Yaw,yaw);
	if(speed_difference>=0)
	{
		MOTOR_PWM_Out(Speed_base-speed_difference,Speed_base-speed_difference,Speed_base,Speed_base);	
	}
	else
	{
		MOTOR_PWM_Out(Speed_base,Speed_base,Speed_base+speed_difference,Speed_base+speed_difference);			
	}
}


