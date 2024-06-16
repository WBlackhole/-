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
#define MPU_PID_KP		-50		//��/����PID��������Pֵ  ֵ�޸�����������޸ģ�
#define MPU_PID_KI		0		//��/����PID��������Iֵ 	ֵ�޸�����������޸ģ�ֵ���ɴ�С��1��
#define MPU_PID_KD		0		//��/����PID��������Dֵ  ֵ�޸�����������޸ģ�ֵ���ɴ�С��5��

//С����/����ʱ��Ϊ���ĵ����ص��µ�С��б���˶��ĵ�������ٶȵ���ֵ
//#define Motor_different_Left 2000	//С��A�ֺ�D�ֻ����ٶ�
//#define Motor_different_Right 2000	//С��B�ֺ�C�ֻ����ٶ�	
//ֵ�޸���������С������ʱ��б���˶����Ӵ�Motor_different_Left���ı���ȴ�Щ������СMotor_different_Right���ı����СЩ������֮���෴֮��

/************************************************
*  �������ƣ�pid_Car_X��X=Left/Right��
*  ����˵����Ӧ�ò�-PID����/����
			����Ӳ����MPU6050�����Ǵ��ص����ݶ�С��
			����/���н�����������֤С��������
*  ����˵������
*  �������أ���
*************************************************/
void pid_Car_Left(void);
void pid_Car_Right(void);
float pid_MPU6050_control(float target,float input);


#endif

