#include "wkup.h"

/*******************************************************************************
* �� �� ��         : Enter_Standby_Mode
* ��������		   : �������ģʽ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Enter_Standby_Mode(void)
{
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);//ʹ��PWR����ʱ��
	
	PWR_ClearFlag(PWR_FLAG_WU);//���Wake-up ��־
	
	PWR_WakeUpPinCmd(ENABLE);//ʹ�ܻ��ѹܽ�	ʹ�ܻ���ʧ�ܻ��ѹܽŹ���
	
	
	PWR_EnterSTANDBYMode();//�������ģʽ
}



