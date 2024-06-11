#include "main.h"
#include "RobotArm.h"

LobotServo servos[5];

void RobotArm_init(void)
{
	uartInit(9600);
	servos[0].ID = 0;			//设置舵机ID
	servos[1].ID = 1;
	servos[2].ID = 2;
	servos[3].ID = 12;
	servos[4].ID = 13;
}

void suijiqu(void)
{
	servos[0].Position = 1500;
	servos[1].Position = 1460;
	servos[2].Position = 1585;
	servos[3].Position = 1825;
	servos[4].Position = 1190;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1500;
	servos[1].Position = 1460;
	servos[2].Position = 1585;
	servos[3].Position = 1825;
	servos[4].Position = 1190;
	moveServosByArray(servos, 5, 150);

}


void jinchuyuanzhu6kuang1(void)
{
	servos[0].Position = 1500;
	servos[1].Position = 1465;
	servos[2].Position = 1320;
	servos[3].Position = 1345;
	servos[4].Position = 880;
	moveServosByArray(servos, 5, 500);
	servos[0].Position = 1500;
	servos[1].Position = 1465;
	servos[2].Position = 1320;
	servos[3].Position = 1345;
	servos[4].Position = 880;
	moveServosByArray(servos, 5, 150);

}

void jinchuyuanzhu6kuang2(void)
{
	servos[0].Position = 1500;
	servos[1].Position = 795;
	servos[2].Position = 1320;
	servos[3].Position = 1345;
	servos[4].Position = 880;
	moveServosByArray(servos, 5, 500);
	servos[0].Position = 1500;
	servos[1].Position = 795;
	servos[2].Position = 1320;
	servos[3].Position = 1345;
	servos[4].Position = 880;
	moveServosByArray(servos, 5, 150);

}

void jinchuyuanzhu6kuang3(void)
{
	servos[0].Position = 1500;
	servos[1].Position = 795;
	servos[2].Position = 1320;
	servos[3].Position = 1345;
	servos[4].Position = 1170;
	moveServosByArray(servos, 5, 500);
	servos[0].Position = 1500;
	servos[1].Position = 795;
	servos[2].Position = 1320;
	servos[3].Position = 1345;
	servos[4].Position = 1170;
	moveServosByArray(servos, 5, 150);

}

void jinchuyuanzhu6kuang4(void)
{
	servos[0].Position = 1500;
	servos[1].Position = 775;
	servos[2].Position = 640;
	servos[3].Position = 1220;
	servos[4].Position = 1170;
	moveServosByArray(servos, 5, 500);
	servos[0].Position = 1500;
	servos[1].Position = 775;
	servos[2].Position = 640;
	servos[3].Position = 1220;
	servos[4].Position = 1170;
	moveServosByArray(servos, 5, 150);

}

void jinchuyuanzhu6kuang5(void)
{
	servos[0].Position = 1780;
	servos[1].Position = 775;
	servos[2].Position = 640;
	servos[3].Position = 1220;
	servos[4].Position = 1170;
	moveServosByArray(servos, 5, 500);
	servos[0].Position = 1780;
	servos[1].Position = 775;
	servos[2].Position = 640;
	servos[3].Position = 1220;
	servos[4].Position = 1170;
	moveServosByArray(servos, 5, 150);

}

void jinchuyuanzhu6kuang6(void)
{
	servos[0].Position = 1780;
	servos[1].Position = 770;
	servos[2].Position = 1020;
	servos[3].Position = 1220;
	servos[4].Position = 1420;
	moveServosByArray(servos, 5, 500);
	servos[0].Position = 1780;
	servos[1].Position = 770;
	servos[2].Position = 1020;
	servos[3].Position = 1220;
	servos[4].Position = 1420;
	moveServosByArray(servos, 5, 150);

}

void jinchuyuanzhu6kuang7(void)
{
	servos[0].Position = 1780;
	servos[1].Position = 1290;
	servos[2].Position = 1055;
	servos[3].Position = 1220;
	servos[4].Position = 1420;
	moveServosByArray(servos, 5, 500);
	servos[0].Position = 1780;
	servos[1].Position = 1290;
	servos[2].Position = 1055;
	servos[3].Position = 1220;
	servos[4].Position = 1420;
	moveServosByArray(servos, 5, 150);

}

