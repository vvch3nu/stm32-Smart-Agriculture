#include "tim3.h"
#include "gizwits_product.h"
  
static void GENERAL_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void GENERAL_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;		
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period=(1000-1);
	  // ʱ��Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_Prescaler= 71;	
		// ʱ�ӷ�Ƶ���� ��û�õ����ù�
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
		// ����������ģʽ������Ϊ���ϼ���
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		
		// �ظ���������ֵ��û�õ����ù�
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
		// ����������жϱ�־λ
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	  
		// �����������ж�
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
		
		// ʹ�ܼ�����
    TIM_Cmd(TIM3, ENABLE);
}

void GENERAL_TIM_Init(void)
{
	GENERAL_TIM_NVIC_Config();
	GENERAL_TIM_Mode_Config();		
}

void TIM3_IRQHandler(void)
{
		if ( TIM_GetITStatus( TIM3, TIM_IT_Update) != RESET ) 
		{	
				TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);  	
				gizTimerMs();
		}		 	
}






