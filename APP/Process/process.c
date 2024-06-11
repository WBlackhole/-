#include "process.h"
#include "main.h"

int Move_flag,cnt;
float Yaw1,Yaw2;

extern u8 sight_flag,sight_flag_over,sight_flag_1,sight_flag_2,sight_transform,sight_place,place_close_over,place_far_over,place_close,place_far,transform_result;

void Move_1(void)
{	
	/*走到障碍物前*/
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
	//前进一小段
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
	//转弯
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
	
	//过障碍物
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
//	//左移
//	for(cnt=30;cnt>0;)
//	{
//		Move_flag=0;
//		mpu_dmp_get_data(&pitch,&roll,&yaw);
//		Yaw1=yaw;
//	}
//	for(cnt=500;cnt>0;)
//	{
//		if(sensor_front[1]==1||sensor_behind[1]==1)//前或后灰度传感器的中央传感器检测到黑线
//		{
//			if(cnt<400)//确保走出起始黑线
//			{
//				Move_flag=0;
//				cnt=0;
//				break;
//			}				
//		}
//		Move_flag=4;
//	}
//	//停止0.2秒
//	for(cnt=20;cnt>0;)
//	{
//		Move_flag=0;
//	}
//	//后循迹至第一条黑横线
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
//	//机械臂准备
//	y3z_1();
//	delay_ms(1200);
//	
//	//打开中断接收标志（关闭在串口），打开视觉任务一开始标志位（关闭在串口），关闭视觉任务结束标志位（打开在串口），Move_flag置位
//	sight_flag=1;
//	sight_flag_1=1;
//	sight_flag_over=0;
//	Move_flag=7;
//	//视觉任务一结束 
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
		if(sensor_behind[1]==1)//前灰度传感器的中央传感器检测到黑线
		{
			if(cnt<400)//确保走出起始黑线
			{
				Move_flag=0;
				cnt=0;
				break;
			}				
		}
		Move_flag=4;
	}
	//停止0.2秒
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//后循迹至第一条黑横线
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
	
	//机械臂准备扫描动作
	
//	//打开中断接收标志（关闭在串口），打开视觉任务一开始标志位（关闭在串口），关闭视觉任务结束标志位（打开在串口），Move_flag置位
//	sight_flag=1;
//	sight_flag_1=1;
//	sight_flag_over=0;
//	Move_flag=7;
//	//视觉任务一结束 
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
	
	//抓取动作
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
	//后退至横断区
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
	//走到随机装置变换区，准备第一次抓取
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
	//机械臂扫描准备
	sight_flag=1;
	sight_flag_2=1;
	sight_flag_over=0;
	Move_flag=8;
	//写机械臂扫描准备动作！
	
	//机械臂第一次抓取		
	switch(transform_result)
	{
		case 'a':Sight_FK();break;
		case 'b':Sight_YT();break;
		case 'c':Sight_YZ();break;
	}

	
	//准备余下抓取
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
		//机械臂扫描准备
		sight_flag=1;
		sight_flag_2=1;
		sight_flag_over=0;
		Move_flag=8;
		//写机械臂扫描准备动作！
		
		switch(transform_result)
		{
			case 'a':Sight_FK();break;
			case 'b':Sight_YT();break;
			case 'c':Sight_YZ();break;
		}
		
		delay_ms(1000);
	}
	//小车后退至横断区
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
	//右行
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
	//右行
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
	
	//根据抽签结果决定！
	AFK_BYT_CYZ();

}