void jinchuyuanzhu6kuang8(void)
{
	servos[0].Position = 1780;
	servos[1].Position = 1690;
	servos[2].Position = 1250;
	servos[3].Position = 1280;
	servos[4].Position = 1035;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1780;
	servos[1].Position = 1690;
	servos[2].Position = 1250;
	servos[3].Position = 1280;
	servos[4].Position = 1035;
	moveServosByArray(servos, 5, 150);

}

void jinchuyuanzhu6kuang9(void)
{
	servos[0].Position = 1500;
	servos[1].Position = 1690;
	servos[2].Position = 1250;
	servos[3].Position = 1280;
	servos[4].Position = 1035;
	moveServosByArray(servos, 5, 200);
	servos[0].Position = 1500;
	servos[1].Position = 1690;
	servos[2].Position = 1250;
	servos[3].Position = 1280;
	servos[4].Position = 1035;
	moveServosByArray(servos, 5, 150);

}

// 圆柱-正方形3号框
void y3z_1(void)
{
	servos[0].Position = 1500;
	servos[1].Position = 1520;
	servos[2].Position = 1620;
	servos[3].Position = 2010;
	servos[4].Position = 1500;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1500;
	servos[1].Position = 1520;
	servos[2].Position = 1620;
	servos[3].Position = 2010;
	servos[4].Position = 1500;
	moveServosByArray(servos, 5, 150);

}

void y3z_2(void)
{
	servos[0].Position = 1500;
	servos[1].Position = 1520;
	servos[2].Position = 1620;
	servos[3].Position = 1670;
	servos[4].Position = 1500;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1500;
	servos[1].Position = 1520;
	servos[2].Position = 1620;
	servos[3].Position = 1670;
	servos[4].Position = 1500;
	moveServosByArray(servos, 5, 150);
}
void y3z(void)
{
	servos[0].Position = 1500;
	servos[1].Position = 835;
	servos[2].Position = 1620;
	servos[3].Position = 1670;
	servos[4].Position = 1500;
	moveServosByArray(servos, 5, 600);
	servos[0].Position = 1500;
	servos[1].Position = 835;
	servos[2].Position = 1620;
	servos[3].Position = 1670;
	servos[4].Position = 1500;
	moveServosByArray(servos, 5, 150);
}

void y3z_4(void)
{
	servos[0].Position = 1500;
	servos[1].Position = 835;
	servos[2].Position = 950;
	servos[3].Position = 1445;
	servos[4].Position = 1500;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1500;
	servos[1].Position = 835;
	servos[2].Position = 950;
	servos[3].Position = 1445;
	servos[4].Position = 1500;
	moveServosByArray(servos, 5, 150);
}


void y3z_5(void)
{
	servos[0].Position = 1500;
	servos[1].Position = 835;
	servos[2].Position = 660;
	servos[3].Position = 1250;
	servos[4].Position = 1375;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1500;
	servos[1].Position = 835;
	servos[2].Position = 660;
	servos[3].Position = 1250;
	servos[4].Position = 1375;
	moveServosByArray(servos, 5, 150);
}
//
void y3z_6(void)
{
	servos[0].Position = 1500;
	servos[1].Position = 835;
	servos[2].Position = 625;
	servos[3].Position = 1250;
	servos[4].Position = 1315;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1500;
	servos[1].Position = 835;
	servos[2].Position = 625;
	servos[3].Position = 1250;
	servos[4].Position = 1315;	
	moveServosByArray(servos, 5, 150);
}


void y3z_7(void)
{
	servos[0].Position = 1850;
	servos[1].Position = 835;
	servos[2].Position = 640;
	servos[3].Position = 1250;
	servos[4].Position = 1375;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1850;
	servos[1].Position = 835;
	servos[2].Position = 640;
	servos[3].Position = 1250;
	servos[4].Position = 1375;	
	moveServosByArray(servos, 5, 150);
}


