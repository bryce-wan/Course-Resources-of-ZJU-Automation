#ifndef _dma_H
#define _dma_H

#include "system.h"


void DMAx_Init(DMA_Channel_TypeDef* DMAy_Channelx,u32 par,u32 mar,u16 ndtr);//����DMAx_CHx
void DMAx_Enable(DMA_Channel_TypeDef *DMAy_Channelx,u16 ndtr);	//ʹ��һ��DMA����

#endif
