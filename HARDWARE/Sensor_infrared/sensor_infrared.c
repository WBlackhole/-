#include "sensor_infrared.h"
#include "main.h"

#define IIC_ADDR 0x78
#define VAL_ADDR 0x80
#define Read_Free 0
#define Read_Count 1


int error_front,error_behind;       		//С��λ��ƫ�����ֵ
char sensor_front[4];
char sensor_behind[4];
char sensor_right[2];   	//����ǰ��·���⴫�������ص�ֵ
char a[4],temp_a[4],Last_a[4];
char cnt_a[4]={0};
char State_front[4]={0};
char b[4],temp_b[4],Last_b[4];
char cnt_b[4]={0};
char State_behind[4]={0};


void read_infrared_front(void)
{
	static char Sensor_state;
	u8 val;
	IIC_start_Front(); //����
	IIC_send_byte_Front(IIC_ADDR << 1); //����дָ��
	IIC_send_byte_Front(VAL_ADDR); //�Ĵ�����ַ
	IIC_wait_ack_Front(); //Ӧ��
	IIC_stop_Front(); //ֹͣ
	IIC_start_Front(); //��������
	IIC_send_byte_Front((IIC_ADDR << 1) | 0x01); //���Ͷ�ָ��
	IIC_wait_ack_Front(); //Ӧ��
	val = IIC_read_byte_Front(0); //��ȡһ���ֽ�
	IIC_stop_Front(); //ֹͣ

    a[0]=((val>>0) & 0x01)+0x30; //����Ĵ�����
    a[1]=((val>>1) & 0x01)+0x30;
    a[2]=((val>>2) & 0x01)+0x30;
    a[3]=((val>>3) & 0x01)+0x30;

    sensor_front[0]=Read_infrared_front(0)-'0'; //����Ĵ�����
    sensor_front[1]=Read_infrared_front(1)-'0';
    sensor_front[2]=Read_infrared_front(2)-'0';
    sensor_front[3]=Read_infrared_front(3)-'0';
	
	Sensor_state=sensor_front[0]*8+sensor_front[1]*4+sensor_front[2]*2+sensor_front[3];
	
	switch(Sensor_state)
	{
		case 0x6:
			error_front=0;//���� (0110)
			break;
		case 0x4:
			error_front=-1;//΢ƫ�� (0100)
			break;
		case 0xC:
			error_front=-2;//��ƫ�� (1100)
			break;
		case 0x8:
			error_front=-3;//����ƫ�� (1000)
			break;
		case 0xE:
			error_front=-4;//��ת���� (1110)
			break;
		case 0x2:
			error_front=1;//΢ƫ�� (0010)
			break;
		case 0x3:
			error_front=2;//��ƫ�� (0011)
			break;
		case 0x1:
			error_front=3;//����ƫ�� (0001)
			break;
		case 0x7:
			error_front=4;//��ת���� (0111)
			break;
		case 0xF:
			error_front=5;//(1111)
			break;
		case 0x0:
			error_front=6;//(0000)
			break;
	}
}


