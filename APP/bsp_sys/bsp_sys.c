#include "bsp_sys.h"
#include "main.h"

/************************************************
*  函数名称：sys_Init
*  功能说明：主程序开始前的系统参数初始化
*  参数说明：
*  函数返回：无
*  修改时间：
*************************************************/
void sys_Init(void)
{   
 	SystemInit();				 //系统时钟等初始化
	delay_init();	   	 		 //延时初始化 

	TIM8_PWM_Init(7200,1);       //PWM频率初始化10KHz,周期100us，传感器采样时间需要大于100us
	TIM6_Int_Init(99,7199);		 //TIM6中断时间=(99+1)*(7199+1)/72M=10ms
	
	MPU_Init();					 //mpu6050初始化
	while(mpu_dmp_init());
	MOTOR_Init();           	 //电机初始化               
	IIC_init();					 //灰度传感器I2C通讯初始化
	RobotArm_init();			 //机械臂初始化
	BEEP_Init();				 //蜂鸣器初始化
	Remote_Init();				 //红外遥控模块初始化
	
	USART1_Init();
}


