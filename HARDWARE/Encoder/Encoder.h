#ifndef __ENCODER_H
#define __ENCODER_H

#define MPU_PID_KP		-50
#define MPU_PID_KI		0
#define MPU_PID_KD		0

/************************************************
*  �������ƣ�pid_Car_X��X=Left/Right��
*  ����˵����Ӧ�ò�-PID����/����
			����Ӳ����MPU6050�����Ǵ��ص����ݶ�С��
			����/���н�����������֤С��������
*  ����˵������
*  �������أ���
*************************************************/
void pid_Car_Left(int Yaw);
void pid_Car_Right(int Yaw);

#endif

