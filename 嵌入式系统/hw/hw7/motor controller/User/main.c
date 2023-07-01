// #include "stm32f10x.h"
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "ds18b20.h"
#include "pwm.h"
#include "smg.h"
#include "key.h"

u8 smgduan[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                  0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71}; // 0~F
u8 NOW_TEMP[4] = {2, 8, 0, 0};
u8 REF_TEMP[4] = {2, 8, 0, 0}; // modifiable
u8 dot = 0;
float diff;
float now_temp;
float ref_temp;

void Display(void); // update the display
void Keydown(void); // scan the key and respond to the keydown event
void Drive(void);   // drive the motor

int main()
{
    u8 cnt = 0;
    SysTick_Init(72);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_Init();
    SMG_Init();
    TIM3_CH1_PWM_Init(2000, 72 - 1);
    KEY_Init();
    USART1_Init(9600);

    while (DS18B20_Init())
    {
        printf("DS18B20 Init Failed!\r\n");
        delay_ms(500);
    }
    printf("DS18B20 Init Success!\r\n");

    while (1)
    {
        Keydown();
        now_temp = DS18B20_GetTemperture();
        ref_temp = 10 * REF_TEMP[0] + REF_TEMP[1] + 0.1 * REF_TEMP[2] + 0.01 * REF_TEMP[3];
        Display();
        Drive();
        delay_us(1000);

        if (cnt > 200)
        {
            cnt = 0;
            printf("now_temp: %f\r\n", now_temp);
            printf("ref_temp: %f\r\n", ref_temp);
            printf("dot: %d\r\n", dot);
        }
        cnt++;
    }
}

void Drive(void)
{
    if (now_temp < ref_temp)
    {
        led1 = 0;
        diff = ref_temp - now_temp;
        TIM_SetCompare1(TIM3, 0);
        TIM_SetCompare2(TIM3, diff * 50 + 250);
    }
    else if (now_temp > ref_temp)
    {
        led1 = 1;
        diff = now_temp - ref_temp;
        TIM_SetCompare1(TIM3, diff * 50 + 250);
        TIM_SetCompare2(TIM3, 0);
    }
}

void Keydown(void)
{
    u8 key;
    key = KEY_Scan(0);
    switch (key)
    {
    case KEY1_VALUE:
        REF_TEMP[dot] += 1;
        break;

    case KEY2_VALUE:
        REF_TEMP[dot] -= 1;
        break;

    case KEY5_VALUE:
        dot += 1;
        break;
    }

    if (dot == 4)
        dot = 0;

    if (REF_TEMP[3] == 10)
    {
        REF_TEMP[3] = 0;
        REF_TEMP[2]++;
    }
    if (REF_TEMP[2] == 10)
    {
        REF_TEMP[2] = 0;
        REF_TEMP[1]++;
    }
    if (REF_TEMP[1] == 10)
    {
        REF_TEMP[1] = 0;
        REF_TEMP[0]++;
    }
    if (REF_TEMP[3] == 255)
    {
        REF_TEMP[3] = 9;
        REF_TEMP[2]--;
    }
    if (REF_TEMP[2] == 255)
    {
        REF_TEMP[2] = 9;
        REF_TEMP[1]--;
    }
    if (REF_TEMP[1] == 255)
    {
        REF_TEMP[1] = 9;
        REF_TEMP[0]--;
    }
    if (REF_TEMP[0] == 255)
    {
        REF_TEMP[3] = 0;
        REF_TEMP[2] = 0;
        REF_TEMP[1] = 0;
        REF_TEMP[0] = 0;
    }
    if (10 * REF_TEMP[0] + REF_TEMP[1] + 0.1 * REF_TEMP[2] + 0.01 * REF_TEMP[3] > 50)
    {
        REF_TEMP[3] = 0;
        REF_TEMP[2] = 0;
        REF_TEMP[1] = 0;
        REF_TEMP[0] = 5;
    }
}

void Display(void)
{

    u16 now_temp_int = (u16)(now_temp * 100);

    NOW_TEMP[3] = now_temp_int % 10;        // individual digit
    NOW_TEMP[2] = now_temp_int / 10 % 10;   // ten digit
    NOW_TEMP[1] = now_temp_int / 100 % 10;  // hundred digit
    NOW_TEMP[0] = now_temp_int / 1000 % 10; // thousand digit

    // 000
    GPIO_ResetBits(GPIOA, GPIO_Pin_3);
    GPIO_ResetBits(GPIOA, GPIO_Pin_4);
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
    GPIO_Write(SMG_PORT, (u16)(smgduan[REF_TEMP[0]]) << 8);
    delay_us(1000);
    GPIO_Write(SMG_PORT, 0x0000);

    // 001
    GPIO_SetBits(GPIOA, GPIO_Pin_3);
    GPIO_ResetBits(GPIOA, GPIO_Pin_4);
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
    GPIO_Write(SMG_PORT, (u16)(smgduan[REF_TEMP[1]] + 0x80) << 8);
    delay_us(1000);
    GPIO_Write(SMG_PORT, 0x0000);

    // 010
    GPIO_ResetBits(GPIOA, GPIO_Pin_3);
    GPIO_SetBits(GPIOA, GPIO_Pin_4);
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
    GPIO_Write(SMG_PORT, (u16)(smgduan[REF_TEMP[2]]) << 8);
    delay_us(1000);
    GPIO_Write(SMG_PORT, 0x0000);

    // 011
    GPIO_SetBits(GPIOA, GPIO_Pin_3);
    GPIO_SetBits(GPIOA, GPIO_Pin_4);
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
    GPIO_Write(SMG_PORT, (u16)(smgduan[REF_TEMP[3]]) << 8);
    delay_us(1000);
    GPIO_Write(SMG_PORT, 0x0000);

    // 100
    GPIO_ResetBits(GPIOA, GPIO_Pin_3);
    GPIO_ResetBits(GPIOA, GPIO_Pin_4);
    GPIO_SetBits(GPIOA, GPIO_Pin_5);
    GPIO_Write(SMG_PORT, (u16)(smgduan[NOW_TEMP[0]]) << 8);
    delay_us(1000);
    GPIO_Write(SMG_PORT, 0x0000);

    // 101
    GPIO_SetBits(GPIOA, GPIO_Pin_3);
    GPIO_ResetBits(GPIOA, GPIO_Pin_4);
    GPIO_SetBits(GPIOA, GPIO_Pin_5);
    GPIO_Write(SMG_PORT, (u16)(smgduan[NOW_TEMP[1]] + 0x80) << 8);
    delay_us(1000);
    GPIO_Write(SMG_PORT, 0x0000);

    // 110
    GPIO_ResetBits(GPIOA, GPIO_Pin_3);
    GPIO_SetBits(GPIOA, GPIO_Pin_4);
    GPIO_SetBits(GPIOA, GPIO_Pin_5);
    GPIO_Write(SMG_PORT, (u16)(smgduan[NOW_TEMP[2]]) << 8);
    delay_us(1000);
    GPIO_Write(SMG_PORT, 0x0000);

    // 111
    GPIO_SetBits(GPIOA, GPIO_Pin_3);
    GPIO_SetBits(GPIOA, GPIO_Pin_4);
    GPIO_SetBits(GPIOA, GPIO_Pin_5);
    GPIO_Write(SMG_PORT, (u16)(smgduan[NOW_TEMP[3]]) << 8);
    delay_us(1000);
    GPIO_Write(SMG_PORT, 0x0000);
}
