#include "input.h"

u8 TIM3_CH1_CAPTURE_STA; //���벶��״̬ 
u16 TIM3_CH1_CAPTURE_VAL;//���벶��ֵ

/*******************************************************************************
* �� �� ��         : TIM3_CH1_Input_Init
* ��������		   : TIM3_CH1���벶���ʼ������
* ��    ��         : arr���Զ���װ��ֵ
					 psc��Ԥ��Ƶϵ��
* ��    ��         : ��
*******************************************************************************/
void TIM3_CH1_Input_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ��TIM3ʱ��
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;//�ܽ�����
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	 //������������ģʽ
	GPIO_Init(GPIOA,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	
	TIM_TimeBaseInitStructure.TIM_Period=arr;   //�Զ�װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //��Ƶϵ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);	
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1; //ͨ��1
	TIM_ICInitStructure.TIM_ICFilter=0x00;  //�˲�
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;//������
	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1; //��Ƶϵ��
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;//ֱ��ӳ�䵽TI1
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
		
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��
}

/*******************************************************************************
* �� �� ��         : TIM3_IRQHandler
* ��������		   : TIM3�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void TIM3_IRQHandler(void)
{
	if((TIM3_CH1_CAPTURE_STA&0x80)==0) //��δ�ɹ�����
	{
		if(TIM_GetITStatus(TIM3,TIM_IT_Update)) //���������ж�
		{
			if(TIM3_CH1_CAPTURE_STA&0X40)//�����˸ߵ�ƽ
			{
				if((TIM3_CH1_CAPTURE_STA&0x3f)==0x3f) //�ߵ�ƽʱ��̫��
				{
					TIM3_CH1_CAPTURE_STA|=0x80; //��־һ�β���ɹ�
					TIM3_CH1_CAPTURE_VAL=0xffff;
				}
				else
				{
					TIM3_CH1_CAPTURE_STA++;
				}
			}
		}
		if(TIM_GetITStatus(TIM3,TIM_IT_CC1)) //���������ж�
		{
			if(TIM3_CH1_CAPTURE_STA&0X40)//�����˸ߵ�ƽ
			{
				TIM3_CH1_CAPTURE_STA|=0x80; //�ɹ�����һ���½��ص͵�ƽ
				TIM3_CH1_CAPTURE_VAL=TIM_GetCapture1(TIM3);
				TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling); //�����½��ز���
			}
			else
			{
				TIM3_CH1_CAPTURE_STA=0;
				TIM3_CH1_CAPTURE_VAL=0;
				TIM3_CH1_CAPTURE_STA|=0x40; //���񵽵͵�ƽ ��־
				TIM_Cmd(TIM3,DISABLE);
				TIM_SetCounter(TIM3,0); //��ʱ����ֵΪ0
				TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising); //���������ز���
				TIM_Cmd(TIM3,ENABLE);
			}
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_CC1|TIM_IT_Update);
}


