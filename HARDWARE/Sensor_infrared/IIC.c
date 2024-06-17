#include "IIC.h"
#include "delay.h"

void I2C_SDA_OUT_Front(void)//SDA�����������
{
    GPIO_InitTypeDef GPIO_InitStructure;	

	GPIO_InitStructure.GPIO_Pin=IIC_SDA_Front;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//SDA�������
	GPIO_Init(GPIOX,&GPIO_InitStructure); 						
}

void I2C_SDA_IN_Front(void)//SDA���뷽������
{
	GPIO_InitTypeDef GPIO_InitStructure;	

	GPIO_InitStructure.GPIO_Pin=IIC_SDA_Front;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//SCL��������
	GPIO_Init(GPIOX,&GPIO_InitStructure);
}

void I2C_SDA_OUT_Behind(void)//SDA�����������
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	//RCC_APB2PeriphClockCmd(CLOCK,ENABLE);
	GPIO_InitStructure.GPIO_Pin=IIC_SDA_Behind;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//SDA�������
	GPIO_Init(GPIOX,&GPIO_InitStructure); 						
}

void I2C_SDA_IN_Behind(void)//SDA���뷽������
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	//RCC_APB2PeriphClockCmd(CLOCK,ENABLE);
	GPIO_InitStructure.GPIO_Pin=IIC_SDA_Behind;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//SCL��������
	GPIO_Init(GPIOX,&GPIO_InitStructure);
}

//����Ϊģ��IIC���ߺ���
void IIC_init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(CLOCK, ENABLE);	 //ʹ��PF�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = IIC_SDA_Front |IIC_SCL_Front|IIC_SDA_Behind |IIC_SCL_Behind;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOX, &GPIO_InitStructure);
	GPIO_SetBits(GPIOX,IIC_SDA_Front|IIC_SCL_Front|IIC_SDA_Behind |IIC_SCL_Behind); 
}

void IIC_start_Front()	//��ʼ�ź�
{
	I2C_SDA_OUT_Front();
	IIC_Front_SDA=1;	  	  
	IIC_Front_SCL=1;
	delay_us(5);
	IIC_Front_SDA=0;
	delay_us(5);
	IIC_Front_SCL=0;
}

void IIC_stop_Front()		//��ֹ�ź�
{
	I2C_SDA_OUT_Front();
	IIC_Front_SCL=0;
	IIC_Front_SDA=0;
	delay_us(5);
	IIC_Front_SCL=1; 
	IIC_Front_SDA=1;
	delay_us(5);
}

//��������һ��Ӧ���ź�
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

//����������Ӧ���ź�
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

//�ȴ��ӻ�Ӧ���ź�
//����ֵ��1 ����Ӧ��ʧ��
//		  0 ����Ӧ��ɹ�
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
	IIC_Front_SCL=0;;//����ʱ�ӿ�ʼ���ݴ���
	for(i=0;i<8;i++)
	{
		IIC_Front_SDA=(txd&0x80)>>7;//��ȡ�ֽ�
		txd<<=1;
		delay_us(2);
		IIC_Front_SCL=1;
		delay_us(2); //��������
		IIC_Front_SCL=0;
		delay_us(2);
	}
}

//��ȡһ���ֽ�
char IIC_read_byte_Front(char ack)
{
	u8 i=0,receive=0;
	I2C_SDA_IN_Front();
  for(i=0;i<8;i++)
  {
   	IIC_Front_SCL=0;
		delay_us(2);
		IIC_Front_SCL=1;
		receive<<=1;//����
		if(READ_Front_SDA)
		   receive++;//������ȡ��λ
		delay_us(1);	
  }

  if(!ack)
	  IIC_noack_Front();
	else
		IIC_ack_Front();

	return receive;//���ض�ȡ�����ֽ�
}

void IIC_start_Behind()	//��ʼ�ź�
{
	I2C_SDA_OUT_Behind();
	IIC_Behind_SDA=1;	  	  
	IIC_Behind_SCL=1;
	delay_us(5);
	IIC_Behind_SDA=0;
	delay_us(5);
	IIC_Behind_SCL=0;
}

void IIC_stop_Behind()		//��ֹ�ź�
{
	I2C_SDA_OUT_Behind();
	IIC_Behind_SCL=0;
	IIC_Behind_SDA=0;
	delay_us(5);
	IIC_Behind_SCL=1; 
	IIC_Behind_SDA=1;
	delay_us(5);
}

//��������һ��Ӧ���ź�
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

//����������Ӧ���ź�
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

//�ȴ��ӻ�Ӧ���ź�
//����ֵ��1 ����Ӧ��ʧ��
//		  0 ����Ӧ��ɹ�
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
	IIC_Behind_SCL=0;;//����ʱ�ӿ�ʼ���ݴ���
	for(i=0;i<8;i++)
	{
		IIC_Behind_SDA=(txd&0x80)>>7;//��ȡ�ֽ�
		txd<<=1;
		delay_us(2);
		IIC_Behind_SCL=1;
		delay_us(2); //��������
		IIC_Behind_SCL=0;
		delay_us(2);
	}
}

//��ȡһ���ֽ�
char IIC_read_byte_Behind(char ack)
{
	u8 i=0,receive=0;
	I2C_SDA_IN_Behind();
  for(i=0;i<8;i++)
  {
   	IIC_Behind_SCL=0;
		delay_us(2);
		IIC_Behind_SCL=1;
		receive<<=1;//����
		if(READ_Behind_SDA)
		   receive++;//������ȡ��λ
		delay_us(1);	
  }

  if(!ack)
	  IIC_noack_Behind();
	else
		IIC_ack_Behind();

	return receive;//���ض�ȡ�����ֽ�
}

