#include "usart.h"
#include "main.h"
#include "math.h"


////////////////////////////////////////////////////////////////////////////////// 	 

//////////////////////////////////////////////////////////////////
/*ʹ��microLib�ķ���*/

// ��������
int fputc(int ch, FILE *f)
{
		USART_SendData(USART1, (unsigned char) ch);// USART1 ???? USART2 ?
		while (!(USART1->SR & USART_FLAG_TXE));
		return (ch);
}
	 
// ��������
int GetKey (void)  
{
		while (!(USART1->SR & USART_FLAG_RXNE));
		return ((int)(USART1->DR & 0x1FF));
} 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  
void USART1_Init(void)
{
	//USART1_TX:PA 9   
	//USART1_RX:PA10
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//������Ӧ�˿�ʱ��	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//����pa.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��GPIOA.9���Ͷ�
	
	//USART1_RX PA.10 ��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//����pa.10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��GPIOA.10���ն�
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//��Ӧ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//��ռ���ȼ�Ϊ3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//�����ȼ�Ϊ3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);//�ж����ȼ�����
	
	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate  = 115200;//���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//�շ�ģʽ
	USART_Init(USART1,&USART_InitStructure);//��ʼ������1
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//�����ж�
	USART_Cmd(USART1,ENABLE);//ʹ�ܴ���
}

//ASCIIתʮ����
char ASCII_To_Value(char asc) 
{
    char value;
    switch (asc) 
    {
        case 0x30: // '0' �� ASCII ��Ϊ 0x30��ʮ����Ϊ 48
            value = 0;
            break;
        case 0x31:
            value = 1;
            break;
        case 0x32:
            value = 2;
            break;
        case 0x33:
            value = 3;
            break;
        case 0x34:
            value = 4;
            break;
        case 0x35:
            value = 5;
            break;
        case 0x36:
            value = 6;
            break;
        case 0x37:
            value = 7;
            break;
        case 0x38:
            value = 8;
            break;
        case 0x39:
            value = 9;
            break;
    }
    return value;
}

u8 sight_flag=0;//�ж����ݽ��ձ�־λ
u8 sight_flag_1=0;//�Ӿ�����һ��ʼ��־λ 
u8 sight_flag_2=0;//�Ӿ��������ʼ��־λ
u8 sight_flag_over=0;//�Ӿ����������־λ 
 
u8 transform[3]={0};//�漴�任װ��ɨ�������м�洢����
u8 transform_result;//�漴װ��ʶ����
u8 sight_transform=0;//ʶ������һ��ʼ��־λ

