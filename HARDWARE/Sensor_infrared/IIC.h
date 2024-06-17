#ifndef __IIC_H
#define __IIC_H


#define    IIC_SDA_Front      	GPIO_Pin_0  //SDA的IO口
#define    IIC_SCL_Front      	GPIO_Pin_1  //SCL的IO口
#define    IIC_SDA_Behind       GPIO_Pin_2  //SDA的IO口
#define    IIC_SCL_Behind      	GPIO_Pin_3  //SCL的IO口
#define    GPIOX           	  	GPIOF      //GPIOx选择
#define    CLOCK		   	  	RCC_APB2Periph_GPIOF //时钟信号
 
#define    IIC_Front_SCL        PFout(1) //SCL
#define    IIC_Front_SDA        PFout(0) //输出SDA
#define    READ_Front_SDA       PFin(0)  //输入SDA
#define    IIC_Behind_SCL       PFout(3) //SCL
#define    IIC_Behind_SDA       PFout(2) //输出SDA
#define    READ_Behind_SDA      PFin(2)  //输入SDA

void IIC_init(void);

void I2C_SDA_OUT_Front(void);
void I2C_SDA_IN_Front(void);
void IIC_start_Front(void);
void IIC_stop_Front(void);
void IIC_ack_Front(void);
void IIC_noack_Front(void);
char IIC_wait_ack_Front(void);
void IIC_send_byte_Front(char txd);
char IIC_read_byte_Front(char ack);

void I2C_SDA_OUT_Behind(void);
void I2C_SDA_IN_Behind(void);
void IIC_start_Behind(void);
void IIC_stop_Behind(void);
void IIC_ack_Behind(void);
void IIC_noack_Behind(void);
char IIC_wait_ack_Behind(void);
void IIC_send_byte_Behind(char txd);
char IIC_read_byte_Behind(char ack);
#endif

