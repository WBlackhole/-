#include "bsp_sys.h"
#include "main.h"

/************************************************
*  �������ƣ�sys_Init
*  ����˵����������ʼǰ��ϵͳ������ʼ��
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺
*************************************************/
void sys_Init(void)
{   
 	SystemInit();				 //ϵͳʱ�ӵȳ�ʼ��
	delay_init();	   	 		 //��ʱ��ʼ�� 

	TIM8_PWM_Init(7200,1);       //PWMƵ�ʳ�ʼ��10KHz,����100us������������ʱ����Ҫ����100us
	TIM6_Int_Init(99,7199);		 //TIM6�ж�ʱ��=(99+1)*(7199+1)/72M=10ms
	
	MPU_Init();					 //mpu6050��ʼ��
	while(mpu_dmp_init());
	MOTOR_Init();           	 //�����ʼ��               
	IIC_init();					 //�Ҷȴ�����I2CͨѶ��ʼ��
	RobotArm_init();			 //��е�۳�ʼ��
	BEEP_Init();				 //��������ʼ��
	Remote_Init();				 //����ң��ģ���ʼ��
	
	USART1_Init();
}


