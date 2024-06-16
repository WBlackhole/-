#include "process.h"
#include "main.h"

int Move_flag,cnt;
float Yaw1,Yaw2;

extern u8 sight_flag,sight_flag_over,sight_flag_1,sight_flag_2,sight_transform,sight_place,place_close_over,place_far_over,place_close,place_far,transform_result;

void Move_1(void)
{	
	/*�ߵ��ϰ���ǰ*/
	for(cnt=300;cnt>0;)
	{
		if(sensor_front[3]==1&&sensor_front[0]==0&&cnt<250)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Move_flag=1;
		}
	}
	for(cnt=50;cnt>0;)
	{
		Move_flag=0;
	}
	//ǰ��һС��
	for(cnt=200;cnt>0;)
	{
		if(error_behind==5)
		{
			Move_flag=0;
			cnt=0;			
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(2000,2000,2000,2000);
		}
	}
	//ת��
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[1]==1&&sensor_front[2]==0)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Turn_Right();
			MOTOR_PWM_Out(2500,2500,2500,2500);
		}
	}
	for(cnt=100;cnt>0;)
	{
		if(error_front==All_White)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(2000,2000,2000,2000);
		}
	}
	for(cnt=50;cnt>0;)
	{
		Move_flag=0;
	}
	
	//���ϰ���
	for(cnt=200;cnt>0;)
	{
		Car_Go();
		MOTOR_PWM_Out(3000,3000,3000,3000);			
	}
	
	for(cnt=400;cnt>0;)
	{
		if((sensor_front[0]==0&&sensor_front[3]==1)||(cnt<200))
		{
			Move_flag=0;
			cnt=0;
		}
		else if(error_front==All_White)
		{
			Car_Go();
			MOTOR_PWM_Out(3000,3000,3000,3000);			
		}
		else
		{
			Move_flag=1;
		}			
	}
}	

//void Move_2(void)
//{
//	//����
//	for(cnt=30;cnt>0;)
//	{
//		Move_flag=0;
//		mpu_dmp_get_data(&pitch,&roll,&yaw);
//		Yaw1=yaw;
//	}
//	for(cnt=500;cnt>0;)
//	{
//		if(sensor_front[1]==1||sensor_behind[1]==1)//ǰ���Ҷȴ����������봫������⵽����
//		{
//			if(cnt<400)//ȷ���߳���ʼ����
//			{
//				Move_flag=0;
//				cnt=0;
//				break;
//			}				
//		}
//		Move_flag=4;
//	}
//	//ֹͣ0.2��
//	for(cnt=20;cnt>0;)
//	{
//		Move_flag=0;
//	}
//	//��ѭ������һ���ں���
//	for(cnt=500;cnt>0;)
//	{
//		if(error_behind==All_Black)
//		{
//			Move_flag=0;
//			cnt=0;
//		}
//		else
//		{
//			Basic_BSpeed=1200;
//			Move_flag=2;
//		}		
//	}
//	//��е��׼��
//	y3z_1();
//	delay_ms(1200);
//	
//	//���жϽ��ձ�־���ر��ڴ��ڣ������Ӿ�����һ��ʼ��־λ���ر��ڴ��ڣ����ر��Ӿ����������־λ�����ڴ��ڣ���Move_flag��λ
//	sight_flag=1;
//	sight_flag_1=1;
//	sight_flag_over=0;
//	Move_flag=7;
//	//�Ӿ�����һ���� 
//	if(sight_transform)
//	{
//		BEEP_sound();
//		BEEP_sound();		
//	}

//	
//}

