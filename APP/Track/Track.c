#include "Track.h"
#include "main.h"

extern int error_front,error_behind;

int Basic_FSpeed=2500; 
void Track_front(void)
{
	switch(error_front)
	{         
		case 0 :Car_Go();MOTOR_PWM_Out(Basic_FSpeed,Basic_FSpeed,Basic_FSpeed,Basic_FSpeed);break;
		case -1:Car_Go();MOTOR_PWM_Out(Basic_FSpeed-300,Basic_FSpeed+300,Basic_FSpeed-300,Basic_FSpeed+300);break;
		case -2:Car_Turn_Left();MOTOR_PWM_Out(Basic_FSpeed-1000,Basic_FSpeed,Basic_FSpeed-1000,Basic_FSpeed);break;
		case -3:Car_Turn_Left();MOTOR_PWM_Out(Basic_FSpeed-1200,Basic_FSpeed+200,Basic_FSpeed-1200,Basic_FSpeed+200);break;
		case -4:Car_Turn_Left();MOTOR_PWM_Out(Basic_FSpeed-1200,Basic_FSpeed+200,Basic_FSpeed-1200,Basic_FSpeed+200);break;
		case 1 :Car_Go();MOTOR_PWM_Out(Basic_FSpeed+300,Basic_FSpeed-300,Basic_FSpeed+300,Basic_FSpeed-300);break;
		case 2 :Car_Turn_Right();MOTOR_PWM_Out(Basic_FSpeed,Basic_FSpeed-1000,Basic_FSpeed,Basic_FSpeed-1000);break;
		case 3 :Car_Turn_Right();MOTOR_PWM_Out(Basic_FSpeed+200,Basic_FSpeed-1200,Basic_FSpeed+200,Basic_FSpeed-1200);break;
		case 4 :Car_Turn_Right();MOTOR_PWM_Out(Basic_FSpeed+200,Basic_FSpeed-1200,Basic_FSpeed+200,Basic_FSpeed-1200);break;
		default:Car_Go();MOTOR_PWM_Out(Basic_FSpeed,Basic_FSpeed,Basic_FSpeed,Basic_FSpeed);break;
	}    
}

int Basic_BSpeed=1800;
void Track_behind(void)
{
	switch(error_behind)
	{         
		case 0 :Car_Back();MOTOR_PWM_Out(Basic_BSpeed,Basic_BSpeed,Basic_BSpeed,Basic_BSpeed);break;
		case -1:Car_Back();MOTOR_PWM_Out(Basic_BSpeed+300,Basic_BSpeed-300,Basic_BSpeed+300,Basic_BSpeed-300);break;
		case -2:Car_Turn_Left();MOTOR_PWM_Out(Basic_BSpeed,Basic_BSpeed-1000,Basic_BSpeed,Basic_BSpeed-1000);break;
		case -3:Car_Turn_Left();MOTOR_PWM_Out(Basic_BSpeed+200,Basic_BSpeed-1200,Basic_BSpeed+200,Basic_BSpeed-1200);break;
		case -4:Car_Turn_Left();MOTOR_PWM_Out(Basic_BSpeed+200,Basic_BSpeed-1200,Basic_BSpeed+200,Basic_BSpeed-1200);break;
		case 1 :Car_Back();MOTOR_PWM_Out(Basic_BSpeed-300,Basic_BSpeed+300,Basic_BSpeed-300,Basic_BSpeed+300);break;
		case 2 :Car_Turn_Right();MOTOR_PWM_Out(Basic_BSpeed-1000,Basic_BSpeed,Basic_BSpeed-1000,Basic_BSpeed);break;
		case 3 :Car_Turn_Right();MOTOR_PWM_Out(Basic_BSpeed-1200,Basic_BSpeed+200,Basic_BSpeed-1200,Basic_BSpeed+200);break;
		case 4 :Car_Turn_Right();MOTOR_PWM_Out(Basic_BSpeed-1200,Basic_BSpeed+200,Basic_BSpeed-1200,Basic_BSpeed+200);break;
		default:Car_Back();MOTOR_PWM_Out(Basic_BSpeed,Basic_BSpeed,Basic_BSpeed,Basic_BSpeed);break;
	}   
}