void read_infrared_behind(void)
{
	static char Sensor_state;
	u8 val;
	IIC_start_Behind(); //����
	IIC_send_byte_Behind(IIC_ADDR << 1); //����дָ��
	IIC_send_byte_Behind(VAL_ADDR); //�Ĵ�����ַ
	IIC_wait_ack_Behind(); //Ӧ��
	IIC_stop_Behind(); //ֹͣ
	IIC_start_Behind(); //��������
	IIC_send_byte_Behind((IIC_ADDR << 1) | 0x01); //���Ͷ�ָ��
	IIC_wait_ack_Behind(); //Ӧ��
	val = IIC_read_byte_Behind(0); //��ȡһ���ֽ�
	IIC_stop_Behind(); //ֹͣ

    b[0]=((val>>0) & 0x01)+0x30; //����Ĵ�����
    b[1]=((val>>1) & 0x01)+0x30;
    b[2]=((val>>2) & 0x01)+0x30;
    b[3]=((val>>3) & 0x01)+0x30;

    sensor_behind[0]=Read_infrared_behind(0)-'0'; //����Ĵ�����
    sensor_behind[1]=Read_infrared_behind(1)-'0';
    sensor_behind[2]=Read_infrared_behind(2)-'0';
    sensor_behind[3]=Read_infrared_behind(3)-'0';
	
	Sensor_state=sensor_behind[0]*8+sensor_behind[1]*4+sensor_behind[2]*2+sensor_behind[3];
	
	switch(Sensor_state)
	{
		case 0x6:
			error_behind=0;//���� (0110)
			break;
		case 0x4:
			error_behind=-1;//΢ƫ�� (0100)
			break;
		case 0xC:
			error_behind=-2;//��ƫ�� (1100)
			break;
		case 0x8:
			error_behind=-3;//����ƫ�� (1000)
			break;
		case 0xE:
			error_behind=-4;//��ת���� (1110)
			break;
		case 0x2:
			error_behind=1;//΢ƫ�� (0010)
			break;
		case 0x3:
			error_behind=2;//��ƫ�� (0011)
			break;
		case 0x1:
			error_behind=3;//����ƫ�� (0001)
			break;
		case 0x7:
			error_behind=4;//��ת���� (0111)
			break;
		case 0xF:
			error_behind=5;//(1111)
			break;
		case 0x0:
			error_behind=6;//(0000)
			break;
	}
}

void read_infrared_right(void)
{
    sensor_right[0]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11);//�Ҳ��ϴ�����
    sensor_right[1]=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);//�Ҳ��´�����
}

//״̬�����-ë���˲�״̬��
char Read_infrared_front(char i)
{
	static char Sensor_front;
	switch(State_front[i])
	{
		case Read_Free:Sensor_front=Read_Free_Handle_front(i);break;
		case Read_Count:Sensor_front=Read_Count_Handle_front(i);break;
	}
	
	return Sensor_front;
}

char Read_Free_Handle_front(char i)
{
	if(a[i]!=Last_a[i])
	{
		State_front[i]=Read_Count;//״̬Ǩ��
		temp_a[i]=a[i];//��¼������ֵ����ֵ
	}
	else
	{
		Last_a[i]=a[i];//��¼Ϊ��ȥֵ
	}
	return Last_a[i];
}

char Read_Count_Handle_front(char i)
{
	if(a[i]==temp_a[i])//������������ֵ
	{
		cnt_a[i]++;
	}
	else//�ٴη�������
	{
		cnt_a[i]=0;
		temp_a[i]=a[i];
	}
	
	if(cnt_a[i]>1)//����ֵ��Ч
	{
		State_front[i]=Read_Free;
		cnt_a[i]=0;
		Last_a[i]=temp_a[i];
		return temp_a[i];
	}
	else//��Ч
	{
		return Last_a[i];
	}
}

char Read_infrared_behind(char i)
{
	static char Sensor_behind;
	switch(State_behind[i])
	{
		case Read_Free:Sensor_behind=Read_Free_Handle_behind(i);break;
		case Read_Count:Sensor_behind=Read_Count_Handle_behind(i);break;
	}
	
	return Sensor_behind;
}

char Read_Free_Handle_behind(char i)
{
	if(b[i]!=Last_b[i])
	{
		State_behind[i]=Read_Count;//״̬Ǩ��
		temp_b[i]=b[i];//��¼������ֵ����ֵ
	}
	else
	{
		Last_b[i]=b[i];//��¼Ϊ��ȥֵ
	}
	return Last_b[i];
}

char Read_Count_Handle_behind(char i)
{
	if(b[i]==temp_b[i])//������������ֵ
	{
		cnt_b[i]++;
	}
	else//�ٴη�������
	{
		cnt_b[i]=0;
		temp_b[i]=b[i];
	}
	
	if(cnt_b[i]>1)//����ֵ��Ч
	{
		State_behind[i]=Read_Free;
		cnt_b[i]=0;
		Last_b[i]=temp_b[i];
		return temp_b[i];
	}
	else//��Ч
	{
		return Last_b[i];
	}
}