void Move_4_B(void)
{
	//走至第一个转弯处
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
	//停顿
	for(cnt=50;cnt>0;)
	{
		Move_flag=0;
	}
	//前进一点
	for(cnt=40;cnt>0;)
	{
		Car_Go();
		MOTOR_PWM_Out(2000,2000,2000,2000);			
	}
	//转弯
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
	//走到障碍区A
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
	//过障碍区
	for(cnt=130;cnt>0;)
	{
		Car_Go();
		MOTOR_PWM_Out(3000,3000,3000,3000);			
	}
	//返回区前停止
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
	//进入返回区
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
	//走至第一个转弯处
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
	//停顿
	for(cnt=50;cnt>0;)
	{
		Move_flag=0;
	}
	//前进一点
	for(cnt=40;cnt>0;)
	{
		Car_Go();
		MOTOR_PWM_Out(1500,1500,1500,1500);			
	}
	//转弯
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
	//走到障碍区A
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
	//过障碍区
	for(cnt=100;cnt>0;)
	{
		Car_Go();
		MOTOR_PWM_Out(1000,1000,1000,1000);			
	}
	//返回区前停止
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
	//进入返回区
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
	//抓取第一次，打开中断数据接收标志位（关闭在串口），打开视觉任务二开始标志位（关闭在串口），关闭视觉任务结束标志位（关闭在串口），Move_flag置位 
	sight_flag=1;
	sight_flag_2=1;
	sight_flag_over=0;
	Move_flag=8;
	
	//视觉任务二扫描结束
	while(sight_place!=1);
	
	//如果近处物块未达数量要求 
	if(place_close_over)
	{
		switch(place_close)
		{
			case 'a':
				//抓近方块
				switch(fk)
				{
					case 0:
						//抓第四个方块
						break;
					case 1:
						//抓第三个方块
						break;
					case 2:
						//抓第二个方块
						break;
					case 3:
						//抓第一个方块
						break;				
				}
				break;
			case 'b':
				//抓近圆台
				switch(yt)
				{
					case 0:
						//抓第二个圆台
						break;
					case 1:
						//抓第一个圆台
						break;
				}
				break;
			case 'c':
				//抓近圆柱
				switch(yz)
				{
					case 0:
						//抓第二个圆柱
						break;
					case 1:
						//抓第一个圆柱
						break;
				}
				break; 
		}
	}
	//如果远处物块未达数量要求 
	if(place_far_over)
	{
		switch(place_far)
		{
			case 'a':
				//抓远方块
				switch(fk)
				{
					case 0:
						//抓第四个方块
						break;
					case 1:
						//抓第三个方块
						break;
					case 2:
						//抓第二个方块
						break;
					case 3:
						//抓第一个方块
						break;				
				}
				break;
			case 'b':
				//抓远圆台
				switch(yt)
				{
					case 0:
						//抓第二个圆台
						break;
					case 1:
						//抓第一个圆台
						break;
				}
				break;
			case 'c':
				//抓远圆柱
				switch(yz)
				{
					case 0:
						//抓第二个圆柱
						break;
					case 1:
						//抓第一个圆柱
						break;
				}
				break; 
		}
	} 	
}

void Sight_YT(void)
{	
	//抓取第一次，打开中断数据接收标志位（关闭在串口），打开视觉任务二开始标志位（关闭在串口），关闭视觉任务结束标志位（关闭在串口），Move_flag置位 
	sight_flag=1;
	sight_flag_2=1;
	sight_flag_over=0;
	Move_flag=8;
	
	//视觉任务二扫描结束
	while(sight_place!=1);
	
	//如果近处物块未达数量要求 
	if(place_close_over)
	{
		switch(place_close)
		{
			case 'a':
				//抓近方块
				switch(fk)
				{
					case 0:
						//抓第二个方块
						break;
					case 1:
						//抓第一个方块
						break;
				}
				break;
			case 'b':
				//抓近圆台
				switch(yt)
				{
					case 0:
						//抓第四个圆台
						break;
					case 1:
						//抓第三个圆台
						break;
					case 2:
						//抓第二个圆台
						break;
					case 3:
						//抓第一个圆台
						break;
				}
				break;
			case 'c':
				//抓近圆柱
				switch(yz)
				{
					case 0:
						//抓第二个圆柱
						break;
					case 1:
						//抓第一个圆柱
						break;
				}
				break; 
		}
	}
	//如果远处物块未达数量要求 
	if(place_far_over)
	{
		switch(place_far)
		{
			case 'a':
				//抓远方块
				switch(fk)
				{
					case 0:
						//抓第二个方块
						break;
					case 1:
						//抓第一个方块
						break;
				}
				break;
			case 'b':
				//抓远圆台
				switch(yt)
				{
					case 0:
						//抓第四个圆台
						break;
					case 1:
						//抓第三个圆台
						break;
					case 2:
						//抓第二个圆台
						break;
					case 3:
						//抓第一个圆台
						break;				
				}
				break;
			case 'c':
				//抓远圆柱
				switch(yz)
				{
					case 0:
						//抓第二个圆柱
						break;
					case 1:
						//抓第一个圆柱
						break;
				}
				break; 
		}
	} 	
}

void Sight_YZ(void)
{	
	//抓取第一次，打开中断数据接收标志位（关闭在串口），打开视觉任务二开始标志位（关闭在串口），关闭视觉任务结束标志位（关闭在串口），Move_flag置位 
	sight_flag=1;
	sight_flag_2=1;
	sight_flag_over=0;
	Move_flag=8;
	
	//视觉任务二扫描结束
	while(sight_place!=1);
	
	//如果近处物块未达数量要求 
	if(place_close_over)
	{
		switch(place_close)
		{
			case 'a':
				//抓近方块
				switch(fk)
				{
					case 0:
						//抓第二个方块
						break;
					case 1:
						//抓第一个方块
						break;
				}
				break;
			case 'b':
				//抓近圆台
				switch(yt)
				{
					case 0:
						//抓第二个圆台
						break;
					case 1:
						//抓第一个圆台
						break;
				}
				break;
			case 'c':
				//抓近圆柱
				switch(yz)
				{
					case 0:
						//抓第四个圆柱
						break;
					case 1:
						//抓第三个圆柱
						break;
					case 2:
						//抓第二个圆柱
						break;
					case 3:
						//抓第一个圆柱
						break;
				}
				break; 
		}
	}
	//如果远处物块未达数量要求 
	if(place_far_over)
	{
		switch(place_far)
		{
			case 'a':
				//抓远方块
				switch(fk)
				{
					case 0:
						//抓第二个方块
						break;
					case 1:
						//抓第一个方块
						break;
				}
				break;
			case 'b':
				//抓远圆台
				switch(yt)
				{
					case 0:
						//抓第二个圆台
						break;
					case 1:
						//抓第一个圆台
						break;
				}
				break;
			case 'c':
				//抓远圆柱
				switch(yz)
				{
					case 0:
						//抓第四个圆柱
						break;
					case 1:
						//抓第三个圆柱
						break;
					case 2:
						//抓第二个圆柱
						break;
					case 3:
						//抓第一个圆柱
						break;
				}
				break; 
		}
	} 	
}

