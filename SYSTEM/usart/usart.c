#include "usart.h"
#include "main.h"
#include "math.h"


////////////////////////////////////////////////////////////////////////////////// 	 

//////////////////////////////////////////////////////////////////
/*使用microLib的方法*/

// 发送数据
int fputc(int ch, FILE *f)
{
		USART_SendData(USART1, (unsigned char) ch);// USART1 ???? USART2 ?
		while (!(USART1->SR & USART_FLAG_TXE));
		return (ch);
}
	 
// 接收数据
int GetKey (void)  
{
		while (!(USART1->SR & USART_FLAG_RXNE));
		return ((int)(USART1->DR & 0x1FF));
} 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  
  
void USART1_Init(void)
{
	//USART1_TX:PA 9   
	//USART1_RX:PA10
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//开启对应端口时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//引脚pa.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速率50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIOA.9发送端
	
	//USART1_RX PA.10 浮空输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//引脚pa.10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIOA.10接收端
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//对应中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//抢占优先级为3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//子优先级为3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);//中断优先级设置
	
	//USART 初始化设置
	USART_InitStructure.USART_BaudRate  = 115200;//设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件控制流
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//收发模式
	USART_Init(USART1,&USART_InitStructure);//初始化串口1
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//开启中断
	USART_Cmd(USART1,ENABLE);//使能串口
}

//ASCII转十进制
char ASCII_To_Value(char asc) 
{
    char value;
    switch (asc) 
    {
        case 0x30: // '0' 的 ASCII 码为 0x30，十进制为 48
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

u8 sight_flag=0;//中断数据接收标志位
u8 sight_flag_1=0;//视觉任务一开始标志位 
u8 sight_flag_2=0;//视觉任务二开始标志位
u8 sight_flag_over=0;//视觉任务结束标志位 
 
u8 transform[3]={0};//随即变换装置扫描结果的中间存储数组
u8 transform_result;//随即装置识别结果
u8 sight_transform=0;//识别任务一开始标志位

u8 place_data_close[3]={0};//放置区近处扫描结果的中间存储数组
u8 place_data_far[3]={0};//放置区远处扫描结果的中间存储数组
u8 close_over=0;//近处扫描结束标志位
u8 far_over=0;//远处扫描结束标志位
u8 place_close;//近处结果
u8 place_far;//远处结果
u8 sight_place;//识别任务二开始标志位
u8 RxBuffer[10]={0};//数据格式：0x41 0x4F 结果 0x54（结果：X ，Y， Lable【a||b||c】） 
u8 RxCounter=0;
void USART1_IRQHandler(void)			 
{
		u8 com_data; 
		u8 i;
		static u8 RxState = 0;	 
		if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET&&sight_flag)  	   //接收中断  
		{			
			USART_ClearITPendingBit(USART1,USART_IT_RXNE);   //清除中断标志
			com_data = USART_ReceiveData(USART1);
			static u8 X,Y,comma_Index_X,comma_Index_Y;
			if(RxState==0&&com_data==0x41)  //0x41帧头
			{
				RxState=1;
				RxBuffer[RxCounter++]=com_data;
			}		
			else if(RxState==1&&com_data==0x4F)  //0x4F帧头
			{
				RxState=2;
				RxBuffer[RxCounter++]=com_data;
			}		
			else if(RxState==2)
			{
				RxBuffer[RxCounter++]=com_data;
				if(com_data==0x2C)//逗号 
				{
					RxState=3;
					comma_Index_X=RxCounter-1;
					X=0;
					for(i=2;i<comma_Index_X;i++)
					{
						X+=ASCII_To_Value(RxBuffer[i])*pow(10,comma_Index_X-i-1);
					}
					if(X<30||X>120)//如果X不在范围内
					{
						//数据无效清空
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
			//任务一
			else if(RxState==4&&sight_flag_1)//RxBuffer接受且视觉任务一标志位开启
			{
				RxBuffer[RxCounter++]=com_data; 			
				switch(RxBuffer[comma_Index_Y+1])
				{
					case 'a':transform[0]++;break;
					case 'b':transform[1]++;break;
					case 'c':transform[2]++;break;
				}
				//出现扫描结果十次的识别物
				if(transform[0]==10||transform[1]==10||transform[2]==10)
				{
					//数据接收完毕，打开状态机，停止接收信息
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
				//清空缓冲区重新接收数据
				RxState = 0;
				RxCounter=0;
				for(i=0;i<4;i++)
				{
					RxBuffer[i]=0x00;      
				}
			}
			//任务二 
			else if(RxState==4&&sight_flag_2)//RxBuffer接受且视觉任务二标志位开启
			{
				RxBuffer[RxCounter++]=com_data;
				if(Y>0&&Y<50&&close_over==0)//近处物块数据处理
				{
					switch(RxBuffer[comma_Index_Y+1])//数据接收
					{
						case 'a':place_data_close[0]++;break;
						case 'b':place_data_close[1]++;break;
						case 'c':place_data_close[2]++;break;
					}
					//出现扫描结果十次的物块，确定近处物块
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
					switch(RxBuffer[comma_Index_Y+1])//十次数据接收
					{
						case 'a':place_data_far[0]++;break;
						case 'b':place_data_far[1]++;break;
						case 'c':place_data_far[2]++;break;
					}
					//出现扫描结果十次的物块，确定远处物块
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
				//近处和远处扫描结果均结束，进入状态机,停止接收数据
				if(far_over&&close_over)
				{
					sight_flag_over=1;
					sight_flag_2=0; 
					sight_flag=0;
					//准备下次扫描
					far_over=0;
					close_over=0;
				}
				//清空缓冲区重新接收数据
				RxState = 0;
				RxCounter=0;
				for(i=0;i<4;i++)
				{
					RxBuffer[i]=0x00;      
				}
			}
			else   //接收异常
			{
				RxState = 0;
				RxCounter=0;
				for(i=0;i<10;i++)
				{
					RxBuffer[i]=0x00;      //将存放数据数组清零
				}
			}
			if(RxCounter > 10)            //接收异常
			{
				RxState = 0;
				RxCounter=0;
				for(i=0;i<10;i++)
				{
					RxBuffer[i]=0x00;      //将存放数据数组清零
				}
			
			}
		}				
}
#endif	

