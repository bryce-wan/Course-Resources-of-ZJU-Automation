#include "input.h"

u8 TIM3_CH1_CAPTURE_STA; //输入捕获状态 
u16 TIM3_CH1_CAPTURE_VAL;//输入捕获值

/*******************************************************************************
* 函 数 名         : TIM3_CH1_Input_Init
* 函数功能		   : TIM3_CH1输入捕获初始化函数
* 输    入         : arr：自动重装载值
					 psc：预分频系数
* 输    出         : 无
*******************************************************************************/
void TIM3_CH1_Input_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能TIM3时钟
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;//管脚设置
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	 //设置上拉输入模式
	GPIO_Init(GPIOA,&GPIO_InitStructure); 	   /* 初始化GPIO */
	
	TIM_TimeBaseInitStructure.TIM_Period=arr;   //自动装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //分频系数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);	
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1; //通道1
	TIM_ICInitStructure.TIM_ICFilter=0x00;  //滤波
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;//捕获极性
	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1; //分频系数
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;//直接映射到TI1
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
		
	TIM_Cmd(TIM3,ENABLE); //使能定时器
}

/*******************************************************************************
* 函 数 名         : TIM3_IRQHandler
* 函数功能		   : TIM3中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void TIM3_IRQHandler(void)
{
	if((TIM3_CH1_CAPTURE_STA&0x80)==0) //还未成功捕获
	{
		if(TIM_GetITStatus(TIM3,TIM_IT_Update)) //发生更新中断
		{
			if(TIM3_CH1_CAPTURE_STA&0X40)//捕获到了高电平
			{
				if((TIM3_CH1_CAPTURE_STA&0x3f)==0x3f) //高电平时间太长
				{
					TIM3_CH1_CAPTURE_STA|=0x80; //标志一次捕获成功
					TIM3_CH1_CAPTURE_VAL=0xffff;
				}
				else
				{
					TIM3_CH1_CAPTURE_STA++;
				}
			}
		}
		if(TIM_GetITStatus(TIM3,TIM_IT_CC1)) //发生捕获中断
		{
			if(TIM3_CH1_CAPTURE_STA&0X40)//捕获到了高电平
			{
				TIM3_CH1_CAPTURE_STA|=0x80; //成功捕获一次下降沿低电平
				TIM3_CH1_CAPTURE_VAL=TIM_GetCapture1(TIM3);
				TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling); //设置下降沿捕获
			}
			else
			{
				TIM3_CH1_CAPTURE_STA=0;
				TIM3_CH1_CAPTURE_VAL=0;
				TIM3_CH1_CAPTURE_STA|=0x40; //捕获到低电平 标志
				TIM_Cmd(TIM3,DISABLE);
				TIM_SetCounter(TIM3,0); //定时器初值为0
				TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising); //设置上升沿捕获
				TIM_Cmd(TIM3,ENABLE);
			}
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_CC1|TIM_IT_Update);
}