u8 place_data_close[3]={0};//����������ɨ�������м�洢����
u8 place_data_far[3]={0};//������Զ��ɨ�������м�洢����
u8 close_over=0;//����ɨ�������־λ
u8 far_over=0;//Զ��ɨ�������־λ
u8 place_close;//�������
u8 place_far;//Զ�����
u8 sight_place;//ʶ���������ʼ��־λ
u8 RxBuffer[10]={0};//���ݸ�ʽ��0x41 0x4F ��� 0x54�������X ��Y�� Lable��a||b||c���� 
u8 RxCounter=0;
void USART1_IRQHandler(void)			 
{
		u8 com_data; 
		u8 i;
		static u8 RxState = 0;	 
		if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET&&sight_flag)  	   //�����ж�  
		{			
			USART_ClearITPendingBit(USART1,USART_IT_RXNE);   //����жϱ�־
			com_data = USART_ReceiveData(USART1);
			static u8 X,Y,comma_Index_X,comma_Index_Y;
			if(RxState==0&&com_data==0x41)  //0x41֡ͷ
			{
				RxState=1;
				RxBuffer[RxCounter++]=com_data;
			}		
			else if(RxState==1&&com_data==0x4F)  //0x4F֡ͷ
			{
				RxState=2;
				RxBuffer[RxCounter++]=com_data;
			}		
			else if(RxState==2)
			{
				RxBuffer[RxCounter++]=com_data;
				if(com_data==0x2C)//���� 
				{
					RxState=3;
					comma_Index_X=RxCounter-1;
					X=0;
					for(i=2;i<comma_Index_X;i++)
					{
						X+=ASCII_To_Value(RxBuffer[i])*pow(10,comma_Index_X-i-1);
					}
					if(X<30||X>120)//���X���ڷ�Χ��
					{
						//������Ч���
						RxCounter = 0;
						RxState = 0;
						for(i=0;i<10;i++)
						{
							RxBuffer[i]=0x00;      
						}						
					}
				}
			}
			else if(RxState==3)
			{
				RxBuffer[RxCounter++]=com_data;
				if(com_data==0x2C)
				{
					RxState=4;
					comma_Index_Y=RxCounter-1;
					Y=0;
					for(i=comma_Index_X+1;i<comma_Index_Y;i++)
					{
						Y+=ASCII_To_Value(RxBuffer[i])*pow(10,comma_Index_Y-i-1);
					}
				}
			}
			//����һ
			else if(RxState==4&&sight_flag_1)//RxBuffer�������Ӿ�����һ��־λ����
			{
				RxBuffer[RxCounter++]=com_data; 			
				switch(RxBuffer[comma_Index_Y+1])
				{
					case 'a':transform[0]++;break;
					case 'b':transform[1]++;break;
					case 'c':transform[2]++;break;
				}
				//����ɨ����ʮ�ε�ʶ����
				if(transform[0]==10||transform[1]==10||transform[2]==10)
				{
					//���ݽ�����ϣ���״̬����ֹͣ������Ϣ
					sight_flag=0; 
					sight_flag_1=0;
					sight_flag_over=1;
					if(transform[0]==10)
					{
						transform_result='a';
					}
					else if(transform[1]==10)
					{
						transform_result='b';
					}
					else if(transform[2]==10)
					{
						transform_result='c';
					}
				}
				//��ջ��������½�������
				RxState = 0;
				RxCounter=0;
				for(i=0;i<4;i++)
				{
					RxBuffer[i]=0x00;      
				}
			}
			//����� 
			else if(RxState==4&&sight_flag_2)//RxBuffer�������Ӿ��������־λ����
			{
				RxBuffer[RxCounter++]=com_data;
				if(Y>0&&Y<50&&close_over==0)//����������ݴ���
				{
					switch(RxBuffer[comma_Index_Y+1])//���ݽ���
					{
						case 'a':place_data_close[0]++;break;
						case 'b':place_data_close[1]++;break;
						case 'c':place_data_close[2]++;break;
					}
					//����ɨ����ʮ�ε���飬ȷ���������
					if(place_data_close[0]==10||place_data_close[1]==10||place_data_close[2]==10)
					{
						close_over=1;
						if(place_data_close[0]==10)
						{
							place_close='a';
						}
						else if(place_data_close[1]==10)
						{
							place_close='b';
						}
						else if(place_data_close[2]==10)
						{
							place_close='c';
						}
					}
				}
				else if(Y>50&&Y<150&&far_over==0)
				{
					switch(RxBuffer[comma_Index_Y+1])//ʮ�����ݽ���
					{
						case 'a':place_data_far[0]++;break;
						case 'b':place_data_far[1]++;break;
						case 'c':place_data_far[2]++;break;
					}
					//����ɨ����ʮ�ε���飬ȷ��Զ�����
					if(place_data_far[0]==10||place_data_far[1]==10||place_data_far[2]==10)
					{
						far_over=1;
						if(place_data_far[0]==10)
						{
							place_far='a';
						}
						else if(place_data_far[1]==10)
						{
							place_far='b';
						}
						else if(place_data_far[2]==10)
						{
							place_far='c';
						}
					}
				}
				//������Զ��ɨ����������������״̬��,ֹͣ��������
				if(far_over&&close_over)
				{
					sight_flag_over=1;
					sight_flag_2=0; 
					sight_flag=0;
					//׼���´�ɨ��
					far_over=0;
					close_over=0;
				}
				//��ջ��������½�������
				RxState = 0;
				RxCounter=0;
				for(i=0;i<4;i++)
				{
					RxBuffer[i]=0x00;      
				}
			}
			else   //�����쳣
			{
				RxState = 0;
				RxCounter=0;
				for(i=0;i<10;i++)
				{
					RxBuffer[i]=0x00;      //�����������������
				}
			}
			if(RxCounter > 10)            //�����쳣
			{
				RxState = 0;
				RxCounter=0;
				for(i=0;i<10;i++)
				{
					RxBuffer[i]=0x00;      //�����������������
				}
			
			}
		}				
}
#endif	

