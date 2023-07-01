#include "smg.h"

/*******************************************************************************
 * 函 数 名         : SMG_Init
 * 函数功能		   : 数码管初始化
 * 输    入         : 无
 * 输    出         : 无
 *******************************************************************************/
void SMG_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure; // 声明一个结构体变量，用来初始化GPIO
	/* 开启GPIO时钟 */
	RCC_APB2PeriphClockCmd(SMG_PORT_RCC, ENABLE);

	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin = SMG_PIN; // 选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SMG_PORT, &GPIO_InitStructure); /* 初始化GPIO */

	RCC_APB2PeriphClockCmd(LS_PORT_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LS_PORT, &GPIO_InitStructure);
}
