#include "reg51.h" //此文件中定义了单片机的一些特殊功能寄存器
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;
enum Mode
{
	CONFIRMED,
	MODIFY
} mode = CONFIRMED;
u8 isRunning = 0;

#define GPIO_DIG P1
#define GPIO_KEY P2
sbit LSA = P0 ^ 0;
sbit LSB = P0 ^ 1;
sbit LSC = P0 ^ 2;

u8 bit_change = 0;
u8 KeyValue;
u8 KeyState;
u8 code smgduan[20] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, // 0-9,A,b,C,d,E,F,H,P,U,blank
					   0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x76, 0x73, 0x3e, 0x00};

u8 Data[8] = {0, 2, 0, 19, 0, 0, 0, 0};								  // 前三位温度，后四位时间
u8 DisplayData[8] = {0x3f, 0x5b, 0x3f, 0x00, 0x3f, 0x3f, 0x3f, 0x3f}; // 020 0000
u8 num = 0;
void Delay(u16 i)
{
	while (i--)
		;
}
void Delay10ms(void) // 误差 0us
{
	unsigned char a, b, c;
	for (c = 1; c > 0; c--)
		for (b = 38; b > 0; b--)
			for (a = 130; a > 0; a--)
				;
}
/*******************************************************************************
 * 函 数 名			: Timer0Init
 * 函数功能			: 定时器0初始化，10ms定时
 *******************************************************************************/
void Timer0Init()
{
	TMOD |= 0X01; // 选择为定时器0模式，工作方式1，仅用TR0打开启动。
	TH0 = 0Xd8;	  // 给定时器赋初值，定时10ms
	TL0 = 0Xf0;
	ET0 = 1; // 打开定时器0中断允许
	EA = 1;	 // 打开总中断
	TR0 = 1; // 打开定时器
}
void Data2Display()
{
	DisplayData[0] = smgduan[Data[0]];
	DisplayData[1] = smgduan[Data[1]];
	DisplayData[2] = smgduan[Data[2]];
	DisplayData[3] = smgduan[Data[3]];
	DisplayData[4] = smgduan[Data[4]];
	DisplayData[5] = smgduan[Data[5]] + 128;
	DisplayData[6] = smgduan[Data[6]];
	DisplayData[7] = smgduan[Data[7]];
}
/*******************************************************************************
 * 函 数 名 		: DigDisplay
 * 函数功能		   	: 数码管动态扫描函数，循环扫描8个数码管显示
 *******************************************************************************/
void DigDisplay()
{
	u8 i;
	for (i = 0; i < 8; i++)
	{
		switch (i) // 位选，选择点亮的数码管，
		{
		case (0):
			LSA = 0, LSB = 0, LSC = 0;
			break; // 显示第0位
		case (1):
			LSA = 1, LSB = 0, LSC = 0;
			break; // 显示第1位
		case (2):
			LSA = 0, LSB = 1, LSC = 0;
			break; // 显示第2位
		case (3):
			LSA = 1, LSB = 1, LSC = 0;
			break; // 显示第3位
		case (4):
			LSA = 0, LSB = 0, LSC = 1;
			break; // 显示第4位
		case (5):
			LSA = 1, LSB = 0, LSC = 1;
			break; // 显示第5位
		case (6):
			LSA = 0, LSB = 1, LSC = 1;
			break; // 显示第6位
		case (7):
			LSA = 1, LSB = 1, LSC = 1;
			break; // 显示第7位
		}
		GPIO_DIG = DisplayData[i]; // 发送段码
		Delay(100);				   // 间隔一段时间扫描
		GPIO_DIG = 0x00;		   // 消隐
	}
}
void KeyDown(void)
{
	unsigned int a = 0;
	GPIO_KEY = 0x0f;
	if (GPIO_KEY != 0x0f) // 读取按键是否按下
	{
		Delay10ms();		  // 延时10ms进行消抖
		if (GPIO_KEY != 0x0f) // 再次检测键盘是否按下
		{
			KeyState = 1; // 有按键按下
			// 测试列
			GPIO_KEY = 0X0F;
			switch (GPIO_KEY)
			{
			case (0X07):
				KeyValue = 0;
				break;
			case (0X0b):
				KeyValue = 1;
				break;
			case (0X0d):
				KeyValue = 2;
				break;
			case (0X0e):
				KeyValue = 3;
				break;
			}
			// 测试行
			GPIO_KEY = 0XF0;
			switch (GPIO_KEY)
			{
			case (0X70):
				KeyValue = KeyValue;
				break;
			case (0Xb0):
				KeyValue = KeyValue + 4;
				break;
			case (0Xd0):
				KeyValue = KeyValue + 8;
				break;
			case (0Xe0):
				KeyValue = KeyValue + 12;
				break;
			}
			// while ((a < 500) && (GPIO_KEY != 0xf0)) // 按键松手检测
			// {
			// 	Delay10ms();
			// 	a++;
			// }
			a = 0;
		}
	}
}

