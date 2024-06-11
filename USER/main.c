#include "main.h"
extern float Yaw2,Yaw1,speed_difference;
;
extern int Move_flag;
extern u8 sight_flag,sight_flag_over,sight_flag_1,sight_flag_2,sight_transform,sight_place,place_close_over,place_far_over,place_close,place_far,transform_result;
	
int main()
{	
	//系统初始化
	sys_Init();
//	BEEP_sound();

	int Address,Command;
	while(1)
	{
		if(IR_GetDataFlag() || IR_GetRepeatFlag())	//如果收到数据帧或者收到连发帧
		{
			static char i=1;
			Address=IR_GetAddress();		//获取遥控器地址码
			Command=IR_GetCommand();		//获取遥控器命令码
			if(Command==0x1C&&i)
			{
				Move_1();
				Move_2_B();
				Move_3_B();
				Move_4_B();
				i=!i;
			}
		}	
	}
//	sight_flag=1;
//	sight_flag_2=1;
//	sight_flag_over=0;
//	Move_flag=8;
//	while(sight_place!=1);
//	place_close_over=1;
//	place_far_over=1;
//	if(place_close_over)
//	{
//		switch(place_close)
//		{
//			case 'a':
//				//抓近方块
//				break;
//			case 'b':
//				//抓近圆台
//				break;
//			case 'c':
//				//抓近圆柱
//				break; 
//		}
//	}
//	//如果远处物块未达数量要求 
//	if(place_far_over)
//	{
//		switch(place_far)
//		{
//			case 'a':
//				//抓远方块
//				break;
//			case 'b':
//				//抓远圆台
//				break;
//			case 'c':
//				//抓远圆柱
//				break; 
//		}
//	} 	
	while(1)
	{
//		read_infrared_front();
//		Car_Go();
//		MOTOR_PWM_Out(2000,2000,2000,2000);
//		Track_front();
//		pid_Car_Right();
	}
}

