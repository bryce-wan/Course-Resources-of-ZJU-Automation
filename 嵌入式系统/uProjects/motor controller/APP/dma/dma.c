#include "dma.h"

/*******************************************************************************
* �� �� ��         : DMAx_Init
* ��������		   : DMA��ʼ������
* ��    ��         : 
					 DMAy_Channelx:DMAͨ��ѡ��,@ref DMA_channel DMA_Channel_0~DMA_Channel_7
					 par:�����ַ
					 mar:�洢����ַ
					 ndtr:���ݴ�����
* ��    ��         : ��
*******************************************************************************/ 
void DMAx_Init(DMA_Channel_TypeDef* DMAy_Channelx,u32 par,u32 mar,u16 ndtr)
{
	DMA_InitTypeDef  DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//DMA1ʱ��ʹ�� 
	
	//DMA_DeInit(DMAy_Channelx);
	
	/* ���� DMA */
	DMA_InitStructure.DMA_PeripheralBaseAddr = par;//DMA�����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = mar;//DMA �洢��0��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//�洢��������ģʽ
	DMA_InitStructure.DMA_BufferSize = ndtr;//���ݴ����� 
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���:8λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ���:8λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ����ͨģʽ 
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//�е����ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMAy_Channelx, &DMA_InitStructure);//��ʼ��DMA 
	
}

/*******************************************************************************
* �� �� ��         : DMAx_Enable
* ��������		   : ����һ��DMA����
* ��    ��         : DMAy_Channelx:DMAͨ��ѡ��,@ref DMA_channel DMA_Channel_0~DMA_Channel_7
					 ndtr:���ݴ�����
* ��    ��         : ��
*******************************************************************************/ 
void DMAx_Enable(DMA_Channel_TypeDef *DMAy_Channelx,u16 ndtr)
{
 
	DMA_Cmd(DMAy_Channelx, DISABLE);                      //�ر�DMA���� 
	
	DMA_SetCurrDataCounter(DMAy_Channelx,ndtr);          //���ݴ�����  
 
	DMA_Cmd(DMAy_Channelx, ENABLE);                      //����DMA���� 
}	  
