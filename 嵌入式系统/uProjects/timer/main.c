#include <reg51.h>
#define start_year 4;  // 2004
#define start_month 2; // February
#define start_day 27;  // 27th
#define start_hour 23; // 23:58:00
#define start_min 58;
#define start_sec 0;

// no speed up
// #define counter_H 0x3c;
// #define counter_L 0xb0;

// speed up 1000x
#define counter_H 0xff;
#define counter_L 0xce;

struct TIME
{
    unsigned char year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char min;
    unsigned char sec;
} data time;

// not leap year
unsigned char MONTH1[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
// leap year
unsigned char MONTH2[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
unsigned int MonthDay;
unsigned char cnt_50ms = 0;

// judge whether the year is leap year
unsigned char is_leap_year(unsigned char year)
{
    return ((year + 2000) % 4 == 0 && (year + 2000) % 100 != 0) || ((year + 2000) % 400 == 0);
}

// timer0 initialization
void timer0_init(void)
{
    TMOD = 0x01;     // set timer0 as mode1 (16-bit)
    TH0 = counter_H; // initial counter values
    TL0 = counter_L;
    TR0 = 1; // timer0 start run
    ET0 = 1; // enable timer0 interrupt
    EA = 1;  // open global interrupt switch
}

// timer0 interrupt service routine
void timer0_isr(void) interrupt 1
{
    TH0 = counter_H; // reload counter values
    TL0 = counter_L;
    cnt_50ms++;

    if (cnt_50ms == 20)
    {
        cnt_50ms = 0;
        time.sec++;
        if (time.sec == 60)
        {
            time.sec = 0;
            time.min++;
            if (time.min == 60)
            {
                time.min = 0;
                time.hour++;
                if (time.hour == 24)
                {
                    time.hour = 0;
                    time.day++;
                    if (is_leap_year(time.year))
                        MonthDay = MONTH2[time.month - 1];
                    else
                        MonthDay = MONTH1[time.month - 1];

                    if (time.day == MonthDay + 1)
                    {
                        time.day = 1;
                        time.month++;
                        if (time.month == 13)
                        {
                            time.month = 1;
                            time.year++;
                        }
                    }
                }
            }
        }
    }
}

void main(void)
{
    // initialize time
    time.year = start_year;
    time.month = start_month;
    time.day = start_day;
    time.hour = start_hour;
    time.min = start_min;
    time.sec = start_sec;

    timer0_init();
    while (1)
        ;
}