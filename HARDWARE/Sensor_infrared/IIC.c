#include "IIC.h"
#include "delay.h"

void I2C_SDA_OUT_Front(void)//SDA输出方向配置
{
    GPIO_InitTypeDef GPIO_InitStructure;	

	GPIO_InitStructure.GPIO_Pin=IIC_SDA_Front;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//SDA推挽输出
	GPIO_Init(GPIOX,&GPIO_InitStructure); 						
}

void I2C_SDA_IN_Front(void)//SDA输入方向配置
{
	GPIO_InitTypeDef GPIO_InitStructure;	

	GPIO_InitStructure.GPIO_Pin=IIC_SDA_Front;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//SCL上拉输入
	GPIO_Init(GPIOX,&GPIO_InitStructure);
}

void I2C_SDA_OUT_Behind(void)//SDA输出方向配置
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	//RCC_APB2PeriphClockCmd(CLOCK,ENABLE);
	GPIO_InitStructure.GPIO_Pin=IIC_SDA_Behind;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//SDA推挽输出
	GPIO_Init(GPIOX,&GPIO_InitStructure); 						
}

void I2C_SDA_IN_Behind(void)//SDA输入方向配置
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	//RCC_APB2PeriphClockCmd(CLOCK,ENABLE);
	GPIO_InitStructure.GPIO_Pin=IIC_SDA_Behind;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//SCL上拉输入
	GPIO_Init(GPIOX,&GPIO_InitStructure);
}

//以下为模拟IIC总线函数
void IIC_init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(CLOCK, ENABLE);	 //使能PF端口时钟

	GPIO_InitStructure.GPIO_Pin = IIC_SDA_Front |IIC_SCL_Front|IIC_SDA_Behind |IIC_SCL_Behind;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOX, &GPIO_InitStructure);
	GPIO_SetBits(GPIOX,IIC_SDA_Front|IIC_SCL_Front|IIC_SDA_Behind |IIC_SCL_Behind); 
}

void IIC_start_Front()	//起始信号
{
	I2C_SDA_OUT_Front();
	IIC_Front_SDA=1;	  	  
	IIC_Front_SCL=1;
	delay_us(5);
	IIC_Front_SDA=0;
	delay_us(5);
	IIC_Front_SCL=0;
}

void IIC_stop_Front()		//终止信号
{
	I2C_SDA_OUT_Front();
	IIC_Front_SCL=0;
	IIC_Front_SDA=0;
	delay_us(5);
	IIC_Front_SCL=1; 
	IIC_Front_SDA=1;
	delay_us(5);
}

//主机产生一个应答信号
void IIC_ack_Front()
{
	IIC_Front_SCL=0;
	I2C_SDA_OUT_Front();
  IIC_Front_SDA=0;	
  delay_us(2);
  IIC_Front_SCL=1;
  delay_us(2);
  IIC_Front_SCL=0;	
}

//主机不产生应答信号
void IIC_noack_Front()
{
  IIC_Front_SCL=0;
  I2C_SDA_OUT_Front();
  IIC_Front_SDA=1;
  delay_us(2);
  IIC_Front_SCL=1;
  delay_us(2);
  IIC_Front_SCL=0;
}

//等待从机应答信号
//返回值：1 接收应答失败
//		  0 接收应答成功
char IIC_wait_ack_Front()
{
	u8 tempTime=0;
	I2C_SDA_IN_Front();
	IIC_Front_SDA=1;
	delay_us(1);
	IIC_Front_SCL=1;
	delay_us(1);

	while(READ_Front_SDA)
	{
		tempTime++;
		if(tempTime>250)
		{
			IIC_stop_Front();
			return 1;
		}	 
	}

	IIC_Front_SCL=0;
	return 0;
}

void IIC_send_byte_Front(char txd)
{
	u8 i=0;
	I2C_SDA_OUT_Front();
	IIC_Front_SCL=0;;//拉低时钟开始数据传输
	for(i=0;i<8;i++)
	{
		IIC_Front_SDA=(txd&0x80)>>7;//读取字节
		txd<<=1;
		delay_us(2);
		IIC_Front_SCL=1;
		delay_us(2); //发送数据
		IIC_Front_SCL=0;
		delay_us(2);
	}
}

//读取一个字节
char IIC_read_byte_Front(char ack)
{
	u8 i=0,receive=0;
	I2C_SDA_IN_Front();
  for(i=0;i<8;i++)
  {
   	IIC_Front_SCL=0;
		delay_us(2);
		IIC_Front_SCL=1;
		receive<<=1;//左移
		if(READ_Front_SDA)
		   receive++;//连续读取八位
		delay_us(1);	
  }

  if(!ack)
	  IIC_noack_Front();
	else
		IIC_ack_Front();

	return receive;//返回读取到的字节
}

void IIC_start_Behind()	//起始信号
{
	I2C_SDA_OUT_Behind();
	IIC_Behind_SDA=1;	  	  
	IIC_Behind_SCL=1;
	delay_us(5);
	IIC_Behind_SDA=0;
	delay_us(5);
	IIC_Behind_SCL=0;
}

void IIC_stop_Behind()		//终止信号
{
	I2C_SDA_OUT_Behind();
	IIC_Behind_SCL=0;
	IIC_Behind_SDA=0;
	delay_us(5);
	IIC_Behind_SCL=1; 
	IIC_Behind_SDA=1;
	delay_us(5);
}

//主机产生一个应答信号
void IIC_ack_Behind()
{
	IIC_Behind_SCL=0;
	I2C_SDA_OUT_Behind();
  IIC_Behind_SDA=0;	
  delay_us(2);
  IIC_Behind_SCL=1;
  delay_us(2);
  IIC_Behind_SCL=0;	
}

//主机不产生应答信号
void IIC_noack_Behind()
{
	IIC_Behind_SCL=0;
	I2C_SDA_OUT_Behind();
  IIC_Behind_SDA=1;
  delay_us(2);
  IIC_Behind_SCL=1;
  delay_us(2);
  IIC_Behind_SCL=0;
}

//等待从机应答信号
//返回值：1 接收应答失败
//		  0 接收应答成功
char IIC_wait_ack_Behind()
{
	u8 tempTime=0;
	I2C_SDA_IN_Behind();
	IIC_Behind_SDA=1;
	delay_us(1);
	IIC_Behind_SCL=1;
	delay_us(1);

	while(READ_Behind_SDA)
	{
		tempTime++;
		if(tempTime>250)
		{
			IIC_stop_Behind();
			return 1;
		}	 
	}

	IIC_Behind_SCL=0;
	return 0;
}

void IIC_send_byte_Behind(char txd)
{
	u8 i=0;
	I2C_SDA_OUT_Behind();
	IIC_Behind_SCL=0;;//拉低时钟开始数据传输
	for(i=0;i<8;i++)
	{
		IIC_Behind_SDA=(txd&0x80)>>7;//读取字节
		txd<<=1;
		delay_us(2);
		IIC_Behind_SCL=1;
		delay_us(2); //发送数据
		IIC_Behind_SCL=0;
		delay_us(2);
	}
}

//读取一个字节
char IIC_read_byte_Behind(char ack)
{
	u8 i=0,receive=0;
	I2C_SDA_IN_Behind();
  for(i=0;i<8;i++)
  {
   	IIC_Behind_SCL=0;
		delay_us(2);
		IIC_Behind_SCL=1;
		receive<<=1;//左移
		if(READ_Behind_SDA)
		   receive++;//连续读取八位
		delay_us(1);	
  }

  if(!ack)
	  IIC_noack_Behind();
	else
		IIC_ack_Behind();

	return receive;//返回读取到的字节
}

