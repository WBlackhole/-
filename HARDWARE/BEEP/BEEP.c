#include "main.h"
#include "beep.h"

//D10Òý½Å
void BEEP_Init(void)
 {
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOD,GPIO_Pin_10);
 }

void BEEP_sound(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_10);
	Delay_ms(500);
	GPIO_ResetBits(GPIOD,GPIO_Pin_10);
}
 
