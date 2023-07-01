#include "reg52.h"
#include <intrins.h>

typedef unsigned int uint;
typedef unsigned char uchar;

uchar code smgduan[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                          0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};

uchar Mode = 0; // 用于改变模式
int sec = 0;
int KeyValue[4] = {3, 0, 2, 0};
int KeyTime[7] = {6, 0, 0, 0, 0, 0, 0};

void KeyScan(void);

void Display(void);

void delay(uint i);

void time0() interrupt 0
{
    TF0 = 0;    //
    TH0 = 0Xd8; // 给定时器赋初值，定时10ms
    TL0 = 0Xf0;
    KeyScan();
    Display();
}

void main()
{
    IT0 = 1; // 下降沿触发
    EX0 = 1; // 外部中断0
    EA = 1;  // 总中断
    PX0 = 0; // 中断优先级

    TMOD |= 0X01;
    TH0 = 0Xd8; // 给定时器赋初值，定时10ms
    TL0 = 0Xf0;
    TR0 = 1;
    PT0 = 1;

    while (1)
    {
        nop();
    }
}

void KeyScan(void)
{
    static del = 0;
    char a = 0;
    int i = 0, j = 0, k = 1;
    int jianpan[4][4] = {{7, 8, 9, 14}, {4, 5, 6, 13}, {1, 2, 3, 12}, {0, 10, 10, 11}};
    P2 = 0x0f;
    if (P2 != 0x0f)
    {
        delay(1000);
        if (P2 != 0x0f)
        {
            P2 = 0X0F;
            switch (P2)
            {
            case (0X07):
                i = 0;
                break;
            case (0X0b):
                i = 1;
                break;
            case (0X0d):
                i = 2;
                break;
            case (0X0e):
                i = 3;
                break;
            }
            P2 = 0XF0;
            switch (P2)
            {
            case (0X70):
                j = 0;
                break;
            case (0Xb0):
                j = 1;
                break;
            case (0Xd0):
                j = 2;
                break;
            case (0Xe0):
                j = 3;
                break;
            }

            switch (Mode)
            {
            case (0):
                if (((j < 3) && (i < 3)) || (j == 3 && i == 0))
                {
                    KeyValue[KeyValue[0]] = jianpan[j][i];
                }
                else if (j == 3 && i == 3)
                {
                    KeyValue[1] = 0;
                    KeyValue[2] = 0;
                    KeyValue[3] = 0;
                }
                else if (j == 2 && i == 3)
                {
                    beepprotect = ~beepprotect;
                }
                else if (j == 3 && i == 1)
                {
                    delay(20000);
                    KeyValue[0]--;
                    if (KeyValue[0] < 1)
                        KeyValue[0] = 3;
                }
                else if (j == 3 && i == 2)
                {
                    delay(20000);
                    Mode++;
                    if (Mode > 1)
                        Mode = 0;
                }
                else if (j == 0 && i == 3)
                {
                    if (KeyValue[3] + KeyValue[2] * 10 + KeyValue[1] * 100 < 250)
                    {
                        delay(50000);
                        if (del > 5)
                        {
                            k = 3;
                        }
                        else if (del > 10)
                        {
                            k = 5;
                        }
                        else
                        {
                            k = 1;
                        }
                        KeyValue[3] = KeyValue[3] + k;
                        if (KeyValue[3] > 9)
                        {
                            KeyValue[3] = KeyValue[3] - 10;
                            KeyValue[2]++;
                            if (KeyValue[2] > 9)
                            {
                                KeyValue[2] = KeyValue[2] - 10;
                                KeyValue[1]++;
                            }
                        }
                    }
                    else if (KeyValue[3] + KeyValue[2] * 10 + KeyValue[1] * 100 > 250)
                    {
                        KeyValue[3] = 0;
                        KeyValue[2] = 5;
                        KeyValue[1] = 2;
                    }
                    del++;
                }
                else if (j == 1 && i == 3)
                {
                    if (KeyValue[3] + KeyValue[2] * 10 + KeyValue[1] * 100 > 20)
                    {
                        delay(50000);
                        if (del > 5)
                        {
                            k = 3;
                        }
                        else if (del > 10)
                        {
                            k = 5;
                        }
                        else
                        {
                            k = 1;
                        }
                        KeyValue[3] = KeyValue[3] - k;
                        if (KeyValue[3] < 0)
                        {
                            KeyValue[3] = KeyValue[3] + 10;
                            KeyValue[2]--;
                            if (KeyValue[2] < 0)
                            {
                                KeyValue[2] = KeyValue[2] + 10;
                                KeyValue[1]--;
                            }
                        }
                    }
                    else if (KeyValue[3] + KeyValue[2] * 10 + KeyValue[1] * 100 < 20)
                    {
                        KeyValue[3] = 0;
                        KeyValue[2] = 2;
                        KeyValue[1] = 0;
                    }
                    del++;
                }
                break;
            case (1):
                if (((j < 3) && (i < 3)) || (j == 3 && i == 0))
                {
                    if (KeyTime[0] != 3 && KeyTime[0] != 5)
                        KeyTime[KeyTime[0]] = jianpan[j][i];
                    else if (j > 1 || i == 0 || i == 1)
                        KeyTime[KeyTime[0]] = jianpan[j][i];
                }
                else if (j == 3 && i == 1)
                {
                    delay(20000);
                    KeyTime[0]--;
                    if (KeyTime[0] < 1)
                        KeyTime[0] = 6;
                }
                else if (j == 3 && i == 3)
                {
                    uint k = 0;
                    for (k = 1; k <= 6; k++)
                        KeyTime[k] = 0;
                }
                else if (j == 3 && i == 2)
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
        del = 0;
    }
}

void Display(void)
{
    uchar i;
    switch (Mode)
    {
    case (0):
        for (i = 0; i < 8; i++)
        {
            P0 = i;
            if (i == 0)
            {
                P1 = smgduan[Mode];
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
    case (1):
        for (i = 0; i < 8; i++)
        {
            P0 = i;
            if (i == 0)
            {
                P1 = smgduan[Mode];
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

void delay(uint i)
{
    while (i--)
        ;
}