void datapros()
{
	u8 KeyMap[16] = {7, 8, 9, 127, 4, 5, 6, 127, 1, 2, 3, 127, 0, 127, 127, 127};
	u16 curValue = 0;
	if (GPIO_KEY == 0xf0)
		num = 0;
	switch (mode)
	{
	case CONFIRMED:
		switch (KeyValue)
		{
		case 13: // 开始
			while (GPIO_KEY != 0xf0)
				Delay10ms();
			isRunning = 1;
			break;
		case 14: // 停止
			while (GPIO_KEY != 0xf0)
				Delay10ms();
			isRunning = 0;
			break;
		case 15: // 进入修改模式
			while (GPIO_KEY != 0xf0)
				Delay10ms();
			mode = MODIFY;
			break;
		default:
			break;
		}
		break;
	case MODIFY:
		switch (KeyValue)
		{
		case 0:
		case 1:
		case 2:
		case 4:
		case 5:
		case 6:
		case 8:
		case 9:
		case 10:
		case 12: // 数字键
			while (GPIO_KEY != 0xf0)
				Delay10ms();
			if (!(bit_change == 6 && KeyMap[KeyValue] >= 6)) // 不能输入大于60的数
			{
				Data[bit_change] = KeyMap[KeyValue];
				Data2Display();
				bit_change = (bit_change + 1) % 8; // 修改标右移
				if (bit_change == 3)
					bit_change = 4;
			}
			break;
		case 3:
		case 7: // ++ / --
			num++;
			if (num == 32) // 接收num个按下信号触发一次++/--
			{
				num = 0;
				if (0 <= bit_change && bit_change <= 2) // 温度区域
				{
					curValue = Data[0] * 100 + Data[1] * 10 + Data[2];
					if (KeyValue == 3)
					{
						if (bit_change == 0 && curValue < 900)
							curValue += 100;
						if (bit_change == 1 && curValue < 990)
							curValue += 10;
						if (bit_change == 2 && curValue < 999)
							curValue += 1;
					}
					if (KeyValue == 7)
					{
						if (bit_change == 0 && curValue >= 100)
							curValue -= 100;
						if (bit_change == 1 && curValue >= 10)
							curValue -= 10;
						if (bit_change == 2 && curValue >= 1)
							curValue -= 1;
					}
					Data[0] = curValue / 100;
					Data[1] = curValue / 10 % 10;
					Data[2] = curValue % 10;
					Data2Display();
				}
				if (4 <= bit_change && bit_change <= 7) // 时间区域
				{
					curValue = (Data[4] * 10 + Data[5]) * 60 + Data[6] * 10 + Data[7];
					if (KeyValue == 3)
					{
						if (bit_change == 4 && curValue < 5400)
							curValue += 600;
						if (bit_change == 5 && curValue < 5940)
							curValue += 60;
						if (bit_change == 6 && curValue < 5990)
							curValue += 10;
						if (bit_change == 7 && curValue < 5999)
							curValue += 1;
					}
					if (KeyValue == 7)
					{
						if (bit_change == 4 && curValue >= 600)
							curValue -= 600;
						if (bit_change == 5 && curValue >= 60)
							curValue -= 60;
						if (bit_change == 6 && curValue >= 10)
							curValue -= 10;
						if (bit_change == 7 && curValue >= 1)
							curValue -= 1;
					}
					Data[4] = curValue / 600;
					Data[5] = curValue / 60 % 10;
					Data[6] = curValue / 10 % 6;
					Data[7] = curValue % 10;
					Data2Display();
				}
			}

			break;
		case 11: // RST
			while (GPIO_KEY != 0xf0)
				Delay10ms();
			Data[0] = Data[2] = Data[4] = Data[5] = Data[6] = Data[7] = 0;
			Data[1] = 2;
			Data[3] = 19;
			Data2Display();
			break;
		case 13: // 修改标左移
			while (GPIO_KEY != 0xf0)
				Delay10ms();
			Data2Display();
			bit_change = (bit_change - 1 + 8) % 8;
			if (bit_change == 3)
				bit_change = 2;
			break;
		case 14: // 修改标右移
			while (GPIO_KEY != 0xf0)
				Delay10ms();
			Data2Display();
			bit_change = (bit_change + 1) % 8;
			if (bit_change == 3)
				bit_change = 4;
			break;
		case 15: // 退出修改模式
			while (GPIO_KEY != 0xf0)
				Delay10ms();
			curValue = Data[0] * 100 + Data[1] * 10 + Data[2];
			if (curValue > 250)
				curValue = 250;
			Data[0] = curValue / 100;
			Data[1] = curValue / 10 % 10;
			Data[2] = curValue % 10;
			Data2Display();
			mode = CONFIRMED;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
void main()
{
	KeyState = 0;
	Timer0Init();
	while (1)
	{
		KeyDown();
		if (KeyState == 1)
		{
			datapros();
			KeyState = 0;
		}
		DigDisplay(); // 数码管显示函数
	}
}
u8 sec_10ms = 0;
u8 sec = 0;
void Timer0() interrupt 1
{
	static u16 i;
	static u16 curValue;
	TH0 = 0Xd8; // 给定时器赋初值，定时10ms
	TL0 = 0Xf0;
	if (mode == MODIFY)
		i++;
	if (i == 64)
	{
		Data2Display();
		DisplayData[bit_change] = 0x00;
	}
	if (i == 128)
	{
		i = 0;
		Data2Display();
	}
	if (isRunning)
	{
		sec_10ms++;
		if (sec_10ms == 100)
		{
			sec_10ms = 0;
			// sec++;
			// if (sec == 60)
			// {
			// 	sec = 0;
			curValue = (Data[4] * 10 + Data[5]) * 60 + Data[6] * 10 + Data[7];
			curValue--;
			Data[4] = curValue / 600;
			Data[5] = curValue / 60 % 10;
			Data[6] = curValue / 10 % 6;
			Data[7] = curValue % 10;
			Data2Display();
			if (curValue == 0)
			{
				isRunning = 0;
			}
			// }
		}
	}
}