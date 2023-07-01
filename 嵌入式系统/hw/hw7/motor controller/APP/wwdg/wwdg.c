#include "wwdg.h"
#include "led.h"
#include "SysTick.h"

/*******************************************************************************
* �� �� ��         : WWDG_Init
* ��������		   : WWDG��ʼ��
					 ����ֵ�ǣ�0x5f
					 ��ʱ������ֵ�ǣ�0x7f
					 Ԥ��Ƶֵ��:8
					 ���ڿ��Ź������жϵ�Ƶ�ʼ��㹫ʽ�ǣ�PCLK1/(4096*2^pre)
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void WWDG_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE); //�������ڿ��Ź���ʱ��
	WWDG_SetWindowValue(0x5f);//���ô���ֵ
	WWDG_SetPrescaler(WWDG_Prescaler_8);//���÷�Ƶֵ
	
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;//�����ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���
	
	WWDG_Enable(0x7f); //ʹ�ܴ��ڿ��Ź�����ʼ��������ֵ
	WWDG_ClearFlag(); //������ڿ��Ź�״̬��־(��һ�������ϣ�������벻���ж�)
	WWDG_EnableIT(); //�����ж�
	
}

/*******************************************************************************
* �� �� ��         : WWDG_IRQHandler
* ��������		   : WWDG�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void WWDG_IRQHandler(void)
{
	WWDG_SetCounter(0x7f); //���¸�ֵ
	WWDG_ClearFlag(); //������ڿ��Ź�״̬��־
	led2=!led2;	
}
