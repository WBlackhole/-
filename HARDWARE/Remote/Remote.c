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
 
//��ʼ��
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
	//�ڲ�ʱ��
	TIM_InternalClockConfig(TIM1);
	//ʱ����Ԫ TIM1->�߼���ʱ�� 1US
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	//���벶��
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;  //ͨ��1
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling; //�½��ز���
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM1, &TIM_ICInitStructure);
	//���Ӵ���ģʽ  �����CNT�������Զ�����
	TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);
	//NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;  //TIM1�ж�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);    	
    //����CC1IE�����ж�
	TIM_ITConfig(TIM1,TIM_IT_CC1,ENABLE);	
    
    TIM_Cmd(TIM1, ENABLE);
}
 
//����ʱ��
uint32_t IC_GetFreq(void)
{
	return (TIM_GetCapture1(TIM1) + 1);
}

//���´���ʹ�������벶������ȡ�����½���֮���ʱ�䣬ʹ��һ������Ϊ1US�Ĳ�����Ϊ��׼
//ͨ���½��ز���õ������½���֮��Ļ�׼���εĴ������Ӷ��õ�ʱ��
//�ٽ��NEC���룬����д���������
//���벶���ж�
void TIM1_CC_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_CC1) == SET)
	{
		if(IR_State==1)		//״̬1���ȴ�Start�źŻ�Repeat�ź�
		{
			IR_Time = IC_GetFreq();
			//�����ʱΪ13.5ms������յ���Start�źţ��ж�ֵ��12MHz������Ϊ13500����11.0592MHz������Ϊ12442��
			if(IR_Time>13500-500 && IR_Time<13500+500)
			{
				IR_State=2;			//��״̬Ϊ2
			}
			//�����ʱΪ11.25ms������յ���Repeat�źţ��ж�ֵ��12MHz������Ϊ11250����11.0592MHz������Ϊ10368��
			else if(IR_Time>11250-500 && IR_Time<11250+500)
			{
				IR_RepeatFlag=1;	//���յ�����֡��־λΪ1
				IR_State=1;			//��״̬Ϊ0
			}
			else					//���ճ���
			{
				IR_State=1;			//��״̬Ϊ1
			}
		}
		else if(IR_State==2)		//״̬2����������
		{
			IR_Time = IC_GetFreq();
			//�����ʱΪ1120us������յ�������0���ж�ֵ��12MHz������Ϊ1120����11.0592MHz������Ϊ1032��
			if(IR_Time>1120-500 && IR_Time<1120+500)
			{
				IR_Data[IR_pData/8]&=~(0x01<<(IR_pData%8));	//���ݶ�Ӧλ��0
				IR_pData++;			//����λ��ָ������
			}
			//�����ʱΪ2250us������յ�������1���ж�ֵ��12MHz������Ϊ2250����11.0592MHz������Ϊ2074��
			else if(IR_Time>2240-500 && IR_Time<2240+500)
			{
				IR_Data[IR_pData/8]|=(0x01<<(IR_pData%8));	//���ݶ�Ӧλ��1
				IR_pData++;			//����λ��ָ������
			}
			else					//���ճ���
			{
				IR_pData=0;			//����λ��ָ����0
				IR_State=1;			//��״̬Ϊ1
			}
			if(IR_pData>=32)		//������յ���32λ����
			{
				IR_pData=0;			//����λ��ָ����0
                //��֤�����Ƿ������ȷ ��ת��
				if((IR_Data[0] & IR_Data[1])==0 && (IR_Data[2] & IR_Data[3])==0)
				{
					IR_Address=IR_Data[0];	//ת������
					IR_Command=IR_Data[2];
					IR_DataFlag=1;	//���յ�����֡��־λΪ1
				}
				IR_State=1;			//��״̬Ϊ0
			}
		}
	}
	TIM_ClearITPendingBit(TIM1,TIM_IT_CC1);
}
 
// ����ң�ػ�ȡ�յ�����֡��־λ
uint8_t IR_GetDataFlag(void)
{
	if(IR_DataFlag)
	{
		IR_DataFlag=0;
		return 1;
	}
	return 0;
}
 
// ����ң�ػ�ȡ�յ�����֡��־λ
uint8_t IR_GetRepeatFlag(void)
{
	if(IR_RepeatFlag)
	{
		IR_RepeatFlag=0;
		return 1;
	}
	return 0;
}
 
// ����ң�ػ�ȡ�յ��ĵ�ַ����
uint8_t IR_GetAddress(void)
{
	return IR_Address;
}
 
// ����ң�ػ�ȡ�յ�����������
uint8_t IR_GetCommand(void)
{
	return IR_Command;
}

//Ӧ��
//if(IR_GetDataFlag() || IR_GetRepeatFlag())	//����յ�����֡�����յ�����֡
//{
//	Address=IR_GetAddress();		//��ȡң������ַ��
//	Command=IR_GetCommand();		//��ȡң����������
//}


