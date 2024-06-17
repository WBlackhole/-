#include "main.h"
#include "Encoder.h"

#define Speed_base 2000	//С�������ٶ�

extern float pitch,roll,yaw; 	//ŷ����

// PID���㺯��
float pid_MPU6050_control(float target,float input)
{
	//�������
	static float error,last_error,integral_error;
		
	//�������
	float PWM;

	// �������
    error = target - input;
	//���»���
    integral_error+= error;
	
	PWM= MPU_PID_KP * error + MPU_PID_KI* integral_error + MPU_PID_KD * (error-last_error);
	
	// ������һ�����
	last_error = error;
	
    return PWM;
}

void pid_Car_Left(int Yaw)
{
	float speed_difference;

	Car_Left();

	while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0){}
	speed_difference=pid_MPU6050_control(Yaw,yaw);
	if(speed_difference>=0)//��ƫ
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