void y3z_8(void)
{
	servos[0].Position = 1850;
	servos[1].Position = 835;
	servos[2].Position = 1365;
	servos[3].Position = 1250;
	servos[4].Position = 1375;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1850;
	servos[1].Position = 835;
	servos[2].Position = 1365;
	servos[3].Position = 1250;
	servos[4].Position = 1375;	
	moveServosByArray(servos, 5, 150);
}


//moveServo(2,1220,500);
//moveServo(2,1220,100);
void y3z_9(void)
{
	servos[0].Position = 1850;
	servos[1].Position = 1235;
	servos[2].Position = 1365;
	servos[3].Position = 1250;
	servos[4].Position = 1375;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1850;
	servos[1].Position = 1235;
	servos[2].Position = 1365;
	servos[3].Position = 1250;
	servos[4].Position = 1375;
	moveServosByArray(servos, 5, 150);
}
void y3z_10(void)
{
	servos[0].Position = 1850;
	servos[1].Position = 1225;
	servos[2].Position = 1390;
	servos[3].Position = 1510;
	servos[4].Position = 1745;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1850;
	servos[1].Position = 1225;
	servos[2].Position = 1390;
	servos[3].Position = 1510;
	servos[4].Position = 1745;
	moveServosByArray(servos, 5, 150);
}


void y3z_11(void)
{
	servos[0].Position = 1500;
	servos[1].Position = 1225;
	servos[2].Position = 1390;
	servos[3].Position = 1510;
	servos[4].Position = 1745;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1500;
	servos[1].Position = 1225;
	servos[2].Position = 1390;
	servos[3].Position = 1510;
	servos[4].Position = 1745;
	moveServosByArray(servos, 5,150);
}
void y3z_12(void)
{
	servos[0].Position = 1500;
	servos[1].Position = 1225;
	servos[2].Position = 1390;
	servos[3].Position = 1510;
	servos[4].Position = 1400;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1500;
	servos[1].Position = 1225;
	servos[2].Position = 1390;
	servos[3].Position = 1510;
	servos[4].Position = 1400;
	moveServosByArray(servos, 5,150);
}



// 正方形6号框两个
void capture_8(void)
{
	servos[0].Position = 1555;
	servos[1].Position = 870;
	servos[2].Position = 1105;
	servos[3].Position = 905;
	servos[4].Position = 2205;
	moveServosByArray(servos, 5, 600);
	servos[0].Position = 1555;
	servos[1].Position = 870;
	servos[2].Position = 1105;
	servos[3].Position = 905;
	servos[4].Position = 2205;
	moveServosByArray(servos, 5, 200);
}

void capture_far(void)
{
	servos[0].Position = 1555;
	servos[1].Position = 870;
	servos[2].Position = 2250;
	servos[3].Position = 1615;
	servos[4].Position = 1645;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1555;
	servos[1].Position = 870;
	servos[2].Position = 2250;
	servos[3].Position = 1615;
	servos[4].Position = 1645;	
	moveServosByArray(servos, 5, 200);
}
void capture_9(void)
{
	servos[0].Position = 1910;
	servos[1].Position = 870;
	servos[2].Position = 2250;
	servos[3].Position = 1615;
	servos[4].Position = 1680;
	moveServosByArray(servos, 5, 300);
	servos[0].Position = 1910;
	servos[1].Position = 870;
	servos[2].Position = 2250;
	servos[3].Position = 1615;
	servos[4].Position = 1680;	
	moveServosByArray(servos, 5, 100);
}

void capture_raise_big_1(void)
{
	servos[0].Position = 1910;
	servos[1].Position = 870;
	servos[2].Position = 1055;
	servos[3].Position = 900;
	servos[4].Position = 1680;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1910;
	servos[1].Position = 870;
	servos[2].Position = 1055;
	servos[3].Position = 900;
	servos[4].Position = 1680;	
	moveServosByArray(servos, 5, 200);
}

