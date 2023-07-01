#ifndef _smg_H
#define _smg_H

#include "system.h"

/*  ?????????????????? */
#define SMG_PORT GPIOB
#define SMG_PIN (GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)
#define SMG_PORT_RCC RCC_APB2Periph_GPIOB
#define LS_PORT GPIOA
#define LS_PIN (GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5)
#define LS_PORT_RCC RCC_APB2Periph_GPIOA

void SMG_Init(void); // ?????????

#endif