void Move_2_B(void)
{
	for(cnt=30;cnt>0;)
	{
		Move_flag=0;
		mpu_dmp_get_data(&pitch,&roll,&yaw);
		Yaw1=yaw;
	}
	for(cnt=500;cnt>0;)
	{
		if(sensor_behind[1]==1)//ǰ�Ҷȴ����������봫������⵽����
		{
			if(cnt<400)//ȷ���߳���ʼ����
			{
				Move_flag=0;
				cnt=0;
				break;
			}				
		}
		Move_flag=4;
	}
	//ֹͣ0.2��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��ѭ������һ���ں���
	for(cnt=500;cnt>0;)
	{
		if(error_behind==All_Black)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Basic_BSpeed=1200;
			Move_flag=2;
		}		
	}
 	for(cnt=100;cnt>0;)
	{
		Move_flag=0;
	}
	
	//��е��׼��ɨ�趯��
	
//	//���жϽ��ձ�־���ر��ڴ��ڣ������Ӿ�����һ��ʼ��־λ���ر��ڴ��ڣ����ر��Ӿ����������־λ�����ڴ��ڣ���Move_flag��λ
//	sight_flag=1;
//	sight_flag_1=1;
//	sight_flag_over=0;
//	Move_flag=7;
//	//�Ӿ�����һ���� 
//	while(sight_transform!=1);
	suijiqu();
	delay_ms(1200);
	BEEP_sound();
	Delay_ms(300);
	BEEP_sound();
	
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	for(cnt=200;cnt>0;)
	{
		if(sensor_front[3]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Left();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}		
	}
	for(cnt=200;cnt>0;)
	{
		if(sensor_front[3]==0)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Left();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}		
	
	}
	for(cnt=50;cnt>0;)
	{
		Move_flag=0;
	}
	for(cnt=75;cnt>0;)
	{
		Car_Back();
		MOTOR_PWM_Out(1000,1000,1000,1000);			
	}
	for(cnt=50;cnt>0;)
	{
		Move_flag=0;
	}
	
	//ץȡ����
	jinchuyuanzhu6kuang1();
	Delay_ms(1500);
	jinchuyuanzhu6kuang2();
	Delay_ms(1500);
	jinchuyuanzhu6kuang3();
	Delay_ms(1500);
	jinchuyuanzhu6kuang4();
	Delay_ms(1500);
	jinchuyuanzhu6kuang5();
	Delay_ms(1500);
	jinchuyuanzhu6kuang6();
	Delay_ms(1500);
	jinchuyuanzhu6kuang7();
	Delay_ms(1500);
	jinchuyuanzhu6kuang8();
	Delay_ms(1500);
	jinchuyuanzhu6kuang9();
	Delay_ms(1500);
	
	for(int i=7;i>0;i--)
	{
		for(cnt=60;cnt>0;)
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
		for(cnt=50;cnt>0;)
		{
			Move_flag=0;
		}

	}
	//�����������
	for(cnt=500;cnt>0;)
	{
		if(error_front==All_Black)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(2000,2000,2000,2000);			
		}		
	}

}

void Move_3(void)
{
	//�ߵ����װ�ñ任����׼����һ��ץȡ
	for(cnt=200;cnt>0;)
	{
		if(error_behind==All_Black)
		{
			if(cnt<175)
			{
				Move_flag=0;
				cnt=0;
				break;
			}
		}
		Car_Back();
		MOTOR_PWM_Out(1000,1000,1000,1000);
	}
	for(cnt=15;cnt>0;)
	{
		Car_Back();
		MOTOR_PWM_Out(1000,1000,1000,1000);
	}
	//��е��ɨ��׼��
	sight_flag=1;
	sight_flag_2=1;
	sight_flag_over=0;
	Move_flag=8;
	//д��е��ɨ��׼��������
	
	//��е�۵�һ��ץȡ		
	switch(transform_result)
	{
		case 'a':Sight_FK();break;
		case 'b':Sight_YT();break;
		case 'c':Sight_YZ();break;
	}

	
	//׼������ץȡ
	while(fk!=0||yt!=0||yz!=0)
	{
		for(cnt=80;cnt>0;)
	   {
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);
		}
		for(cnt=50;cnt>0;)
		{
			Move_flag=0;
		}	
		//��е��ɨ��׼��
		sight_flag=1;
		sight_flag_2=1;
		sight_flag_over=0;
		Move_flag=8;
		//д��е��ɨ��׼��������
		
		switch(transform_result)
		{
			case 'a':Sight_FK();break;
			case 'b':Sight_YT();break;
			case 'c':Sight_YZ();break;
		}
		
		delay_ms(1000);
	}
	//С�������������
	for(cnt=500;cnt>0;)
	{
		if(error_front==All_Black)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Move_flag=1;
		}
	}	
}

