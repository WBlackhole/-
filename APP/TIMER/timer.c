#include "timer.h"
#include "main.h"

	

//ͨ�ö�ʱ��6�жϳ�ʼ�����ж�ʱ��=psc*arr/72M
void TIM6_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<4;	
 	TIM6->ARR=arr;  	 
	TIM6->PSC=psc;  		  
	TIM6->DIER|=1<<0;  
	TIM6->CR1|=0x01;  
	MY_NVIC_Init(1,3,TIM6_IRQn,2);							 
}

//��ʱ��6�жϷ������,�ж�ʱ�����жϳ�ʼ����������	 
void TIM6_IRQHandler(void)
{ 		    		  			    

	
	TIM6->SR&=~(1<<0); 	    
}











