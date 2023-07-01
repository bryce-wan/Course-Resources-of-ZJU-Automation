#include "key.h"
#include "SysTick.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; // 定义结构体变量
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = (KEY1_Pin | KEY2_Pin | KEY5_Pin);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY_Port, &GPIO_InitStructure);
}

u8 KEY_Scan(u8 mode)
{
	static u8 key = 1;
	if (key == 1 && (KEY1 == 0 || KEY2 == 0 || KEY5 == 0)) // 任意一个按键按下
	{
		delay_ms(10); // 消抖
		key = 0;
		if (KEY1 == 0)
		{
			return KEY1_VALUE;
		}
		else if (KEY2 == 0)
		{
			return KEY2_VALUE;
		}
		else if (KEY5 == 0)
		{
			return KEY5_VALUE;
		}
	}
	else if (KEY1 == 1 && KEY2 == 1 && KEY5 == 1) // 无按键按下
	{
		key = 1;
	}
	if (mode == 1) // 连续按键按下
	{
		key = 1;
	}
	return 0;
}