void capture_raise_big_2(void)
{
	servos[0].Position = 1910;
	servos[1].Position = 870;
	servos[2].Position = 1055;
	servos[3].Position = 900;
	servos[4].Position = 2150;
	moveServosByArray(servos, 5, 500);
	servos[0].Position = 1910;
	servos[1].Position = 870;
	servos[2].Position = 1055;
	servos[3].Position = 900;
	servos[4].Position = 2150;	
	moveServosByArray(servos, 5, 200);
}
//moveServo(1,1760,500);
//moveServo(1,1760,200);
void capture_10(void)
{
	servos[0].Position = 1910;
	servos[1].Position = 1760;
	servos[2].Position = 1155;
	servos[3].Position = 900;
	servos[4].Position = 2150;
	moveServosByArray(servos, 5, 500);
	servos[0].Position = 1910;
	servos[1].Position = 1760;
	servos[2].Position = 1155;
	servos[3].Position = 900;
	servos[4].Position = 2150;	
	moveServosByArray(servos, 5, 200);
}

void capture_10_2(void)
{
	servos[0].Position = 1910;
	servos[1].Position = 1760;
	servos[2].Position = 1055;
	servos[3].Position = 900;
	servos[4].Position = 2250;
	moveServosByArray(servos, 5, 500);
	servos[0].Position = 1910;
	servos[1].Position = 1760;
	servos[2].Position = 1055;
	servos[3].Position = 900;
	servos[4].Position = 2250;	
	moveServosByArray(servos, 5, 200);
}

//moveServo(0,1555,200);
//moveServo(0,1555,100);
void capture_11(void)
{
	servos[0].Position = 1555;
	servos[1].Position = 1770;
	servos[2].Position = 1055;
	servos[3].Position = 900;
	servos[4].Position = 2250;
	moveServosByArray(servos, 5, 200);
	servos[0].Position = 1555;
	servos[1].Position = 1770;
	servos[2].Position = 1055;
	servos[3].Position = 900;
	servos[4].Position = 2250;	
	moveServosByArray(servos, 5, 100);
}

//moveServo(1,870,600);
//moveServo(1,870,200);
void capture_12(void)
{
	servos[0].Position = 1555;
	servos[1].Position = 870;
	servos[2].Position = 1055;
	servos[3].Position = 900;
	servos[4].Position = 2150;
	moveServosByArray(servos, 5, 600);
	servos[0].Position = 1555;
	servos[1].Position = 870;
	servos[2].Position = 1055;
	servos[3].Position = 900;
	servos[4].Position = 2150;	
	moveServosByArray(servos, 5, 200);
}

//void capture_close(void);

//moveServo(0,1910,300);
//moveServo(0,1910,100);
void capture_13(void)
{
	servos[0].Position = 1555;
	servos[1].Position = 2125;
	servos[2].Position = 1060;
	servos[3].Position = 865;
	servos[4].Position = 1500;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1555;
	servos[1].Position = 2125;
	servos[2].Position = 1060;
	servos[3].Position = 865;
	servos[4].Position = 1500;	
	moveServosByArray(servos, 5, 200);
}

//void capture_raise_big(void);

//moveServo(1,1775,1000);
//moveServo(1,1775,1000);
void capture_14(void)
{
	servos[0].Position = 1555;
	servos[1].Position = 2200;
	servos[2].Position = 1060;
	servos[3].Position = 865;
	servos[4].Position = 1500;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1555;
	servos[1].Position = 2200;
	servos[2].Position = 1060;
	servos[3].Position = 865;
	servos[4].Position = 1500;	
	moveServosByArray(servos, 5, 200);
}

//moveServo(0,1555,200);
//moveServo(0,1555,100);
void capture_15(void)
{
	servos[0].Position = 1555;
	servos[1].Position = 1770;
	servos[2].Position = 1055;
	servos[3].Position = 900;
	servos[4].Position = 2150;
	moveServosByArray(servos, 5, 200);
	servos[0].Position = 1555;
	servos[1].Position = 1770;
	servos[2].Position = 1055;
	servos[3].Position = 900;
	servos[4].Position = 2150;	
	moveServosByArray(servos, 5, 100);
}

