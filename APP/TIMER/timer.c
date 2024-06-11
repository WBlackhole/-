#include "timer.h"
#include "main.h"

int fk,yt,yz;
u8 place_close_over,place_far_over;
	
extern int Move_flag,cnt;
extern float pitch,roll,yaw;

extern u8 sight_flag_over,sight_transform,sight_place,transform_result,place_close,place_far;


//通用定时器6中断初始化，中断时间=psc*arr/72M
void TIM6_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<4;	
 	TIM6->ARR=arr;  	 
	TIM6->PSC=psc;  		  
	TIM6->DIER|=1<<0;  
	TIM6->CR1|=0x01;  
	MY_NVIC_Init(1,3,TIM6_IRQn,2);							 
}

//定时器6中断服务程序,中断时间由中断初始化函数设置	 
void TIM6_IRQHandler(void)
{ 		    		  			    
	read_infrared_front();
	read_infrared_behind();
	read_infrared_right();
	
	if(Move_flag==0)//刹车
	{
		MOTOR_PWM_Out(0,0,0,0);
		Car_Go();
		cnt--;
	}
	else if(Move_flag==1)//前循迹
	{
		Track_front();
		cnt--;
	}
	else if(Move_flag==2)//后循迹
	{
		Track_behind();
		cnt--;
	}
	else if(Move_flag==3)//PID控制-前行
	{
		cnt-=10;
	}
	else if(Move_flag==4)//PID控制-左行
	{
		pid_Car_Left();
		cnt--;
	}
	else if(Move_flag==5)//PID控制-右行
	{
		pid_Car_Right();
		cnt--;
	}			
	else if(Move_flag==6)//PID控制-后行
	{
//		while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0){}
//		speed_difference=pid_MPU6050_control(0,yaw);
//		MOTOR_PWM_Out(2000+speed_difference,2000-speed_difference,2000+speed_difference,2000-speed_difference);
//		Car_Back();		
//		cnt--;
	}			
	else if(Move_flag==7&&sight_flag_over)//识别任务：置位物块抓取次数
	{
		//置位抓取次数
		switch(transform_result)
		{
			case 'a':fk=4;yt=2;yz=2;break;
			case 'b':fk=2;yt=4;yz=2;break;
			case 'c':fk=2;yt=2;yz=4;break;
		}
		//识别任务结束
		sight_transform=1; 
		sight_flag_over=0;
	}
	else if(Move_flag==8&&sight_flag_over)//放置任务
	{
		switch(place_close)
		{
			case 'a':
				if(fk>0)
				{
					fk--;
					place_close_over=1;
				}
				else
				{
					place_close_over=0;
				}
				break;
			case 'b':
				if(yt>0)
				{
					yt--;
					place_close_over=1;
				}
				else
				{
					place_close_over=0;
				}
				break;
			case 'c':
				if(yz>0)
				{
					yz--;
					place_close_over=1;
				}
				else
				{
					place_close_over=0;
				}
				break;
		}
		switch(place_far)
		{
			case 'a':
				if(fk>0)
				{
					fk--;
					place_close_over=1;
				}
				else
				{
					place_close_over=0;
				}
				break;
			case 'b':
				if(yt>0)
				{
					yt--;
					place_close_over=1;
				}
				else
				{
					place_close_over=0;
				}
				break;
			case 'c':
				if(yt>0)
				{
					yt--;
					place_close_over=1;
				}
				else
				{
					place_close_over=0;
				}
				break;
		}
		//识别任务结束
		sight_place=1;
		sight_flag_over=0; 
	}
	else if(Move_flag==9)//放置任务
	{
		Car_Turn_Right();
		MOTOR_PWM_Out(1000,1000,1000,1000);
		cnt--;
	}
	TIM6->SR&=~(1<<0); 	    
}

void Delay_ms(int ums)
{
	for(cnt=ums;cnt>0;)
	{
		Move_flag=3;
	}
	
}










