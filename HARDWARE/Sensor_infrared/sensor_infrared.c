#include "sensor_infrared.h"
#include "main.h"

#define IIC_ADDR 0x78
#define VAL_ADDR 0x80
#define Read_Free 0
#define Read_Count 1


int error_front;       		//С��λ��ƫ�����ֵ
char sensor_front[4];
char a[4],temp[4],Last[4];
char cnt[4]={0};
char State_front[4]={0};

//ë���˲�״̬��
static char Read_Free_Handle_front(char i)
{
	if(a[i]!=Last[i])
	{
		State_front[i]=Read_Count;//״̬Ǩ��
		temp[i]=a[i];//��¼������ֵ����ֵ
	}
	else
	{
		Last[i]=a[i];//��¼Ϊ��ȥֵ
	}
	return Last[i];
}

static char Read_Count_Handle_front(char i)
{
	if(a[i]==temp[i])//������������ֵ
	{
		cnt[i]++;
	}
	else//�ٴη�������
	{
		cnt[i]=0;
		temp[i]=a[i];
	}
	
	if(cnt[i]>1)//����ֵ��Ч
	{
		State_front[i]=Read_Free;
		cnt[i]=0;
		Last[i]=temp[i];
		return temp[i];
	}
	else//��Ч
	{
		return Last[i];
	}
}

static char Read_infrared_front(char i)
{
	static char Sensor_front;
	switch(State_front[i])//ԭʼ����
	{
		case Read_Free:Sensor_front=Read_Free_Handle_front(i);break;
		case Read_Count:Sensor_front=Read_Count_Handle_front(i);break;
	}
	
	return Sensor_front;//�˲�����
}

//�Ҷȴ��������ݶ�ȡ
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
