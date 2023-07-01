#include "reg52.h"
#include <intrins.h>
#define num_mode 0
#define time_mode 1

typedef unsigned int u16;
typedef unsigned char u8;

u8 code smgduan[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                       0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71}; // 显示0~F的值
n8 mode = 0;
int KeyValue[4] = {3, 0, 2, 0};
int KeyTime[7] = {6, 0, 0, 0, 0, 0, 0};

void Delay(u16 i)
{
    while (i--)
        ;
}

void KeyDown(void)
{
    // u16 keyboard[4][4] = {{7, 8, 9, 14},
    //                       {4, 5, 6, 13},
    //                       {1, 2, 3, 12},
    //                       {10, 0, 11, 15}};

    u16 keyboard[4][4] = {{7, 8, 9, 14},
                          {4, 5, 6, 13},
                          {1, 2, 3, 12},
                          {0, 10, 10, 11}};

    u8 i = 0, j = 0;
    static u16 keydelay = 0;
    P2 = 0x0f; // 低四位置1
    if (P2 != 0x0f)
    {
        Delay(1000);
        if (P2 != 0x0f)
        {
            switch (P2)
            {
            case (0x07): // 0111
                j = 0;
                break;
            case (0x0b): // 1011
                j = 1;
                break;
            case (0x0d): // 1101
                j = 2;
                break;
            case (0x0e): // 1110
                j = 3;
                break;
            default:
                break;
            }

            P2 = 0xf0; // 高四位置1
            switch (P2)
            {
            case 0x70: // 0111
                i = 0;
                break;
            case 0xb0: // 1011
                i = 1;
                break;
            case 0xd0: // 1101
                i = 2;
                break;
            case 0xe0: // 1110
                i = 3;
                break;
            default:
                break;
            }

            switch (mode)
            {
            case num_mode: // 数字模式

                if (((i < 3) && (j < 3)) || (i == 3 && j == 0)) // [0~9]数字改变
                {
                    KeyValue[KeyValue[0]] = keyboard[i][j];
                }

                else if (i == 3 && j == 3) // [RST]复位
                {
                    KeyValue[1] = 0;
                    KeyValue[2] = 0;
                    KeyValue[3] = 0;
                }

                else if (i == 2 && j == 3) // [NULL]什么也不做
                {
                    // beepprotect = ~beepprotect;
                }

                else if (i == 3 && j == 1) // [.]选择小数点位置
                {
                    delay(20000);
                    KeyValue[0]--;
                    if (KeyValue[0] < 1)
                        KeyValue[0] = 3;
                }

                else if (i == 3 && j == 2) // [MODE]修改模式
                {
                    delay(20000);
                    Mode++;
                    if (Mode > 1)
                        Mode = 0;
                }

                else if (i == 0 && j == 3) // [++]
                {
                    u16 cur_value = KeyValue[3] + KeyValue[2] * 10 + KeyValue[1] * 100;
                    if (cur_value < 250)
                    {
                        delay(50000);
                        if (keydelay > 5)
                        {
                            k = 3;
                        }
                        else if (keydelay > 10)
                        {
                            k = 5;
                        }
                        else
                        {
                            k = 1;
                        }
                        KeyValue[3] += k;
                        if (KeyValue[3] > 9)
                        {
                            KeyValue[3] = 0;
                            KeyValue[2]++;
                            if (KeyValue[2] > 9)
                            {
                                KeyValue[2] = 0;
                                KeyValue[1]++;
                            }
                        }
                    }
                    else if (cur_value > 250)
                    {
                        KeyValue[3] = 0;
                        KeyValue[2] = 5;
                        KeyValue[1] = 2;
                    }
                    keydelay++;
                }

                else if (i == 1 && j == 3) // [--]
                {
                    u16 cur_value = KeyValue[3] + KeyValue[2] * 10 + KeyValue[1] * 100;
                    if (cur_value > 20)
                    {
                        delay(50000);
                        if (keydelay > 5)
                        {
                            k = 3;
                        }
                        else if (keydelay > 10)
                        {
                            k = 5;
                        }
                        else
                        {
                            k = 1;
                        }
                        KeyValue[3] -= k;
                        if (KeyValue[3] < 0)
                        {
                            KeyValue[3] = 9;
                            KeyValue[2]--;
                            if (KeyValue[2] < 0)
                            {
                                KeyValue[2] = 9;
                                KeyValue[1]--;
                            }
                        }
                    }
                    else if (cur_value < 20)
                    {
                        KeyValue[3] = 0;
                        KeyValue[2] = 2;
                        KeyValue[1] = 0;
                    }
                    keydelay++;
                }
                break;

            case time_mode: // 时间模式

                if (((i < 3) && (j < 3)) || (i == 3 && j == 0))
                {
                    if (KeyTime[0] != 3 && KeyTime[0] != 5)
                        KeyTime[KeyTime[0]] = keyboard[i][j];
                    else if (i > 1 || j == 0 || j == 1)
                        KeyTime[KeyTime[0]] = keyboard[i][j];
                }

                else if (i == 3 && j == 1)
                {
                    delay(20000);
                    KeyTime[0]--;
                    if (KeyTime[0] < 1)
                        KeyTime[0] = 6;
                }

                else if (i == 3 && j == 3)
                {
                    u16 k = 0;
                    for (k = 1; k <= 6; k++)
                        KeyTime[k] = 0;
                }

                else if (i == 3 && j == 2)
                {
                    delay(20000);
                    Mode++;
                    if (Mode > 1)
                        Mode = 0;
                }
                break;
            }
        }
    }
    else
    {
        keydelay = 0;
    }
}

void Display(void)
{
    u8 i;
    switch (mode)
    {
    case num_mode:
        for (i = 0; i < 8; i++)
        {
            P0 = i;
            if (i == 0)
            {
                P1 = smgduan[mode];
            }
            else if (i != KeyValue[0] + 4)
                P1 = smgduan[KeyValue[i - 4]];
            else
                P1 = smgduan[KeyValue[i - 4]] + 128;
            delay(100);
            P1 = 0;
            if (i == 0)
                i = i + 4;
        }
        break;

    case time_mode:
        for (i = 0; i < 8; i++)
        {
            P0 = i;
            if (i == 0)
            {
                P1 = smgduan[mode];
            }
            else if (i != KeyTime[0] + 1)
                P1 = smgduan[KeyTime[i - 1]];
            else
                P1 = smgduan[KeyTime[i - 1]] + 128;
            delay(100);
            P1 = 0;
            if (i == 0)
                i = i + 1;
        }
        break;
    }
}

void timer0_init(void)
{
    TMOD &= 0xF0; // 低四位置0,高四位不变
    TMOD |= 0x01; // 最低置1
    TH0 = 0xd8;   // 给定时器赋初值，定时10ms
    TL0 = 0xf0;
    ET0 = 1; // 打开定时器0中断允许
    TR0 = 1; // 打开定时器
}

void timer0() interrupt 0
{
    TF0 = 0;    // 清除TF0标志
    TH0 = 0Xd8; // 给定时器赋初值，定时10ms
    TL0 = 0Xf0;
    KeyDown();
    Display();
}

void main()
{
    IT0 = 1; // 下降沿触发
    EX0 = 1; // 外部中断0
    EA = 1;  // 总中断
    PX0 = 0; // 中断优先级

    timer0_init();

    while (1)
    {
        nop();
    }
}