//
void capture_double_1(void)
{
	servos[0].Position = 1555;
	servos[1].Position = 1770;
	servos[2].Position = 1055;
	servos[3].Position = 1100;
	servos[4].Position = 2390;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1555;
	servos[1].Position = 1770;
	servos[2].Position = 1055;
	servos[3].Position = 1100;
	servos[4].Position = 2390;	
	moveServosByArray(servos, 5, 200);

}
void capture_double_2(void)
{
	servos[0].Position = 1555;
	servos[1].Position = 1770;
	servos[2].Position = 1300;
	servos[3].Position = 900;
	servos[4].Position = 2380;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1555;
	servos[1].Position = 1770;
	servos[2].Position = 1300;
	servos[3].Position = 900;
	servos[4].Position = 2380;	
	moveServosByArray(servos, 5, 200);

}

//moveServo(0,1900,200);
//moveServo(0,1900,100);
void capture_16(void)
{
	servos[0].Position = 1910;
	servos[1].Position = 1770;
	servos[2].Position = 1300;
	servos[3].Position = 750;
	servos[4].Position = 2380;
	moveServosByArray(servos, 5, 200);
	servos[0].Position = 1910;
	servos[1].Position = 1770;
	servos[2].Position = 1300;
	servos[3].Position = 750;
	servos[4].Position = 2380;	
	moveServosByArray(servos, 5, 100);
}

//
void capture_double_get(void)
{
	servos[0].Position = 1910;
	servos[1].Position = 1770;
	servos[2].Position = 1330;
	servos[3].Position = 1240;
	servos[4].Position = 2295;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1910;
	servos[1].Position = 1770;
	servos[2].Position = 1330;
	servos[3].Position = 1240;
	servos[4].Position = 2295;	
	moveServosByArray(servos, 5, 200);
}

//moveServo(2,1250,500);
//moveServo(2,1250,100);
void capture_17(void)
{
	servos[0].Position = 1910;
	servos[1].Position = 1770;
	servos[2].Position = 1200;
	servos[3].Position = 1240;
	servos[4].Position = 2295;
	moveServosByArray(servos, 5, 500);
	servos[0].Position = 1910;
	servos[1].Position = 1770;
	servos[2].Position = 1200;
	servos[3].Position = 1240;
	servos[4].Position = 2295;	
	moveServosByArray(servos, 5, 100);
}

//moveServo(1,2125,500);
//moveServo(1,2125,100);
void capture_18(void)
{
	servos[0].Position = 1910;
	servos[1].Position = 2125;
	servos[2].Position = 1200;
	servos[3].Position = 1240;
	servos[4].Position = 2295;
	moveServosByArray(servos, 5, 500);
	servos[0].Position = 1910;
	servos[1].Position = 2125;
	servos[2].Position = 1200;
	servos[3].Position = 1240;
	servos[4].Position = 2295;	
	moveServosByArray(servos, 5, 100);
}

//
void capture_right_place(void)
{
	servos[0].Position = 1910;
	servos[1].Position = 2125;
	servos[2].Position = 2170;
	servos[3].Position = 1735;
	servos[4].Position = 1900;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1910;
	servos[1].Position = 2125;
	servos[2].Position = 2170;
	servos[3].Position = 1735;
	servos[4].Position = 1900;	
	moveServosByArray(servos, 5, 200);
}

//moveServo(0,1555,200);
//moveServo(0,1555,100);
void capture_19(void)
{
	servos[0].Position = 1555;
	servos[1].Position = 2125;
	servos[2].Position = 2170;
	servos[3].Position = 1735;
	servos[4].Position = 1900;
	moveServosByArray(servos, 5, 200);
	servos[0].Position = 1555;
	servos[1].Position = 2125;
	servos[2].Position = 2170;
	servos[3].Position = 1735;
	servos[4].Position = 1900;
	moveServosByArray(servos, 5, 100);
}

//
void capture_raise(void)
{
	servos[0].Position = 1555;
	servos[1].Position = 2125;
	servos[2].Position = 1060;
	servos[3].Position = 865;
	servos[4].Position = 2060;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1555;
	servos[1].Position = 2125;
	servos[2].Position = 1060;
	servos[3].Position = 865;
	servos[4].Position = 2060;	
	moveServosByArray(servos, 5, 200);
}


