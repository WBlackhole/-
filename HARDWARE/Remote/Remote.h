#ifndef __REMOTE_H
#define __REMOTE_H
 
//ºìÍâ°´¼ü¼üÂë
#define IR_0			0x19
#define IR_1			0x45
#define IR_2			0x46
#define IR_3			0x47
#define IR_4			0x44
#define IR_5			0x40
#define IR_6			0x43
#define IR_7			0x07
#define IR_8			0x15
#define IR_9			0x09
 
void Remote_Init(void);
uint32_t IC_GetFreq(void);
uint8_t IR_GetDataFlag(void);
uint8_t IR_GetRepeatFlag(void);

uint8_t IR_GetAddress(void);
uint8_t IR_GetCommand(void);
 
#endif
