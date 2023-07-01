#include "reg52.h"

#define num_mode 0
#define time_mode 1

typedef unsigned int u16;
typedef unsigned char u8;

u8 code smgduan[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                       0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71}; // 0~9,A,b,C,d,E,F
u8 mode = 0, timer_start = 0;
int KeyValue[4] = {3, 0, 2, 0};
int KeyTime[7] = {6, 0, 0, 0, 0, 0, 0};
u16 cur_value;
u16 plus = 0;
u16 sub = 0;
u16 tempplus = 0;
u8 change = 0;
u8 dispmode = 0;

void KeyDown(void);
void Display(void);
void Delay(u16 i);

void timer0_init(void)
{
    // TMOD &= 0xF0; // clear the last 4 bits
    TMOD |= 0x01; // set the last 4 bits to 0001
    TH0 = 0xd8;   // set the initial value of timer0
    TL0 = 0xf0;
    ET0 = 1; // enable timer0 interrupt
    TR0 = 1; // start timer0
    PT0 = 1; // set the priority of timer0 interrupt to high
}

void timer0() interrupt 1
{
    if (timer_start == 1)
    {
        // modify = 0;
        u16 sec = 0;
        mode = 1;
        while (1)
        {
            if (TF0 == 1 && timer_start == 1)
            {
                TF0 = 0;
                TH0 = 0Xd8; // set the initial value of timer0
                TL0 = 0Xf0;
                sec++;
                if (sec >= 100)
                {
                    sec = 0;
                    KeyTime[6]--;
                    if (KeyTime[6] < 0)
                    {
                        KeyTime[6] = 9;
                        KeyTime[5]--;
                        if (KeyTime[5] < 0)
                        {
                            KeyTime[5] = 5;
                            KeyTime[4]--;
                            if (KeyTime[4] < 0)
                            {
                                KeyTime[4] = 9;
                                KeyTime[3]--;
                                if (KeyTime[3] < 0)
                                {
                                    KeyTime[3] = 5;
                                    KeyTime[2]--;
                                    if (KeyTime[2] < 0)
                                    {
                                        KeyTime[2] = 9;
                                        KeyTime[1]--;
                                        if (KeyTime[1] < 0)
                                            KeyTime[1] = 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (timer_start == 1)
            {
                // tempplus += 1;
                // if (tempplus > 100)
                // {
                //     if (KeyValue[3] + KeyValue[2] * 10 + KeyValue[1] * 100 < 250)
                //     {
                //         KeyValue[3] += 1;
                //         if (KeyValue[3] > 9)
                //         {
                //             KeyValue[3] = 0;
                //             KeyValue[2]++;
                //             if (KeyValue[2] > 9)
                //             {
                //                 KeyValue[2] = 0;
                //                 KeyValue[1]++;
                //             }
                //         }
                //     }
                //     tempplus = 0;
                // }
                change += 1;
            }

            Display(); // display the time
            KeyDown(); // check if the key is pressed

            if (KeyTime[1] == 0 && KeyTime[2] == 0 && KeyTime[3] == 0 && KeyTime[4] == 0 && KeyTime[5] == 0 && KeyTime[6] == 0) // time is up
            {
                timer_start = 0;
                return;
            }
        }
    }
}

void main()
{
    IT0 = 1; // set the interrupt type of INT0 to falling edge
    EX0 = 1; // enable INT0 interrupt
    EA = 1;  // enable all interrupt
    PX0 = 0; // set the priority of INT0 interrupt to low

    while (1)
    {
        Delay(100);
        KeyDown();
        Display();
    }
}

void Delay(u16 i)
{
    while (i--)
        ;
}

void KeyDown(void)
{
    u16 keyboard[4][4] = {{1, 2, 3, 14},
                          {4, 5, 6, 13},
                          {7, 8, 9, 12},
                          {10, 0, 11, 10}}; // keyboard map

    u8 i = 0, j = 0, k = 0;
    u8 temp;
    u8 sec, min, hour;
    u16 modified_value;
    static u16 keydelay = 0;

    cur_value = KeyValue[3] + KeyValue[2] * 10 + KeyValue[1] * 100;
    P2 = 0x0f;
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

            P2 = 0xf0;
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
            case num_mode: // number mode

                if ((((i < 3) && (j < 3)) || (i == 3 && j == 1)) && timer_start == 0) // 0~9
                {
                    temp = KeyValue[KeyValue[0]];
                    KeyValue[KeyValue[0]] = keyboard[i][j];

                    modified_value = KeyValue[3] + KeyValue[2] * 10 + KeyValue[1] * 100; // get the modified value

                    if (modified_value > 250)
                    {
                        KeyValue[1] = 2;
                        KeyValue[2] = 5;
                        KeyValue[3] = 0;
                    }
                    else if (modified_value < 20)
                    {
                        KeyValue[1] = 0;
                        KeyValue[2] = 2;
                        KeyValue[3] = 0;
                    }
                }

                else if (i == 3 && j == 2 && timer_start == 0) // [RST] reset the temperature value
                {
                    KeyValue[1] = 0;
                    KeyValue[2] = 2;
                    KeyValue[3] = 0;
                }

                else if (i == 3 && j == 0 && timer_start == 0) // [.] move the decimal point
                {
                    Delay(20000);
                    KeyValue[0]--;
                    if (KeyValue[0] < 1)
                        KeyValue[0] = 3;
                }

                else if (i == 3 && j == 3) // [MODE] modify the mode (num or time)
                {
                    Delay(20000);
                    mode += 1;
                    if (mode > 1)
                        mode = 0;
                }

                else if (i == 0 && j == 3 && timer_start == 0) // [++] plus
                {
                    plus += 1;
                    if (plus > 10)
                    {
                        if (cur_value < 250)
                        {
                            // Delay(13000);
                            // if (keydelay > 5)
                            // {
                            //     k = 3;
                            // }
                            // if (keydelay > 10)
                            // {
                            //     k = 5;
                            // }
                            // else
                            // {
                            //     k = 1;
                            // }
                            k = 1;
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
                        else if (cur_value >= 250)
                        {
                            KeyValue[1] = 2;
                            KeyValue[2] = 5;
                            KeyValue[3] = 0;
                        }
                        keydelay++;
                        // Delay(50000);
                        plus = 0;
                    }
                    Display();
                }

                else if (i == 1 && j == 3 && timer_start == 0) // [--] sub
                {
                    sub += 1;
                    if (sub > 10)
                    {
                        if (cur_value > 20)
                        {
                            // Delay(13000);
                            // if (keydelay > 5)
                            // {
                            //     k = 3;
                            // }
                            // if (keydelay > 10)
                            // {
                            //     k = 5;
                            // }
                            // else
                            // {
                            //     k = 1;
                            // }
                            k = 1;
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
                        else if (cur_value <= 20)
                        {
                            KeyValue[1] = 0;
                            KeyValue[2] = 2;
                            KeyValue[3] = 0;
                        }
                        keydelay++;
                        // Delay(50000);
                        sub = 0;
                    }
                    Display();
                }
                break;

            case time_mode: // time mode

                if ((((i < 3) && (j < 3)) || (i == 3 && j == 1)) && timer_start == 0) // 0~9
                {
                    temp = KeyTime[KeyTime[0]];
                    KeyTime[KeyTime[0]] = keyboard[i][j];

                    sec = KeyTime[6] + 10 * KeyTime[5];
                    min = KeyTime[4] + 10 * KeyTime[3];
                    hour = KeyTime[2] + 10 * KeyTime[1];
                    if (sec >= 60 || min >= 60 || hour >= 24)
                    {
                        KeyTime[KeyTime[0]] = temp;
                    }
                }

                else if (i == 3 && j == 0 && timer_start == 0) // [.] move the decimal point
                {
                    Delay(20000);
                    KeyTime[0]--;
                    if (KeyTime[0] < 1)
                        KeyTime[0] = 6;
                }

                else if (i == 3 && j == 2 && timer_start == 0) // [RST] reset the temperature value
                {
                    k = 0;
                    for (k = 1; k <= 6; k++)
                        KeyTime[k] = 0;
                }

                else if (i == 3 && j == 3) // [MODE] modify the mode (num or time)
                {
                    // modify = 1;
                    Delay(20000);
                    mode += 1;
                    if (mode > 1)
                        mode = 0;
                }

                else if (i == 0 && j == 3) // [STRAT] start the timer
                {
                    if (timer_start == 0)
                    {
                        timer_start = 1;
                        timer0_init();
                    }
                }

                else if (i == 1 && j == 3) // [STOP] stop the timer
                {
                    timer_start = 0;
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

void Display(void) // display the value
{
    u8 i;
    // save_mode = mode;
    if (timer_start == 0)
    {
        switch (mode)
        {
        case num_mode:
            for (i = 0; i < 8; i++)
            {
                P0 = i;
                if (i == 0)
                {
                    P1 = smgduan[mode]; // dispaly the mode
                }
                else if (i != KeyValue[0] + 4)
                    P1 = smgduan[KeyValue[i - 4]];
                else
                    P1 = smgduan[KeyValue[i - 4]] + 128;
                Delay(100);
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
                Delay(100);
                P1 = 0;
                if (i == 0)
                    i = i + 1;
            }
            break;
        }
    }

    else if (timer_start == 1)
    {
        if (change > 100)
        {
            if (dispmode == 1)
                dispmode = 0;
            else
                dispmode = 1;
            change = 0;
        }

        switch (dispmode)
        {
        case num_mode:
            for (i = 0; i < 8; i++)
            {
                P0 = i;
                if (i == 0)
                {
                    P1 = smgduan[mode]; // dispaly the mode
                }
                else if (i != KeyValue[0] + 4)
                    P1 = smgduan[KeyValue[i - 4]];
                else
                    P1 = smgduan[KeyValue[i - 4]] + 128;
                Delay(100);
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
                Delay(100);
                P1 = 0;
                if (i == 0)
                    i = i + 1;
            }
            break;
        }
    }
}
