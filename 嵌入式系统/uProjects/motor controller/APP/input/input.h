#ifndef _input_H
#define _input_H

#include "system.h"

extern u8 TIM3_CH1_CAPTURE_STA; //���벶���״̬
extern u16 TIM3_CH1_CAPTURE_VAL;//���벶��ֵ


void TIM3_CH1_Input_Init(u16 arr,u16 psc);
	
#endif