//moveServo(1,1280,500);
//moveServo(1,1280,100);
void capture_20(void)
{
	servos[0].Position = 1555;
	servos[1].Position = 1280;
	servos[2].Position = 1060;
	servos[3].Position = 865;
	servos[4].Position = 2160;
	moveServosByArray(servos, 5, 500);
	servos[0].Position = 1555;
	servos[1].Position = 1280;
	servos[2].Position = 1060;
	servos[3].Position = 865;
	servos[4].Position = 2160;	
	moveServosByArray(servos, 5, 100);
}

//moveServo(0,1850,200);
//moveServo(0,1850,100);
void capture_21(void)
{
	servos[0].Position = 1555;
	servos[1].Position = 1280;
	servos[2].Position = 1060;
	servos[3].Position = 865;
	servos[4].Position = 2160;
	moveServosByArray(servos, 5, 200);
	servos[0].Position = 1555;
	servos[1].Position = 1280;
	servos[2].Position = 1060;
	servos[3].Position = 865;
	servos[4].Position = 2160;	
	moveServosByArray(servos, 5, 100);
}

//
void capture_grab(void)
{
	servos[0].Position = 1555;
	servos[1].Position = 1280;
	servos[2].Position = 1330;
	servos[3].Position = 935;
	servos[4].Position = 2215;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1555;
	servos[1].Position = 1280;
	servos[2].Position = 1330;
	servos[3].Position = 935;
	servos[4].Position = 2215;	
	moveServosByArray(servos, 5, 200);
}

//moveServo(0,2060,500);
//moveServo(0,2060,100);
void capture_22(void)
{
	servos[0].Position = 1900;
	servos[1].Position = 1280;
	servos[2].Position = 1330;
	servos[3].Position = 935;
	servos[4].Position = 2215;
	moveServosByArray(servos, 5, 500);
	servos[0].Position = 1900;
	servos[1].Position = 1280;
	servos[2].Position = 1330;
	servos[3].Position = 935;
	servos[4].Position = 2215;	
	moveServosByArray(servos, 5, 100);
}

void capture_raise_other(void)
{
	servos[0].Position = 1900;
	servos[1].Position = 1280;
	servos[2].Position = 1250;
	servos[3].Position = 1240;
	servos[4].Position = 2295;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1900;
	servos[1].Position = 1280;
	servos[2].Position = 1250;
	servos[3].Position = 1240;
	servos[4].Position = 2295;	
	moveServosByArray(servos, 5, 200);
}

//moveServo(1,2200,600);
//moveServo(1,2200,200);
void capture_23(void)
{
	servos[0].Position = 1900;
	servos[1].Position = 2200;
	servos[2].Position = 1250;
	servos[3].Position = 1240;
	servos[4].Position = 2295;
	moveServosByArray(servos, 5, 600);
	servos[0].Position = 1900;
	servos[1].Position = 2200;
	servos[2].Position = 1250;
	servos[3].Position = 1240;
	servos[4].Position = 2295;	
	moveServosByArray(servos, 5, 200);
}

void capture_left_place(void)
{
	servos[0].Position = 1900;
	servos[1].Position = 2200;
	servos[2].Position = 2385;
	servos[3].Position = 2010;
	servos[4].Position = 1805;
	moveServosByArray(servos, 5, 1000);
	servos[0].Position = 1900;
	servos[1].Position = 2200;
	servos[2].Position = 2385;
	servos[3].Position = 2010;
	servos[4].Position = 1805;	
	moveServosByArray(servos, 5, 200);
}

//moveServo(0,1555,200);
//moveServo(0,1555,100);
void capture_24(void)
{
	servos[0].Position = 1555;
	servos[1].Position = 2200;
	servos[2].Position = 2385;
	servos[3].Position = 2010;
	servos[4].Position = 1805;
	moveServosByArray(servos, 5, 200);
	servos[0].Position = 1555;
	servos[1].Position = 2200;
	servos[2].Position = 2385;
	servos[3].Position = 2010;
	servos[4].Position = 1805;	
	moveServosByArray(servos, 5, 100);
}

//void capture_raise(void);