void Move_3_B(void)
{
	for(cnt=50;cnt>0;)
	{
		Move_flag=0;
	}
	//����
	for(cnt=500;cnt>0;)
	{
		if(sensor_behind[1]==1)
		{
			if(cnt<400)
			{
				Move_flag=0;
				cnt=0;
				break;
			}
		}
		Car_Right();
		MOTOR_PWM_Out(2000,2000,2000,2000);
	}
	Basic_FSpeed=1500;
	Basic_BSpeed=1500;
	AFK_BYT_CYZ();
}

void Move_4(void)
{	
	for(cnt=50;cnt>0;)
	{
		Move_flag=0;
		mpu_dmp_get_data(&pitch,&roll,&yaw);
		Yaw2=yaw;
	}
	//����
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[1]==1||sensor_behind[1]==1)
		{
			if(cnt<400)
			{
				Move_flag=0;
				cnt=0;
				break;
			}
		}
		Move_flag=5;
	}
	
	//���ݳ�ǩ���������
	AFK_BYT_CYZ();

}

void Move_4_B(void)
{
	//������һ��ת�䴦
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Move_flag=1;
		}			
	}
	//ͣ��
	for(cnt=50;cnt>0;)
	{
		Move_flag=0;
	}
	//ǰ��һ��
	for(cnt=40;cnt>0;)
	{
		Car_Go();
		MOTOR_PWM_Out(2000,2000,2000,2000);			
	}
	//ת��
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[1]==0&&sensor_front[2]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Turn_Left();
			MOTOR_PWM_Out(2500,2500,2500,2500);
		}
	}
	//�ߵ��ϰ���A
	for(cnt=200;cnt>0;)
	{
		if(error_front==All_White)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Basic_FSpeed=1500;
			Move_flag=1;
		}
	}
	//���ϰ���
	for(cnt=130;cnt>0;)
	{
		Car_Go();
		MOTOR_PWM_Out(3000,3000,3000,3000);			
	}
	//������ǰֹͣ
	for(cnt=500;cnt>0;)
	{
		if(error_front==All_Black)
		{
			Move_flag=0;
			cnt=0;			
		}
		else
		{
			Basic_FSpeed=2000;
			Move_flag=1;
		}
	}
	for(cnt=30;cnt>0;)
	{
		Move_flag=0;
	}
	//���뷵����
	for(cnt=300;cnt>0;)
	{
		if(error_behind==All_White&&cnt<250)
		{
			Move_flag=0;
			cnt=0;			
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	
}

void Move_5(void)
{
	//������һ��ת�䴦
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[0]==1&&cnt<400)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Move_flag=1;
		}			
	}
	//ͣ��
	for(cnt=50;cnt>0;)
	{
		Move_flag=0;
	}
	//ǰ��һ��
	for(cnt=40;cnt>0;)
	{
		Car_Go();
		MOTOR_PWM_Out(1500,1500,1500,1500);			
	}
	//ת��
	for(cnt=500;cnt>0;)
	{
		if(error_front==0)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Turn_Left();
			MOTOR_PWM_Out(2500,2500,2500,2500);
		}
	
	}
	//�ߵ��ϰ���A
	for(cnt=200;cnt>0;)
	{
		if(error_front==All_White)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Move_flag=1;
		}
	}
	//���ϰ���
	for(cnt=100;cnt>0;)
	{
		Car_Go();
		MOTOR_PWM_Out(1000,1000,1000,1000);			
	}
	//������ǰֹͣ
	for(cnt=500;cnt>0;)
	{
		if(error_front==All_Black)
		{
			Move_flag=0;
			cnt=0;			
		}
		else
		{
			Move_flag=1;
		}
	}
	for(cnt=50;cnt>0;)
	{
		Move_flag=0;
	}
	//���뷵����
	for(cnt=300;cnt>0;)
	{
		if(error_front==All_Black&&cnt<250)
		{
			Move_flag=0;
			cnt=0;			
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	
}

void Sight_FK(void)
{	
	//ץȡ��һ�Σ����ж����ݽ��ձ�־λ���ر��ڴ��ڣ������Ӿ��������ʼ��־λ���ر��ڴ��ڣ����ر��Ӿ����������־λ���ر��ڴ��ڣ���Move_flag��λ 
	sight_flag=1;
	sight_flag_2=1;
	sight_flag_over=0;
	Move_flag=8;
	
	//�Ӿ������ɨ�����
	while(sight_place!=1);
	
	//����������δ������Ҫ�� 
	if(place_close_over)
	{
		switch(place_close)
		{
			case 'a':
				//ץ������
				switch(fk)
				{
					case 0:
						//ץ���ĸ�����
						break;
					case 1:
						//ץ����������
						break;
					case 2:
						//ץ�ڶ�������
						break;
					case 3:
						//ץ��һ������
						break;				
				}
				break;
			case 'b':
				//ץ��Բ̨
				switch(yt)
				{
					case 0:
						//ץ�ڶ���Բ̨
						break;
					case 1:
						//ץ��һ��Բ̨
						break;
				}
				break;
			case 'c':
				//ץ��Բ��
				switch(yz)
				{
					case 0:
						//ץ�ڶ���Բ��
						break;
					case 1:
						//ץ��һ��Բ��
						break;
				}
				break; 
		}
	}
	//���Զ�����δ������Ҫ�� 
	if(place_far_over)
	{
		switch(place_far)
		{
			case 'a':
				//ץԶ����
				switch(fk)
				{
					case 0:
						//ץ���ĸ�����
						break;
					case 1:
						//ץ����������
						break;
					case 2:
						//ץ�ڶ�������
						break;
					case 3:
						//ץ��һ������
						break;				
				}
				break;
			case 'b':
				//ץԶԲ̨
				switch(yt)
				{
					case 0:
						//ץ�ڶ���Բ̨
						break;
					case 1:
						//ץ��һ��Բ̨
						break;
				}
				break;
			case 'c':
				//ץԶԲ��
				switch(yz)
				{
					case 0:
						//ץ�ڶ���Բ��
						break;
					case 1:
						//ץ��һ��Բ��
						break;
				}
				break; 
		}
	} 	
}

void Sight_YT(void)
{	
	//ץȡ��һ�Σ����ж����ݽ��ձ�־λ���ر��ڴ��ڣ������Ӿ��������ʼ��־λ���ر��ڴ��ڣ����ر��Ӿ����������־λ���ر��ڴ��ڣ���Move_flag��λ 
	sight_flag=1;
	sight_flag_2=1;
	sight_flag_over=0;
	Move_flag=8;
	
	//�Ӿ������ɨ�����
	while(sight_place!=1);
	
	//����������δ������Ҫ�� 
	if(place_close_over)
	{
		switch(place_close)
		{
			case 'a':
				//ץ������
				switch(fk)
				{
					case 0:
						//ץ�ڶ�������
						break;
					case 1:
						//ץ��һ������
						break;
				}
				break;
			case 'b':
				//ץ��Բ̨
				switch(yt)
				{
					case 0:
						//ץ���ĸ�Բ̨
						break;
					case 1:
						//ץ������Բ̨
						break;
					case 2:
						//ץ�ڶ���Բ̨
						break;
					case 3:
						//ץ��һ��Բ̨
						break;
				}
				break;
			case 'c':
				//ץ��Բ��
				switch(yz)
				{
					case 0:
						//ץ�ڶ���Բ��
						break;
					case 1:
						//ץ��һ��Բ��
						break;
				}
				break; 
		}
	}
	//���Զ�����δ������Ҫ�� 
	if(place_far_over)
	{
		switch(place_far)
		{
			case 'a':
				//ץԶ����
				switch(fk)
				{
					case 0:
						//ץ�ڶ�������
						break;
					case 1:
						//ץ��һ������
						break;
				}
				break;
			case 'b':
				//ץԶԲ̨
				switch(yt)
				{
					case 0:
						//ץ���ĸ�Բ̨
						break;
					case 1:
						//ץ������Բ̨
						break;
					case 2:
						//ץ�ڶ���Բ̨
						break;
					case 3:
						//ץ��һ��Բ̨
						break;				
				}
				break;
			case 'c':
				//ץԶԲ��
				switch(yz)
				{
					case 0:
						//ץ�ڶ���Բ��
						break;
					case 1:
						//ץ��һ��Բ��
						break;
				}
				break; 
		}
	} 	
}

void Sight_YZ(void)
{	
	//ץȡ��һ�Σ����ж����ݽ��ձ�־λ���ر��ڴ��ڣ������Ӿ��������ʼ��־λ���ر��ڴ��ڣ����ر��Ӿ����������־λ���ر��ڴ��ڣ���Move_flag��λ 
	sight_flag=1;
	sight_flag_2=1;
	sight_flag_over=0;
	Move_flag=8;
	
	//�Ӿ������ɨ�����
	while(sight_place!=1);
	
	//����������δ������Ҫ�� 
	if(place_close_over)
	{
		switch(place_close)
		{
			case 'a':
				//ץ������
				switch(fk)
				{
					case 0:
						//ץ�ڶ�������
						break;
					case 1:
						//ץ��һ������
						break;
				}
				break;
			case 'b':
				//ץ��Բ̨
				switch(yt)
				{
					case 0:
						//ץ�ڶ���Բ̨
						break;
					case 1:
						//ץ��һ��Բ̨
						break;
				}
				break;
			case 'c':
				//ץ��Բ��
				switch(yz)
				{
					case 0:
						//ץ���ĸ�Բ��
						break;
					case 1:
						//ץ������Բ��
						break;
					case 2:
						//ץ�ڶ���Բ��
						break;
					case 3:
						//ץ��һ��Բ��
						break;
				}
				break; 
		}
	}
	//���Զ�����δ������Ҫ�� 
	if(place_far_over)
	{
		switch(place_far)
		{
			case 'a':
				//ץԶ����
				switch(fk)
				{
					case 0:
						//ץ�ڶ�������
						break;
					case 1:
						//ץ��һ������
						break;
				}
				break;
			case 'b':
				//ץԶԲ̨
				switch(yt)
				{
					case 0:
						//ץ�ڶ���Բ̨
						break;
					case 1:
						//ץ��һ��Բ̨
						break;
				}
				break;
			case 'c':
				//ץԶԲ��
				switch(yz)
				{
					case 0:
						//ץ���ĸ�Բ��
						break;
					case 1:
						//ץ������Բ��
						break;
					case 2:
						//ץ�ڶ���Բ��
						break;
					case 3:
						//ץ��һ��Բ��
						break;
				}
				break; 
		}
	} 	
}

void AFK_BYT_CYZ(void)
{
/************************************************
				�ߵ�A�����-����
************************************************/
	//����
	for(cnt=250;cnt>0;)
	{
		if(sensor_behind[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Move_flag=2;
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	for(cnt=250;cnt>0;)
	{
		if(sensor_front[3]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			if(sensor_behind[0]==1)
			{
				Car_Back();
				MOTOR_PWM_Out(1500,1500,1500,1500);
			}
			else
			{
				Move_flag=2;
			}
		}
	}
	//��A�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			if(sensor_front[3]==1)
			{
				Car_Go();
				MOTOR_PWM_Out(1500,1500,1500,1500);
			}
			else
			{
				Move_flag=1;	
			}
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	
	//��е������⶯��
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}
	
	//��A�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Move_flag=1;
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}
	
/************************************************
				�ߵ�B����-Բ̨
************************************************/
	//��B����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=1;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��B�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			if(sensor_front[3]==1)
			{
				Car_Go();
				MOTOR_PWM_Out(1500,1500,1500,1500);
			}
			else
			{
				Move_flag=1;	
			}
		}
	}

	//��е������⶯��
	if(transform_result=='b')
	{
		
	}
	else
	{
		
	}

	//��B�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Move_flag=1;
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='b')
	{
		
	}
	else
	{
		
	}

