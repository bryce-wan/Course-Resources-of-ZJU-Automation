#include "smg.h"

/*******************************************************************************
 * �� �� ��         : SMG_Init
 * ��������		   : ����ܳ�ʼ��
 * ��    ��         : ��
 * ��    ��         : ��
 *******************************************************************************/
void SMG_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure; // ����һ���ṹ�������������ʼ��GPIO
	/* ����GPIOʱ�� */
	RCC_APB2PeriphClockCmd(SMG_PORT_RCC, ENABLE);

	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin = SMG_PIN; // ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SMG_PORT, &GPIO_InitStructure); /* ��ʼ��GPIO */

	RCC_APB2PeriphClockCmd(LS_PORT_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LS_PORT, &GPIO_InitStructure);
}
