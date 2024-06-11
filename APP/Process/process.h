#ifndef __PROCESS_H
#define __PROCESS_H


#define All_Black 5		//前传感器扫描为全黑 值修改意见：无需进行任何修改！
#define All_White 6		//前传感器扫描为全黑 值修改意见：无需进行任何修改！	



extern char sensor_front[4],sensor_behind[4],sensor_right[2];
extern int error_front,error_behind;
extern float pitch,roll,yaw;
extern int Basic_BSpeed,Basic_FSpeed;
extern int fk,yt,yz;

void Move_1(void);
void Move_2(void);
void Move_3(void);
void Move_4(void);
void Move_5(void);
void Move_2_B(void);
void Move_3_B(void);
void Move_4_B(void);

void Sight_FK(void);
void Sight_YT(void);
void Sight_YZ(void);
void AFK_BYT_CYZ(void);
void AFK_BYZ_CYT(void);
void AYT_BFK_CYZ(void);
void AYT_BYZ_CFK(void);
void AYZ_BFK_CYT(void);
void AYZ_BYT_CFK(void);

#endif
