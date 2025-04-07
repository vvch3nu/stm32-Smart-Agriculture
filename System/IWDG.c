#include "iwdg.h"

void IWDG_Init(void)
{
	//���ϵͳ���ɶ������Ź�����ĸ�λ����������λ
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)	
	{
		//�������Ź�����ĸ�λ
		printf("IWDG RST ...\r\n");
		//�����־λ
		RCC_ClearFlag();
	}
	else
	{
		//����������λ
		printf("Normal RST ...\r\n");
	}
	//ʹ�� LSI ʱ�� �����Ź��ṩʱ�ӻ�׼��������Ҳ�У�ϵͳ��ϵͳ������ʱ�ӣ�
	RCC_LSICmd(ENABLE);
	//�ȴ�LSI �ȶ�
	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
	//������� IWDG_PR and IWDG_RLR�Ĵ���
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	//���÷�Ƶֵ�� LSI/32  40K/64 = 625HZ
	IWDG_SetPrescaler(IWDG_Prescaler_64);
	IWDG_SetReload(6250);	//10s���Ź� ����10s��ι�� ���Ź��ͻ�ʹ��Ƭ����λ
	//ʹ����װ�ؼĴ�������
	IWDG_ReloadCounter();    
	
	//ʹ�ܿ��Ź�
	IWDG_Enable();
}



