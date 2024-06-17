#include "motor.h"
#include "delay.h"

#define GO    0//������״̬ ǰ��
#define BACK  1//����
#define STOP  2//ͣ��

//����ǰ������������ĸ�����
#define MOTOR_CLK      RCC_APB2Periph_GPIOD
#define MOTOR_PORT     GPIOD
#define MOTOR_A1       GPIO_Pin_0  //A��
#define MOTOR_A2       GPIO_Pin_1  
#define MOTOR_B1       GPIO_Pin_2  //B��
#define MOTOR_B2       GPIO_Pin_3
#define MOTOR_C1       GPIO_Pin_4  //C��
#define MOTOR_C2       GPIO_Pin_5
#define MOTOR_D1       GPIO_Pin_6  //D��
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
*  �������ƣ�MOTOR_x(x=A/B/C/D)
*  ����˵�������Ƶ��x������ͣת
*  ����˵����state�ǵ��״̬����
*  �������أ���
*  �޸�ʱ�䣺
*************************************************/
static void MOTOR_A(char state)
{
    
	if(state == GO)//��ǰ���ǰ��
	{
      GPIO_SetBits(MOTOR_PORT,MOTOR_A1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_A2);	
	}
	
    if(state == BACK)//��ǰ�������
	{
      GPIO_SetBits(MOTOR_PORT,MOTOR_A2);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_A1);	
	}
	
    if(state == STOP)//ͣת
	{
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_A1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_A2);
	}
		
}

//��ǰB���
static void MOTOR_B(char state)
{
    
	if(state == GO)//��ǰ���ǰ��
	{
	  GPIO_SetBits(MOTOR_PORT,MOTOR_B1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_B2);
	}
	if(state == BACK)//��ǰ�������
	{
		
      GPIO_SetBits(MOTOR_PORT,MOTOR_B2);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_B1);
	
	}
	if(state == STOP)//ͣת
	{
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_B1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_B2);
	}
    
}

//���C���
static void MOTOR_C(char state)
{
    
	if(state == GO)//�����ǰ��
	{
	  GPIO_SetBits(MOTOR_PORT,MOTOR_C1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_C2);

	}
	if(state == BACK)//���������
	{

	
	  GPIO_SetBits(MOTOR_PORT,MOTOR_C2);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_C1);
	
	}
	if(state == STOP)//ͣת
	{
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_C1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_C2);
	}
		
}

//�Һ�D���
static void MOTOR_D(char state)
{
    
	if(state == GO)//�Һ���ǰ��
	{
	  GPIO_SetBits(MOTOR_PORT,MOTOR_D1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_D2);
		
	}
	if(state == BACK)//�Һ�������
	{

	  GPIO_SetBits(MOTOR_PORT,MOTOR_D2);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_D1);
	}
	if(state == STOP)//ͣת
	{
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_D1);
	  GPIO_ResetBits(MOTOR_PORT,MOTOR_D2);
	}
		
}



//*************************************************************************//
//***************************ǰ��****************************//
//ֻҪ����INx()��״̬�Ϳ��Ըı���ת������
void Car_Go(void)
{
	//��ǰ��� ǰ    //��ǰ��� ǰ
	MOTOR_A(GO);       MOTOR_B(GO);

	//����� ǰ   //�Һ��� ǰ
	MOTOR_C(GO);       MOTOR_D(GO);
	
	
}

void Car_Back(void)
{
	//��ǰ���          //��ǰ��� 
	MOTOR_A(BACK);      MOTOR_B(BACK);

	//�����          //�Һ��� 
	MOTOR_C(BACK);      MOTOR_D(BACK); 
}

//***************************����***************************//
void Car_Left(void)
{
	
	//��ǰ���        //��ǰ��� 
	MOTOR_A(BACK);    MOTOR_B(GO);

	//�����        //�Һ��� 
    MOTOR_C(GO);      MOTOR_D(BACK); 
	
}
//***************************����תȦ***************************//
void Car_Turn_Left(void)
{
	
	//��ǰ���     //��ǰ��� 
MOTOR_A(BACK);       MOTOR_B(GO);

	//�����    //�Һ��� 
 MOTOR_C(BACK);      MOTOR_D(GO);      
	
}
//***************************����***************************//
void Car_Right(void)
{
	//��ǰ���     //��ǰ��� 
MOTOR_A(GO);       MOTOR_B(BACK);

	//�����    //�Һ��� 
  MOTOR_C(BACK);   MOTOR_D(GO);       
	
}
//***************************����תȦ***************************//
void Car_Turn_Right(void)
{
	//��ǰ���      //��ǰ���  
MOTOR_A(GO);       MOTOR_B(BACK);

	//�����     //�Һ���  
  MOTOR_C(GO);   MOTOR_D(BACK);      
	
}
//***************************ͣ��***************************//
void Car_Stop(void)
{
	//��ǰ��� ͣ    //��ǰ��� ͣ
MOTOR_A(STOP);       MOTOR_B(STOP);

	//����� ͣ   //�Һ��� ͣ
   MOTOR_C(STOP);   MOTOR_D(STOP);    
}
//*************************************************************************//