void AFK_BYT_CYZ(void)
{
/************************************************
				走到A码垛区-方块
************************************************/
	//修正
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
	//停顿
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
	//至A码垛区右圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	
	//机械臂右码垛动作
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}
	
	//至A码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}
	
/************************************************
				走到B垛区-圆台
************************************************/
	//至B码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至B码垛区右圈
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

	//机械臂右码垛动作
	if(transform_result=='b')
	{
		
	}
	else
	{
		
	}

	//至B码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
	if(transform_result=='b')
	{
		
	}
	else
	{
		
	}

/************************************************
				走到C垛区-圆柱
************************************************/
	//至C码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至C码垛区右圈
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

	//机械臂右码垛动作
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

	//至C码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
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
				走到A码垛区-方块
************************************************/
	//修正
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至A码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至A码垛区右圈
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
	
	//机械臂右码垛动作
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}
	
	//至A码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}
	
/************************************************
				走到B垛区-圆柱
************************************************/
	//至B码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至B码垛区右圈
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

	//机械臂右码垛动作
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

	//至B码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
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
				走到C垛区-圆台
************************************************/
	//至C码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至C码垛区右圈
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

	//机械臂右码垛动作
	if(transform_result=='b')
	{

	}
	else
	{

	}

	//至C码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
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
				走到A码垛区-圆台
************************************************/
	//修正
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至A码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至A码垛区右圈
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
	
	//机械臂右码垛动作
	if(transform_result=='b')
	{

	}
	else
	{

	}
	
	//至A码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
	if(transform_result=='b')
	{

	}
	else
	{

	}
	
/************************************************
				走到B垛区-方块
************************************************/
	//至B码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至B码垛区右圈
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

	//机械臂右码垛动作
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}

	//至B码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}

/************************************************
				走到C垛区-圆柱
************************************************/
	//至C码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至C码垛区右圈
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

	//机械臂右码垛动作
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

	//至C码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
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
				走到A码垛区-圆台
************************************************/
	//修正
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至A码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至A码垛区右圈
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
	
	//机械臂右码垛动作
	if(transform_result=='b')
	{

	}
	else
	{

	}
	
	//至A码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
	if(transform_result=='b')
	{

	}
	else
	{

	}
	
/************************************************
				走到B垛区-圆柱
************************************************/
	//至B码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至B码垛区右圈
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

	//机械臂右码垛动作
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

	//至B码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
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
				走到C垛区-方块
************************************************/
	//至C码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至C码垛区右圈
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

	//机械臂右码垛动作
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}

	//至C码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
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
				走到A码垛区-圆柱
************************************************/
	//修正
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至A码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至A码垛区右圈
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
	
	//机械臂右码垛动作
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
	
	//至A码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
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
				走到B垛区-方块
************************************************/
	//至B码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至B码垛区右圈
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

	//机械臂右码垛动作
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}

	//至B码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}

/************************************************
				走到C垛区-圆台
************************************************/
	//至C码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至C码垛区右圈
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

	//机械臂右码垛动作
	if(transform_result=='b')
	{

	}
	else
	{

	}

	//至C码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
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
				走到A码垛区-圆柱
************************************************/
	//修正
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至A码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至A码垛区右圈
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
	
	//机械臂右码垛动作
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
	
	//至A码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
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
				走到B垛区-圆台
************************************************/
	//至B码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至B码垛区右圈
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

	//机械臂右码垛动作
	if(transform_result=='b')
	{

	}
	else
	{

	}

	//至B码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
	if(transform_result=='b')
	{

	}
	else
	{

	}

/************************************************
				走到C垛区-方块
************************************************/
	//至C码区进入线
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}
	//至C码垛区右圈
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

	//机械臂右码垛动作
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}

	//至C码垛区左圈
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
	//停顿
	for(cnt=20;cnt>0;)
	{
		Move_flag=0;
	}

	//机械臂左码垛动作
	if(transform_result=='a')
	{
		
	}
	else
	{
		
	}

}








