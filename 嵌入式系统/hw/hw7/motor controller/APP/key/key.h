#ifndef _key_H
#define _key_H

#include "system.h"

#define KEY1_Pin GPIO_Pin_0
#define KEY2_Pin GPIO_Pin_1
#define KEY3_Pin GPIO_Pin_2
#define KEY4_Pin GPIO_Pin_3
#define KEY5_Pin GPIO_Pin_4
#define KEY6_Pin GPIO_Pin_5
#define KEY7_Pin GPIO_Pin_6
#define KEY8_Pin GPIO_Pin_7

#define KEY_Port (GPIOB)

#define KEY1 PBin(0)
#define KEY2 PBin(1)
#define KEY3 PBin(2)
#define KEY4 PBin(3)
#define KEY5 PBin(4)
#define KEY6 PBin(5)
#define KEY7 PBin(6)
#define KEY8 PBin(7)

#define KEY1_VALUE 1
#define KEY2_VALUE 2
#define KEY3_VALUE 3
#define KEY4_VALUE 4
#define KEY5_VALUE 5
#define KEY6_VALUE 6
#define KEY7_VALUE 7
#define KEY8_VALUE 8

void KEY_Init(void);
u8 KEY_Scan(u8 mode);
#endif
