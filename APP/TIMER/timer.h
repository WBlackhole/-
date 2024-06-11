#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

//通用定时器6中断初始化
void TIM6_Int_Init(u16 arr,u16 psc);
void Delay_ms(int ums);

#endif























