#ifndef __SENSOR_H
#define __SENSOR_H


#include "stm32f10x.h"


/************************************************
*  �������ƣ�read_infrared_x(x=front/behind/right)
*  ����˵������ȡ�Ҷȴ�����������&���������
*  ����˵������
*  �������أ���
*************************************************/
void read_infrared_front(void);
void read_infrared_behind(void);
void read_infrared_right(void);

char Read_infrared_front(char i);
char Read_Free_Handle_front(char i);
char Read_Count_Handle_front(char i);
char Read_infrared_behind(char i);
char Read_Free_Handle_behind(char i);
char Read_Count_Handle_behind(char i);

#endif



