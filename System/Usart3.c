#include "usart3.h"	

uint8_t Usart3_RxPacket[6];				//����������ݰ�����
uint8_t Usart3_RxFlag;					//����������ݰ���־λ

void Uart3_Init(void){
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART3��GPIOAʱ��
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��GPIOBʱ��
	
	//USART3_TX   GPIOB.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.10
   
    //USART3_RX	  GPIOB.11��ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.11  

  //Usart3 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;		//�����ȼ�4
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = 9600;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART3, &USART_InitStructure); //��ʼ������3
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3 

}

//uint8_t Usart3_GetRxFlag(void)
//{
//	if (Usart3_RxFlag == 1)			//��־λΪ1
//	{
//		Usart3_RxFlag = 0;
//		return 1;					//�򷵻�1�����Զ������־λ
//	}
//	return 0;						//��־λΪ0���򷵻�0
//}

void USART3_IRQHandler(void)                	//����3�жϷ������
{
		uint8_t Res;
		static uint8_t RxState = 0;		//��ǰ״̬��״̬
		static uint8_t pRxPacket = 0;	//��ǰ��������λ��

		if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
			Res =USART_ReceiveData(USART3);	//��ȡ���յ�������	
			switch (RxState)
			{
				case 0: 
					if (Res == 0x2C)
					{
						Usart3_RxPacket[pRxPacket] = Res;	//�����ݴ�������
						pRxPacket++;
						RxState = 1;

					}
					else
					{
						pRxPacket = 0;
						RxState = 0;
					}
					break;
				case 1: 
						Usart3_RxPacket[pRxPacket] = Res;	//�����ݴ�������
						pRxPacket++;
						if(pRxPacket >= 6)
						{
							pRxPacket = 0;
							RxState = 2;
						}
					break;
				case 2:
					if (Usart3_RxPacket[5] == (uint8_t)(Usart3_RxPacket[0] + Usart3_RxPacket[1]	//��֤���յ��������Ƿ���ȷ
						+ Usart3_RxPacket[2] + Usart3_RxPacket[3] + Usart3_RxPacket[4]))
					{
						
						RxState = 0;
						pRxPacket = 0;
						Usart3_RxFlag = 1;		//�������ݰ���־λ��1���ɹ�����һ�����ݰ�
					}
					else
					{
						pRxPacket = 0;
						RxState = 0;
					}
					break;
			}
			
			USART_ClearITPendingBit(USART3, USART_IT_RXNE);		//�����־λ
		} 
} 


