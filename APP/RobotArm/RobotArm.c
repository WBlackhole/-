#include "main.h"
#include "RobotArm.h"

LobotServo servos[5];

void RobotArm_init(void)
{
	uartInit(9600);
	servos[0].ID = 0;			//…Ë÷√∂Êª˙ID
	servos[1].ID = 1;
	servos[2].ID = 2;
	servos[3].ID = 12;
	servos[4].ID = 13;
}

