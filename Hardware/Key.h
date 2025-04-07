#ifndef	__KEY_H
#define __KEY_H

#include "stm32f10x.h"                  // Device header

#define KEY1_GPIO_PIN	GPIO_Pin_9
#define KEY2_GPIO_PIN	GPIO_Pin_8
#define KEY3_GPIO_PIN	GPIO_Pin_7
#define KEY4_GPIO_PIN	GPIO_Pin_6

#define KEY_PROT	GPIOB
 
#define KEY1	GPIO_ReadInputDataBit(GPIOB, KEY1_GPIO_PIN) // ��ȡ����0
#define KEY2	GPIO_ReadInputDataBit(GPIOB, KEY2_GPIO_PIN) // ��ȡ����1
#define KEY3	GPIO_ReadInputDataBit(GPIOB, KEY3_GPIO_PIN) // ��ȡ����2
#define KEY4	GPIO_ReadInputDataBit(GPIOB, KEY4_GPIO_PIN) // ��ȡ����2

#define KEY_DELAY_TIME				10
#define KEY_LONG_TIME				2000

#define KEY_Continue_TIME			500
#define KEY_Continue_Trigger_TIME	5

extern u8 KeyNum;

void Key_Init(void);
void Key_scan(void);


#endif
