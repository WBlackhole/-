#ifndef __TRACK_H
#define __TRACK_H


/************************************************
*  函数名称：Track_X（X=front/behind）
*  功能说明：应用层-循迹
			利用硬件层传回的位置误差进行位置修正
*  参数说明：无
*  函数返回：无
*************************************************/
void Track_front(void);
void Track_behind(void);


#endif

