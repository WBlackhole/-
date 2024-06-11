#include "sensor_infrared.h"
#include "main.h"

#define IIC_ADDR 0x78
#define VAL_ADDR 0x80
#define Read_Free 0
#define Read_Count 1


int error_front,error_behind;       		//小车位置偏差误差值
char sensor_front[4];
char sensor_behind[4];
char sensor_right[2];   	//储存前五路红外传感器返回的值
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


void read_infrared_behind(void)
{
	static char Sensor_state;
	u8 val;
	IIC_start_Behind(); //启动
	IIC_send_byte_Behind(IIC_ADDR << 1); //发送写指令
	IIC_send_byte_Behind(VAL_ADDR); //寄存器地址
	IIC_wait_ack_Behind(); //应答
	IIC_stop_Behind(); //停止
	IIC_start_Behind(); //重新启动
	IIC_send_byte_Behind((IIC_ADDR << 1) | 0x01); //发送读指令
	IIC_wait_ack_Behind(); //应答
	val = IIC_read_byte_Behind(0); //读取一个字节
	IIC_stop_Behind(); //停止

    b[0]=((val>>0) & 0x01)+0x30; //最左的传感器
    b[1]=((val>>1) & 0x01)+0x30;
    b[2]=((val>>2) & 0x01)+0x30;
    b[3]=((val>>3) & 0x01)+0x30;

    sensor_behind[0]=Read_infrared_behind(0)-'0'; //最左的传感器
    sensor_behind[1]=Read_infrared_behind(1)-'0';
    sensor_behind[2]=Read_infrared_behind(2)-'0';
    sensor_behind[3]=Read_infrared_behind(3)-'0';
	
	Sensor_state=sensor_behind[0]*8+sensor_behind[1]*4+sensor_behind[2]*2+sensor_behind[3];
	
	switch(Sensor_state)
	{
		case 0x6:
			error_behind=0;//中线 (0110)
			break;
		case 0x4:
			error_behind=-1;//微偏右 (0100)
			break;
		case 0xC:
			error_behind=-2;//很偏右 (1100)
			break;
		case 0x8:
			error_behind=-3;//严重偏右 (1000)
			break;
		case 0xE:
			error_behind=-4;//左转大弯 (1110)
			break;
		case 0x2:
			error_behind=1;//微偏左 (0010)
			break;
		case 0x3:
			error_behind=2;//很偏左 (0011)
			break;
		case 0x1:
			error_behind=3;//严重偏左 (0001)
			break;
		case 0x7:
			error_behind=4;//右转大弯 (0111)
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
    sensor_right[0]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11);//右侧上传感器
    sensor_right[1]=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);//右侧下传感器
}

//状态机编程-毛刺滤波状态机
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
		State_front[i]=Read_Count;//状态迁移
		temp_a[i]=a[i];//记录传感器值跳变值
	}
	else
	{
		Last_a[i]=a[i];//记录为过去值
	}
	return Last_a[i];
}

char Read_Count_Handle_front(char i)
{
	if(a[i]==temp_a[i])//持续等于跳变值
	{
		cnt_a[i]++;
	}
	else//再次发生跳变
	{
		cnt_a[i]=0;
		temp_a[i]=a[i];
	}
	
	if(cnt_a[i]>1)//跳变值有效
	{
		State_front[i]=Read_Free;
		cnt_a[i]=0;
		Last_a[i]=temp_a[i];
		return temp_a[i];
	}
	else//无效
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
		State_behind[i]=Read_Count;//状态迁移
		temp_b[i]=b[i];//记录传感器值跳变值
	}
	else
	{
		Last_b[i]=b[i];//记录为过去值
	}
	return Last_b[i];
}

char Read_Count_Handle_behind(char i)
{
	if(b[i]==temp_b[i])//持续等于跳变值
	{
		cnt_b[i]++;
	}
	else//再次发生跳变
	{
		cnt_b[i]=0;
		temp_b[i]=b[i];
	}
	
	if(cnt_b[i]>1)//跳变值有效
	{
		State_behind[i]=Read_Free;
		cnt_b[i]=0;
		Last_b[i]=temp_b[i];
		return temp_b[i];
	}
	else//无效
	{
		return Last_b[i];
	}
}
