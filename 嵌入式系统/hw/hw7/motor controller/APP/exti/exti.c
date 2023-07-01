#include "exti.h"
#include "led.h"
#include "SysTick.h"
#include "key.h"

/*******************************************************************************
* �� �� ��         : My_EXTI_Init
* ��������		   : �ⲿ�жϳ�ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void My_EXTI_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);//ѡ��GPIO�ܽ������ⲿ�ж���·
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);//ѡ��GPIO�ܽ������ⲿ�ж���·
	
	
	//EXTI8\9 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line8|EXTI_Line9; 
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
}


/*******************************************************************************
* �� �� ��         : EXTI9_5_IRQHandler
* ��������		   : �ⲿ�ж�8��9����
* ��    ��         : ��
* ��    ��         : ��
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


