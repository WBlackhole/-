#include "motor.h"
#include "delay.h"

#define GO    0//定义电机状态 前进
#define BACK  1//后退
#define STOP  2//停车

//配置前部电机驱动的四个引脚
#define MOTOR_CLK      RCC_APB2Periph_GPIOD
#define MOTOR_PORT     GPIOD
#define MOTOR_A1       GPIO_Pin_0  //A轮
#define MOTOR_A2       GPIO_Pin_1  
#define MOTOR_B1       GPIO_Pin_2  //B轮
#define MOTOR_B2       GPIO_Pin_3
#define MOTOR_C1       GPIO_Pin_4  //C轮
#define MOTOR_C2       GPIO_Pin_5
#define MOTOR_D1       GPIO_Pin_6  //D轮
#define MOTOR_D2       GPIO_Pin_7  


void MOTOR_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(MOTOR_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = MOTOR_A1 | MOTOR_A2 | MOTOR_B1 | MOTOR_B2 | MOTOR_C1 | MOTOR_C2 | MOTOR_D1 | MOTOR_D2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_PORT, &GPIO_InitStructure);
}


/************************************************
*  函数名称：MOTOR_x(x=A/B/C/D)
*  功能说明：控制电机x的正反停转
*  参数说明：state是电机状态变量
*  函数返回：无
*  修改时间：
*************************************************/
static void MOTOR_A(char state)
{
    
	if(state == GO)//左前电机前进
	{
      GPIO_SetBits(MOTOR_PORT,MOTOR_A1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_A2);	
	}
	
    if(state == BACK)//左前电机后退
	{
      GPIO_SetBits(MOTOR_PORT,MOTOR_A2);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_A1);	
	}
	
    if(state == STOP)//停转
	{
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_A1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_A2);
	}
		
}

//右前B电机
static void MOTOR_B(char state)
{
    
	if(state == GO)//右前电机前进
	{
	  GPIO_SetBits(MOTOR_PORT,MOTOR_B1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_B2);
	}
	if(state == BACK)//右前电机后退
	{
		
      GPIO_SetBits(MOTOR_PORT,MOTOR_B2);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_B1);
	
	}
	if(state == STOP)//停转
	{
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_B1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_B2);
	}
    
}

//左后C电机
static void MOTOR_C(char state)
{
    
	if(state == GO)//左后电机前进
	{
	  GPIO_SetBits(MOTOR_PORT,MOTOR_C1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_C2);

	}
	if(state == BACK)//左后电机后退
	{

	
	  GPIO_SetBits(MOTOR_PORT,MOTOR_C2);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_C1);
	
	}
	if(state == STOP)//停转
	{
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_C1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_C2);
	}
		
}

//右后D电机
static void MOTOR_D(char state)
{
    
	if(state == GO)//右后电机前进
	{
	  GPIO_SetBits(MOTOR_PORT,MOTOR_D1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_D2);
		
	}
	if(state == BACK)//右后电机后退
	{

	  GPIO_SetBits(MOTOR_PORT,MOTOR_D2);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_D1);
	}
	if(state == STOP)//停转
	{
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_D1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_D2);
	}
		
}



//*************************************************************************//
//***************************前进****************************//
//只要配置INx()的状态就可以改变电机转动方向
void Car_Go(void)
{
	//左前电机 前    //右前电机 前
	MOTOR_A(GO);       MOTOR_B(GO);

	//左后电机 前   //右后电机 前
	MOTOR_C(GO);       MOTOR_D(GO);
	
	
}

void Car_Back(void)
{
	//左前电机          //右前电机 
	MOTOR_A(BACK);      MOTOR_B(BACK);

	//左后电机          //右后电机 
	MOTOR_C(BACK);      MOTOR_D(BACK); 
}

//***************************向左***************************//
void Car_Left(void)
{
	
	//左前电机        //右前电机 
	MOTOR_A(BACK);    MOTOR_B(GO);

	//左后电机        //右后电机 
    MOTOR_C(GO);      MOTOR_D(BACK); 
	
}
//***************************向左转圈***************************//
void Car_Turn_Left(void)
{
	
	//左前电机     //右前电机 
MOTOR_A(BACK);       MOTOR_B(GO);

	//左后电机    //右后电机 
 MOTOR_C(BACK);      MOTOR_D(GO);      
	
}
//***************************向右***************************//
void Car_Right(void)
{
	//左前电机     //右前电机 
MOTOR_A(GO);       MOTOR_B(BACK);

	//左后电机    //右后电机 
  MOTOR_C(BACK);   MOTOR_D(GO);       
	
}
//***************************向右转圈***************************//
void Car_Turn_Right(void)
{
	//左前电机      //右前电机  
MOTOR_A(GO);       MOTOR_B(BACK);

	//左后电机     //右后电机  
  MOTOR_C(GO);   MOTOR_D(BACK);      
	
}
//***************************停车***************************//
void Car_Stop(void)
{
	//左前电机 停    //右前电机 停
MOTOR_A(STOP);       MOTOR_B(STOP);

	//左后电机 停   //右后电机 停
   MOTOR_C(STOP);   MOTOR_D(STOP);    
}
//*************************************************************************//

