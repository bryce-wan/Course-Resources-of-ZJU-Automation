#include "exti.h"
#include "led.h"
#include "SysTick.h"
#include "key.h"

/*******************************************************************************
* 函 数 名         : My_EXTI_Init
* 函数功能		   : 外部中断初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void My_EXTI_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);//选择GPIO管脚用作外部中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);//选择GPIO管脚用作外部中断线路
	
	
	//EXTI8\9 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line8|EXTI_Line9; 
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
}


/*******************************************************************************
* 函 数 名         : EXTI9_5_IRQHandler
* 函数功能		   : 外部中断8、9函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line8)==1)
	{
		delay_ms(10);
		if(KEY1==0)
		{
			led2=0;
		}
	}
	else if(EXTI_GetITStatus(EXTI_Line9)==1)
	{
		delay_ms(10);
		if(KEY2==0)
		{
			led2=1;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line8|EXTI_Line9);
}


