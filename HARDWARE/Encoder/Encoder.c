#include "main.h"
#include "Encoder.h"

#define Motor_different_Left 2000	//小车A轮和D轮基础速度
#define Motor_different_Right 2000	//小车B轮和C轮基础速度	

int Encoder_Count_LF,Encoder_Count_RF,Encoder_Count_LB,Encoder_Count_RB;//编码器计数值
float pitch,roll,yaw; 	//欧拉角

float LF_Speed;//调用的现在速度
float RF_Speed;
float LB_Speed;
float RB_Speed;
int Target_Speed;
float speed_difference;

extern float Yaw1,Yaw2;

void PID_Init(void)
{
	PID Speed_PID;
	PID	MPU_PID;
	
	Speed_PID.KP=Speed_PID_KP;
	Speed_PID.KI=Speed_PID_KI;
	Speed_PID.KD=Speed_PID_KD;
	
	MPU_PID.KP=MPU_PID_KP;
	MPU_PID.KI=MPU_PID_KI;
	MPU_PID.KD=MPU_PID_KD;
	
}
void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource12);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource13);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource14);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource15);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line12 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
}

//中断处理函数
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line12) == SET)
	{
		Encoder_Count_LF ++;
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
	if (EXTI_GetITStatus(EXTI_Line13) == SET)
	{
		Encoder_Count_RF ++;
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
	if (EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		Encoder_Count_LB ++;
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
	if (EXTI_GetITStatus(EXTI_Line15) == SET)
	{
		Encoder_Count_RB ++;
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
}



void Get_Motor_Speed(void)
{
	//计算公式：speed=编码器计数值/减速比 单位：圈/秒
	LF_Speed  = Encoder_Count_LF*100/330.0;
	RF_Speed  = Encoder_Count_RF*100/330.0;
	LB_Speed  = Encoder_Count_LB*100/330.0;
	RB_Speed  = Encoder_Count_RB*100/330.0;
	
	//清空计数值
	Encoder_Count_LF=0;
	Encoder_Count_RF=0;
	Encoder_Count_LB=0;
	Encoder_Count_RB=0;
}


/**************************************************************************
函数功能：速度环pid
入口参数：编码器测量值，目标速度
返回  值：电机PWM
**************************************************************************/
float Speed_Pi(float Speed_now,float target_Speed)
{ 	
	static float error,Last_error;
	static float PWM;
	Target_Speed=target_Speed;

	/*计算目标值与实际值的误差*/
	error=Target_Speed-Speed_now;

	/*增量式PI算法实现*/
	PWM+=Speed_PID_KP*(error-Last_error)+Speed_PID_KI*error;
	
	/*误差传递*/	
	Last_error=error;

	/*返回当前实际值*/
	return PWM; 
}

float PWMA,PWMB,PWMC,PWMD;

void pid_Speed_control(float A,float B,float C,float D)
{
	float limit=7100;
	
	/*计算PWM并限幅*/	
	PWMA=Speed_Pi(LF_Speed,A);
	if(PWMA>=limit)
	{
		PWMA=limit;
	}
	else if(PWMA<0)
	{
		PWMA=0;
	}
	PWMB=Speed_Pi(RF_Speed,B);
	if(PWMB>=limit)
	{
		PWMB=limit;
	}
	else if(PWMB<0)
	{
		PWMB=0;
	}	
	PWMC=Speed_Pi(LB_Speed,C);
	if(PWMC>=limit)
	{
		PWMC=limit;
	}
	else if(PWMC<0)
	{
		PWMC=0;
	}
	PWMD=Speed_Pi(RB_Speed,D);	
	if(PWMD>=limit)
	{
		PWMD=limit;
	}
	else if(PWMD<0)
	{
		PWMD=0;
	}

	/*输出PWM*/		
	MOTOR_PWM_Out(PWMA,PWMB,PWMC,PWMD);
}


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

void pid_Car_Left(void)
{
	Car_Left();
	while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0){}
	speed_difference=pid_MPU6050_control(Yaw1,yaw);
	if(speed_difference>=0)//左偏
	{
		MOTOR_PWM_Out(Motor_different_Left,Motor_different_Right,Motor_different_Right+speed_difference,Motor_different_Left+speed_difference);
	
	}
	else
	{
		MOTOR_PWM_Out(Motor_different_Left-speed_difference,Motor_different_Right-speed_difference,Motor_different_Right,Motor_different_Left);			
	}
}

void pid_Car_Right(void)
{
	Car_Right();		
	while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0){}
	speed_difference=pid_MPU6050_control(Yaw2,yaw);
	if(speed_difference>=0)
	{
		MOTOR_PWM_Out(2000-speed_difference,2000-speed_difference,2000,2000);	
	}
	else
	{
		MOTOR_PWM_Out(2000,2000,2000+speed_difference,2000+speed_difference);			
	}
}