/************************************************
				�ߵ�C����-Բ��
************************************************/
	//��C����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=1;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��C�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			if(sensor_front[3]==1)
			{
				Car_Go();
				MOTOR_PWM_Out(1500,1500,1500,1500);
			}
			else
			{
				Move_flag=1;	
			}
		}
	}

	//��е������⶯��
	if(transform_result=='c')
	{

	}
	else
	{
		if(transform_result=='a')
		{
			
		}
		else
		{
			
		}
	}

	//��C�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Move_flag=1;
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='c')
	{

	}
	else
	{
		if(transform_result=='a')
		{
			
		}
		else
		{
			
		}
	}
}

void AFK_BYZ_CYT(void)
{
/************************************************
				�ߵ�A�����-����
************************************************/
	//����
	for(cnt=250;cnt>0;)
	{
		if(sensor_behind[0]==1&&sensor_behind[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Move_flag=1;
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��A����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1&&cnt<450)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=2;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��A�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Back();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	
	//��е������⶯��
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}
	
	//��A�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}
	
/************************************************
				�ߵ�B����-Բ��
************************************************/
	//��B����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1&&cnt<450)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=1;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��B�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}

	//��е������⶯��
	if(transform_result=='c')
	{

	}
	else
	{
		if(transform_result=='a')
		{
			
		}
		else
		{
			
		}
	}

	//��B�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='c')
	{

	}
	else
	{
		if(transform_result=='a')
		{
			
		}
		else
		{
			
		}
	}

/************************************************
				�ߵ�C����-Բ̨
************************************************/
	//��C����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1&&cnt<450)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=1;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��C�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}

	//��е������⶯��
	if(transform_result=='b')
	{

	}
	else
	{

	}

	//��C�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='b')
	{

	}
	else
	{

	}

}

void AYT_BFK_CYZ(void)
{
/************************************************
				�ߵ�A�����-Բ̨
************************************************/
	//����
	for(cnt=250;cnt>0;)
	{
		if(sensor_behind[0]==1&&sensor_behind[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Move_flag=1;
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��A����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1&&cnt<450)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=2;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��A�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Back();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	
	//��е������⶯��
	if(transform_result=='b')
	{

	}
	else
	{

	}
	
	//��A�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='b')
	{

	}
	else
	{

	}
	
/************************************************
				�ߵ�B����-����
************************************************/
	//��B����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1&&cnt<450)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=1;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��B�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}

	//��е������⶯��
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}

	//��B�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}

/************************************************
				�ߵ�C����-Բ��
************************************************/
	//��C����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1&&cnt<450)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=1;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��C�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}

	//��е������⶯��
	if(transform_result=='c')
	{

	}
	else
	{
		if(transform_result=='a')
		{
			
		}
		else
		{
			
		}
	}

	//��C�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='c')
	{

	}
	else
	{
		if(transform_result=='a')
		{
			
		}
		else
		{
			
		}
	}

}

void AYT_BYZ_CFK(void)
{
/************************************************
				�ߵ�A�����-Բ̨
************************************************/
	//����
	for(cnt=250;cnt>0;)
	{
		if(sensor_behind[0]==1&&sensor_behind[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Move_flag=1;
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��A����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1&&cnt<450)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=2;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��A�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Back();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	
	//��е������⶯��
	if(transform_result=='b')
	{

	}
	else
	{

	}
	
	//��A�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='b')
	{

	}
	else
	{

	}
	
/************************************************
				�ߵ�B����-Բ��
************************************************/
	//��B����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1&&cnt<450)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=1;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��B�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}

	//��е������⶯��
	if(transform_result=='c')
	{

	}
	else
	{
		if(transform_result=='a')
		{
			
		}
		else
		{
			
		}
	}

	//��B�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='c')
	{

	}
	else
	{
		if(transform_result=='a')
		{
			
		}
		else
		{
			
		}
	}

/************************************************
				�ߵ�C����-����
************************************************/
	//��C����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1&&cnt<450)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=1;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��C�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}

	//��е������⶯��
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}

	//��C�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}

}

void AYZ_BFK_CYT(void)
{
/************************************************
				�ߵ�A�����-Բ��
************************************************/
	//����
	for(cnt=250;cnt>0;)
	{
		if(sensor_behind[0]==1&&sensor_behind[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Move_flag=1;
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��A����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1&&cnt<450)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=2;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��A�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Back();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	
	//��е������⶯��
	if(transform_result=='c')
	{

	}
	else
	{
		if(transform_result=='a')
		{
			
		}
		else
		{
			
		}
	}
	
	//��A�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='c')
	{

	}
	else
	{
		if(transform_result=='a')
		{
			
		}
		else
		{
			
		}
	}
	
/************************************************
				�ߵ�B����-����
************************************************/
	//��B����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1&&cnt<450)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=1;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��B�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}

	//��е������⶯��
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}

	//��B�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}

/************************************************
				�ߵ�C����-Բ̨
************************************************/
	//��C����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1&&cnt<450)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=1;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��C�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}

	//��е������⶯��
	if(transform_result=='b')
	{

	}
	else
	{

	}

	//��C�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='b')
	{

	}
	else
	{

	}

}

void AYZ_BYT_CFK(void)
{
/************************************************
				�ߵ�A�����-Բ��
************************************************/
	//����
	for(cnt=250;cnt>0;)
	{
		if(sensor_behind[0]==1&&sensor_behind[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Move_flag=1;
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��A����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1&&cnt<450)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=2;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��A�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Back();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	
	//��е������⶯��
	if(transform_result=='c')
	{

	}
	else
	{
		if(transform_result=='a')
		{
			
		}
		else
		{
			
		}
	}
	
	//��A�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='c')
	{

	}
	else
	{
		if(transform_result=='a')
		{
			
		}
		else
		{
			
		}
	}
	
/************************************************
				�ߵ�B����-Բ̨
************************************************/
	//��B����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1&&cnt<450)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=1;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��B�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}

	//��е������⶯��
	if(transform_result=='b')
	{

	}
	else
	{

	}

	//��B�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='b')
	{

	}
	else
	{

	}

/************************************************
				�ߵ�C����-����
************************************************/
	//��C����������
	for(cnt=500;cnt>0;)
	{
		if(sensor_front[3]==1&&cnt<450)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{			
			Move_flag=1;			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//��C�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[0]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}

	//��е������⶯��
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}

	//��C�������Ȧ
	for(cnt=200;cnt>0;)
	{
		if(sensor_right[1]==1)
		{
			Move_flag=0;
			cnt=0;
		}
		else
		{
			Car_Go();
			MOTOR_PWM_Out(1000,1000,1000,1000);			
		}
	}
	//ͣ��
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//��е������⶯��
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}

}








