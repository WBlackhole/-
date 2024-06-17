#include "sensor_infrared.h"
#include "main.h"

#define IIC_ADDR 0x78
#define VAL_ADDR 0x80
#define Read_Free 0
#define Read_Count 1


int error_front;       		//小车位置偏差误差值
char sensor_front[4];
char a[4],temp[4],Last[4];
char cnt[4]={0};
char State_front[4]={0};

//毛刺滤波状态机
static char Read_Free_Handle_front(char i)
{
	if(a[i]!=Last[i])
	{
		State_front[i]=Read_Count;//状态迁移
		temp[i]=a[i];//记录传感器值跳变值
	}
	else
	{
		Last[i]=a[i];//记录为过去值
	}
	return Last[i];
}

static char Read_Count_Handle_front(char i)
{
	if(a[i]==temp[i])//持续等于跳变值
	{
		cnt[i]++;
	}
	else//再次发生跳变
	{
		cnt[i]=0;
		temp[i]=a[i];
	}
	
	if(cnt[i]>1)//跳变值有效
	{
		State_front[i]=Read_Free;
		cnt[i]=0;
		Last[i]=temp[i];
		return temp[i];
	}
	else//无效
	{
		return Last[i];
	}
}

static char Read_infrared_front(char i)
{
	static char Sensor_front;
	switch(State_front[i])//原始数据
	{
		case Read_Free:Sensor_front=Read_Free_Handle_front(i);break;
		case Read_Count:Sensor_front=Read_Count_Handle_front(i);break;
	}
	
	return Sensor_front;//滤波数据
}

//灰度传感器数据读取
void read_infrared_front(void)
{
	static char Sensor_state;
	u8 val;
	IIC_start_Front(); //启动
	IIC_send_byte_Front(IIC_ADDR << 1); //发送写指令
	IIC_send_byte_Front(VAL_ADDR); //寄存器地址
	IIC_wait_ack_Front(); //应答
	IIC_stop_Front(); //停止
	IIC_start_Front(); //重新启动
	IIC_send_byte_Front((IIC_ADDR << 1) | 0x01); //发送读指令
	IIC_wait_ack_Front(); //应答
	val = IIC_read_byte_Front(0); //读取一个字节
	IIC_stop_Front(); //停止

    a[0]=((val>>0) & 0x01)+0x30; //最左的传感器
    a[1]=((val>>1) & 0x01)+0x30;
    a[2]=((val>>2) & 0x01)+0x30;
    a[3]=((val>>3) & 0x01)+0x30;

    sensor_front[0]=Read_infrared_front(0)-'0'; //最左的传感器
    sensor_front[1]=Read_infrared_front(1)-'0';
    sensor_front[2]=Read_infrared_front(2)-'0';
    sensor_front[3]=Read_infrared_front(3)-'0';
	
	Sensor_state=sensor_front[0]*8+sensor_front[1]*4+sensor_front[2]*2+sensor_front[3];
	
	switch(Sensor_state)
	{
		case 0x6:
			error_front=0;//中线 (0110)
			break;
		case 0x4:
			error_front=-1;//微偏右 (0100)
			break;
		case 0xC:
			error_front=-2;//很偏右 (1100)
			break;
		case 0x8:
			error_front=-3;//严重偏右 (1000)
			break;
		case 0xE:
			error_front=-4;//左转大弯 (1110)
			break;
		case 0x2:
			error_front=1;//微偏左 (0010)
			break;
		case 0x3:
			error_front=2;//很偏左 (0011)
			break;
		case 0x1:
			error_front=3;//严重偏左 (0001)
			break;
		case 0x7:
			error_front=4;//右转大弯 (0111)
			break;
		case 0xF:
			error_front=5;//(1111)
			break;
		case 0x0:
			error_front=6;//(0000)
			break;
	}
}
