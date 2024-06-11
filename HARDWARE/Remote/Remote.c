#include "stm32f10x.h"
#include "Remote.h"
 
uint16_t IR_Time;
uint8_t IR_State=1;
uint8_t IR_Data[4];
uint8_t IR_pData;
uint8_t IR_DataFlag;
uint8_t IR_RepeatFlag;
uint8_t IR_Address;
uint8_t IR_Command;
 
//初始化
void Remote_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//内部时钟
	TIM_InternalClockConfig(TIM1);
	//时基单元 TIM1->高级定时器 1US
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	//输入捕获
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;  //通道1
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling; //下降沿捕获
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM1, &TIM_ICInitStructure);
	//主从触发模式  捕获后CNT计数器自动清零
	TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);
	//NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;  //TIM1中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);    	
    //允许CC1IE捕获中断
	TIM_ITConfig(TIM1,TIM_IT_CC1,ENABLE);	
    
    TIM_Cmd(TIM1, ENABLE);
}
 
//返回时间
uint32_t IC_GetFreq(void)
{
	return (TIM_GetCapture1(TIM1) + 1);
}

//以下代码使用了输入捕获来获取两个下降沿之间的时间，使用一个周期为1US的波形作为基准
//通过下降沿捕获得到两个下降沿之间的基准波形的次数，从而得到时间
//再结合NEC解码，即可写出解码过程
//输入捕获中断
void TIM1_CC_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_CC1) == SET)
	{
		if(IR_State==1)		//状态1，等待Start信号或Repeat信号
		{
			IR_Time = IC_GetFreq();
			//如果计时为13.5ms，则接收到了Start信号（判定值在12MHz晶振下为13500，在11.0592MHz晶振下为12442）
			if(IR_Time>13500-500 && IR_Time<13500+500)
			{
				IR_State=2;			//置状态为2
			}
			//如果计时为11.25ms，则接收到了Repeat信号（判定值在12MHz晶振下为11250，在11.0592MHz晶振下为10368）
			else if(IR_Time>11250-500 && IR_Time<11250+500)
			{
				IR_RepeatFlag=1;	//置收到连发帧标志位为1
				IR_State=1;			//置状态为0
			}
			else					//接收出错
			{
				IR_State=1;			//置状态为1
			}
		}
		else if(IR_State==2)		//状态2，接收数据
		{
			IR_Time = IC_GetFreq();
			//如果计时为1120us，则接收到了数据0（判定值在12MHz晶振下为1120，在11.0592MHz晶振下为1032）
			if(IR_Time>1120-500 && IR_Time<1120+500)
			{
				IR_Data[IR_pData/8]&=~(0x01<<(IR_pData%8));	//数据对应位清0
				IR_pData++;			//数据位置指针自增
			}
			//如果计时为2250us，则接收到了数据1（判定值在12MHz晶振下为2250，在11.0592MHz晶振下为2074）
			else if(IR_Time>2240-500 && IR_Time<2240+500)
			{
				IR_Data[IR_pData/8]|=(0x01<<(IR_pData%8));	//数据对应位置1
				IR_pData++;			//数据位置指针自增
			}
			else					//接收出错
			{
				IR_pData=0;			//数据位置指针清0
				IR_State=1;			//置状态为1
			}
			if(IR_pData>=32)		//如果接收到了32位数据
			{
				IR_pData=0;			//数据位置指针清0
                //验证数据是否接收正确 再转存
				if((IR_Data[0] & IR_Data[1])==0 && (IR_Data[2] & IR_Data[3])==0)
				{
					IR_Address=IR_Data[0];	//转存数据
					IR_Command=IR_Data[2];
					IR_DataFlag=1;	//置收到连发帧标志位为1
				}
				IR_State=1;			//置状态为0
			}
		}
	}
	TIM_ClearITPendingBit(TIM1,TIM_IT_CC1);
}
 
// 红外遥控获取收到数据帧标志位
uint8_t IR_GetDataFlag(void)
{
	if(IR_DataFlag)
	{
		IR_DataFlag=0;
		return 1;
	}
	return 0;
}
 
// 红外遥控获取收到连发帧标志位
uint8_t IR_GetRepeatFlag(void)
{
	if(IR_RepeatFlag)
	{
		IR_RepeatFlag=0;
		return 1;
	}
	return 0;
}
 
// 红外遥控获取收到的地址数据
uint8_t IR_GetAddress(void)
{
	return IR_Address;
}
 
// 红外遥控获取收到的命令数据
uint8_t IR_GetCommand(void)
{
	return IR_Command;
}

//应用
//if(IR_GetDataFlag() || IR_GetRepeatFlag())	//如果收到数据帧或者收到连发帧
//{
//	Address=IR_GetAddress();		//获取遥控器地址码
//	Command=IR_GetCommand();		//获取遥控器命令码
//}


