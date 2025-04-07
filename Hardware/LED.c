#include "led.h"


void LED_Init(void)
{
	//����GPIOBʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//����LED����Ϊ�������ģʽ
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_PROT, &GPIO_InitStructure);
	LED_HIGH;
}


void LED_ON(void)
{
	LED_LOW;
}

void LED_OFF(void)
{
	LED_HIGH;
}
