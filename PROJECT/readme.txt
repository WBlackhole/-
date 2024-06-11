硬件接口

电机部分（A轮-左前 B轮-右前 C轮-左后 D轮-右后）
驱动引脚：驱动板-主控板
A轮（M2） IN1-PD1 IN2-PD0
B轮（M1） IN1-PD2 IN2-PD3
C轮（M3） IN1-PD5 IN2-PD4
D轮（M4） IN1-PD6 IN2-PD7

控制引脚：驱动板-主控板
A轮（M2） P2-PC6
B轮（M1） P1-PC7
C轮（M3） P3-PC8
D轮（M4） P4-PC9

编码器引脚（暂时不接）：
PD12-PD15（左前 右前 左后 右后）

灰度传感器部分（前五路、后五路、右两路）
前四路：传感器-主控板
SDA-PF0 SCL-PF1

后四路：传感器-主控板
SDA-PF  SCL-PF

右两路：传感器-主控板
DO-PD11 DO-PC13（前->后）
 
机械臂部分（五个）
串口部分：主控板-舵机驱动板
PA2-RX PA3-TX

陀螺仪
陀螺仪-主控板
SCL-PB10
SDA-PB11

蜂鸣器
蜂鸣器-主控板
输出-PD10

K210：
PA9 PA10

