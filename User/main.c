#include "stm32f10x.h"                  // Device header
#include "iwdg.h"
#include "adcx.h"
#include "ldr.h"
#include "oled.h"
#include "dht11.h"
#include "led.h"
#include "key.h"
#include "tim2.h"   
#include "tim3.h"   
#include "usart3.h"   
#include "usart.h"
#include "yl_69.h"
#include "motor.h"
#include "sensormodules.h"
#include "gizwits_product.h"
#include "flash.h"


#define KEY_1	1
#define KEY_2	2
#define KEY_3	3
#define KEY_4	4

#define FLASH_START_ADDR	0x0801f000	//д�����ʼ��ַ

SensorModules sensorData;	//�������������ݽṹ�����
SensorThresholdValue Sensorthreshold;	//������������ֵ�ṹ�����

uint8_t menu = 1;	//��ʾ�˵�����
uint8_t OLED_Clear_Flag;	//��ֵ���ý����������־λ
uint8_t mode = 0;	//ϵͳģʽ

enum 
{
	display_page1 = 1,
	display_page2,
	settingsPage
	
}MenuPages;

/**
  * @brief  ��ʾ�˵�1�Ĺ̶�����
  * @param  ��
  * @retval ��
  */
void OLED_Menu1(void)
{
	//��ʾϵͳ��
	OLED_ShowChinese(1, 1, 0);
	OLED_ShowChinese(1, 2, 1);
	OLED_ShowChinese(1, 3, 2);
	OLED_ShowChinese(1, 4, 3);
	OLED_ShowChinese(1, 5, 4);
	OLED_ShowChinese(1, 6, 5);
	OLED_ShowChinese(1, 7, 6);
	OLED_ShowChinese(1, 8, 7);
	
	//��ʾ��ϵͳģʽ����
	OLED_ShowChinese(2, 1, 6);
	OLED_ShowChinese(2, 2, 7);
	OLED_ShowChinese(2, 3, 19);
	OLED_ShowChinese(2, 4, 20);	
	OLED_ShowChar(2, 9, ':');
	
	//��ʾ������ǿ�ȣ�  Lux��
	OLED_ShowChinese(3, 1, 15);
	OLED_ShowChinese(3, 2, 16);	
	OLED_ShowChinese(3, 3, 28);
	OLED_ShowChinese(3, 4, 29);	
	OLED_ShowChar(3, 9, ':');
	OLED_ShowString(3, 14, "Lux");
	
	//��ʾ��������̼�� ��
	OLED_ShowChinese(4, 1, 24);
	OLED_ShowChinese(4, 2, 25);
	OLED_ShowChinese(4, 3, 26);
	OLED_ShowChinese(4, 4, 27);
	OLED_ShowChar(4, 9, ':');
	OLED_ShowString(4, 14, "ppm");
}

/**
  * @brief  ��ʾ�˵�2�Ĺ̶�����
  * @param  ��
  * @retval ��
  */
void OLED_Menu2(void)
{
	//��ʾ�������¶ȣ�  C��
	OLED_ShowChinese(1, 1, 13);
	OLED_ShowChinese(1, 2, 14);
	OLED_ShowChinese(1, 3, 8);
	OLED_ShowChinese(1, 4, 9);	
	OLED_ShowChar(1, 9, ':');
	OLED_ShowChar(1, 12, 'C');
	
	//��ʾ������ʪ�ȣ�  %��
	OLED_ShowChinese(2, 1, 13);
	OLED_ShowChinese(2, 2, 14);
	OLED_ShowChinese(2, 3, 10);
	OLED_ShowChinese(2, 4, 9);	
	OLED_ShowChar(2, 9, ':');
	OLED_ShowChar(2, 12, '%');		
	
	//��ʾ�������¶ȣ�  C��
	OLED_ShowChinese(3, 1, 11);
	OLED_ShowChinese(3, 2, 12);
	OLED_ShowChinese(3, 3, 8);
	OLED_ShowChinese(3, 4, 9);	
	OLED_ShowChar(3, 9, ':');
	OLED_ShowChar(3, 12, 'C');		
	
	//��ʾ������ʪ�ȣ�  %��
	OLED_ShowChinese(4, 1, 11);
	OLED_ShowChinese(4, 2, 12);
	OLED_ShowChinese(4, 3, 10);
	OLED_ShowChinese(4, 4, 9);	
	OLED_ShowChar(4, 9, ':');
	OLED_ShowChar(4, 12, '%');	
}

/**
  * @brief  ��ʾ�˵�1�Ĵ���������
  * @param  ��
  * @retval ��
  */
void SensorDataDisplay1(void)
{
	//��ʾϵͳ״̬����
	if (!mode)
	{
		OLED_ShowChinese(2, 6, 21);
		OLED_ShowChinese(2, 7, 22);		
	}
	else
	{
		OLED_ShowChinese(2, 6, 23);
		OLED_ShowChinese(2, 7, 22);			
	}
	
	//��ʾ����ǿ������
	OLED_ShowNum(3, 10, sensorData.lux, 4);
	
	//��ʾCO2Ũ������
	OLED_ShowNum(4, 10, sensorData.CO2, 4);
}

/**
  * @brief  ��ʾ�˵�2�Ĵ���������
  * @param  ��
  * @retval ��
  */
void SensorDataDisplay2(void)
{
	//��ʾ�����¶�����
	OLED_ShowNum(1, 10, sensorData.temp, 2);
	
	//��ʾ����ʪ������
	OLED_ShowNum(2, 10, sensorData.humi, 2);
	
	//��ʾ�����¶�����
	OLED_ShowNum(3, 10, sensorData.soilTemp, 2);
	
	//��ʾ����ʪ������
	OLED_ShowNum(4, 10, sensorData.soilHumi, 2);
}

/**
  * @brief  ��ʾ��ֵ���ý���1�Ĺ̶�����
  * @param  ��
  * @retval ��
  */
void OLED_settingsPage1(void)
{
	//��ʾ�������¶ȣ���
	OLED_ShowChinese(1, 2, 13);
	OLED_ShowChinese(1, 3, 14);
	OLED_ShowChinese(1, 4, 8);
	OLED_ShowChinese(1, 5, 9);	
	OLED_ShowChar(1, 11, ':');

	//��ʾ������ʪ�ȣ���
	OLED_ShowChinese(2, 2, 13);
	OLED_ShowChinese(2, 3, 14);
	OLED_ShowChinese(2, 4, 10);
	OLED_ShowChinese(2, 5, 9);	
	OLED_ShowChar(2, 11, ':');
	
	
	//��ʾ�������¶ȣ���
	OLED_ShowChinese(3, 2, 11);
	OLED_ShowChinese(3, 3, 12);
	OLED_ShowChinese(3, 4, 8);
	OLED_ShowChinese(3, 5, 9);	
	OLED_ShowChar(3, 11, ':');
	
	
	//��ʾ������ʪ�ȣ���
	OLED_ShowChinese(4, 2, 11);
	OLED_ShowChinese(4, 3, 12);
	OLED_ShowChinese(4, 4, 10);
	OLED_ShowChinese(4, 5, 9);	
	OLED_ShowChar(4, 11, ':');
}

/**
  * @brief  ��ʾ��ֵ���ý���2�Ĺ̶�����
  * @param  ��
  * @retval ��
  */
void OLED_settingsPage2(void)
{
	//��ʾ������ǿ�ȣ���
	OLED_ShowChinese(1, 2, 15);
	OLED_ShowChinese(1, 3, 16);	
	OLED_ShowChinese(1, 4, 28);
	OLED_ShowChinese(1, 5, 29);	
	OLED_ShowChar(1, 11, ':');
	
	//��ʾ��������̼����
	OLED_ShowChinese(2, 2, 24);
	OLED_ShowChinese(2, 3, 25);
	OLED_ShowChinese(2, 4, 26);
	OLED_ShowChinese(2, 5, 27);
	OLED_ShowChar(2, 11, ':');	
}

/**
  * @brief  ��ʾ��ֵ����1�Ĵ���������
  * @param  ��
  * @retval ��
  */
void settingsThresholdDisplay1(void)
{
	//��ʾ�����¶���ֵ����
	OLED_ShowNum(1, 13, Sensorthreshold.tempValue, 2);
	
	//��ʾ����ʪ����ֵ����
	OLED_ShowNum(2, 13, Sensorthreshold.humiValue, 2);
	
	//��ʾ�����¶���ֵ����
	OLED_ShowNum(3, 13, Sensorthreshold.soilTempValue, 2);
	
	//��ʾ����ʪ����ֵ����
	OLED_ShowNum(4, 13, Sensorthreshold.soilHumiValue, 2);
}

/**
  * @brief  ��ʾ��ֵ����2�Ĵ���������
  * @param  ��
  * @retval ��
  */
void settingsThresholdDisplay2(void)
{
	//��ʾ����ǿ����ֵ����
	OLED_ShowNum(1, 13, Sensorthreshold.luxValue, 4);
	
	//��ʾCO2Ũ����ֵ����
	OLED_ShowNum(2, 13, Sensorthreshold.CO2Value, 4);
}

/**
  * @brief  ��ʾ��ֵ�����ѡ�����
  * @param  num Ϊ��ʾ��λ��
  * @retval ��
  */
void OLED_Option(uint8_t num)
{
	switch(num)
	{
		case 1:	
			OLED_ShowChar(1,1,'>');
			OLED_ShowChar(2,1,' ');
			OLED_ShowChar(3,1,' ');
			OLED_ShowChar(4,1,' ');
			break;
		case 2:	
			OLED_ShowChar(1,1,' ');
			OLED_ShowChar(2,1,'>');
			OLED_ShowChar(3,1,' ');
			OLED_ShowChar(4,1,' ');
			break;
		case 3:	
			OLED_ShowChar(1,1,' ');
			OLED_ShowChar(2,1,' ');
			OLED_ShowChar(3,1,'>');
			OLED_ShowChar(4,1,' ');
			break;
		case 4:	
			OLED_ShowChar(1,1,' ');
			OLED_ShowChar(2,1,' ');
			OLED_ShowChar(3,1,' ');
			OLED_ShowChar(4,1,'>');
			break;
		case 5:	
			OLED_ShowChar(1,1,'>');
			OLED_ShowChar(2,1,' ');
			OLED_ShowChar(3,1,' ');
			OLED_ShowChar(4,1,' ');
			break;
		case 6:	
			OLED_ShowChar(1,1,' ');
			OLED_ShowChar(2,1,'>');
			OLED_ShowChar(3,1,' ');
			OLED_ShowChar(4,1,' ');
			break;
		default: break;
	}
}

/**
  * @brief  ���ݱ�־λ���Ʋ������������
  * @param  ��
  * @retval ��
  */
void MotorOperation(void)
{
	if (motorFlag == 1)
	{
		MOTOR_Direction_Angle(1, 0, 90, 1);
		MOTOR_STOP();
		motorFlag = 0;
	}
	else if (motorFlag == 2)
	{
		MOTOR_Direction_Angle(0, 0, 90, 1);
		MOTOR_STOP();
		motorFlag = 0;		
	}

}

/**
  * @brief  ��¼��ֵ�����°�KEY1�Ĵ���
  * @param  ��
  * @retval ���ش���
  */
uint8_t SetSelection(void)
{
	static uint8_t count = 1;
	if(KeyNum == KEY_1)
	{
		KeyNum = 0;
		count++;
		if (count == 5)
		{
			OLED_Clear();
		}
		else if (count > 6)
		{
			OLED_Clear();
			count = 1;
		}
	}
	return count;
}

/**
  * @brief  ����ֵ����Ĵ�������ֵ�����޸�
  * @param  num Ϊ��ǰ�û���Ҫ���ĵĴ�������ֵλ��
  * @retval ��
  */
void ThresholdModification(uint8_t num)
{
	switch (num)
	{
		case 1:
			if (KeyNum == 3)
			{
				KeyNum = 0;
				Sensorthreshold.tempValue++;
				if (Sensorthreshold.tempValue > 99)
				{
					Sensorthreshold.tempValue = 1;
				}
			}
			else if (KeyNum == 4)
			{
				KeyNum = 0;
				Sensorthreshold.tempValue--;
				if (Sensorthreshold.tempValue < 1)
				{
					Sensorthreshold.tempValue = 99;
				}				
			}
			break;
		case 2:
			if (KeyNum == 3)
			{
				KeyNum = 0;
				Sensorthreshold.humiValue++;
				if (Sensorthreshold.humiValue > 99)
				{
					Sensorthreshold.humiValue = 1;
				}
			}
			else if (KeyNum == 4)
			{
				KeyNum = 0;
				Sensorthreshold.humiValue--;
				if (Sensorthreshold.humiValue < 1)
				{
					Sensorthreshold.humiValue = 99;
				}				
			}			
			break;
		case 3:
			if (KeyNum == 3)
			{
				KeyNum = 0;
				Sensorthreshold.soilTempValue++;
				if (Sensorthreshold.soilTempValue > 99)
				{
					Sensorthreshold.soilTempValue = 1;
				}
			}
			else if (KeyNum == 4)
			{
				KeyNum = 0;
				Sensorthreshold.soilTempValue--;
				if (Sensorthreshold.soilTempValue < 1)
				{
					Sensorthreshold.soilTempValue = 99;
				}				
			}
			break;
		case 4:
			if (KeyNum == 3)
			{
				KeyNum = 0;
				Sensorthreshold.soilHumiValue++;
				if (Sensorthreshold.soilHumiValue > 99)
				{
					Sensorthreshold.soilHumiValue = 1;
				}
			}
			else if (KeyNum == 4)
			{
				KeyNum = 0;
				Sensorthreshold.soilHumiValue--;
				if (Sensorthreshold.soilHumiValue < 1)
				{
					Sensorthreshold.soilHumiValue = 99;
				}				
			}
			break;
		case 5:
			if (KeyNum == 3)
			{
				KeyNum = 0;
				Sensorthreshold.luxValue += 10;
				if (Sensorthreshold.luxValue > 2000)
				{
					Sensorthreshold.luxValue = 0;
				}
			}
			else if (KeyNum == 4)
			{
				KeyNum = 0;
				Sensorthreshold.luxValue -= 10;
				if (Sensorthreshold.luxValue > 2000)
				{
					Sensorthreshold.luxValue = 2000;
				}				
			}			
			break;
		case 6:
			if (KeyNum == 3)
			{
				KeyNum = 0;
				Sensorthreshold.CO2Value += 10;
				if (Sensorthreshold.CO2Value > 2000)
				{
					Sensorthreshold.CO2Value = 0;
				}
			}
			else if (KeyNum == 4)
			{
				KeyNum = 0;
				Sensorthreshold.CO2Value -= 10;
				if (Sensorthreshold.CO2Value > 2000)
				{
					Sensorthreshold.CO2Value = 2000;
				}				
			}
			break;	
		default: break;		
	}
}

/**
  * @brief  ��ȡ������̼����
  * @param  *data Ϊ���ݴ���
  * @retval ��
  */
void CO2GetData(uint16_t *data)
{
	if (Usart3_RxFlag == 1)
	{
		Usart3_RxFlag = 0;
		*data = Usart3_RxPacket[1] * 256 + Usart3_RxPacket[2];
	}
}

/**
  * @brief  ����������ɨ��
  * @param  ��
  * @retval ��
  */
void SensorScan(void)
{
	DHT11_Read_Data(&sensorData.humi, &sensorData.temp);
	YL69_PercentageData(&sensorData.soilHumi);
	LDR_LuxData(&sensorData.lux);
	CO2GetData(&sensorData.CO2);
	DS18B20_Read_Temp(&sensorData.soilTemp);
}



int main(void)
{
	ADCX_Init();
	Timer2_Init(9,14398);
	Uart2_Init(9600);
	Uart1_Init(115200);
	Uart3_Init();
	IWDG_Init();	//��ʼ�����Ź�
	
	LDR_Init();
	YL69_Init();
	OLED_Init();
	DHT11_Init();
	LED_Init();
	Buzzer_Init();
	Relay_Init();
	MOTOR_Init();
	Key_Init();
	
	Sensorthreshold.CO2Value = FLASH_R(FLASH_START_ADDR);	//��ָ��ҳ�ĵ�ַ��FLASH
	Sensorthreshold.luxValue = FLASH_R(FLASH_START_ADDR+2);	//��ָ��ҳ�ĵ�ַ��FLASH
	Sensorthreshold.tempValue = FLASH_R(FLASH_START_ADDR+4);	//��ָ��ҳ�ĵ�ַ��FLASH
	Sensorthreshold.humiValue = FLASH_R(FLASH_START_ADDR+6);	//��ָ��ҳ�ĵ�ַ��FLASH
	Sensorthreshold.soilTempValue = FLASH_R(FLASH_START_ADDR+8);	//��ָ��ҳ�ĵ�ַ��FLASH
	Sensorthreshold.soilHumiValue = FLASH_R(FLASH_START_ADDR+10);	//��ָ��ҳ�ĵ�ַ��FLASH

	GENERAL_TIM_Init();
	userInit();		//��ɻ����Ƴ�ʼ��ֵ
	gizwitsInit();	//����һ�����λ�����
	
	while (1)
	{
		IWDG_ReloadCounter(); //���¼��ؼ���ֵ ι��
		SensorScan();	//��ȡ����������

		switch (menu)
		{
			case display_page1:
				SensorDataDisplay1();	//��ʾ������1����
				OLED_Menu1();	//��ʾ��ҳ��1�̶���Ϣ
			
				if (KeyNum == KEY_2)	//�Ƿ��°���2
				{
					KeyNum = 0;
					OLED_Clear();	//����
					menu = display_page2;	//menu = ��ҳ��2
				}
				MotorOperation();
				break;
				
			case display_page2:		
				SensorDataDisplay2();	//��ʾ������2����		
				OLED_Menu2();	//��ʾ��ҳ��2�̶���Ϣ
				if (KeyNum == KEY_2)	//�Ƿ��°���2
				{
					KeyNum = 0;
					OLED_Clear();	//����
					menu = display_page1;	//menu = ��ҳ��1
				}
				MotorOperation();
				break;
				
			case settingsPage:
				//����ҳ����ת������ҳ��ʱ����һ������
				if (OLED_Clear_Flag)
				{
					OLED_Clear_Flag = 0;	//���������־λ
					OLED_Clear();	//����
				}
				ThresholdModification(SetSelection());	//���ڴ�������ֵ
				
				OLED_Option(SetSelection());	//��ȡ�����������Ӷ��жϡ�>����ʾλ��
			
				//��������С�ڵ���4ʱ����ʾ����ҳ��1
				if (SetSelection() <= 4)		
				{
					settingsThresholdDisplay1();	//��ʾ��������ֵ1����	
					OLED_settingsPage1();	//��ʾ��ֵ���ý���1�̶���Ϣ

				}
				else	//������ʾ����ҳ��2
				{
					settingsThresholdDisplay2();	//��ʾ��������ֵ2����	
					OLED_settingsPage2();	//��ʾ��ֵ���ý���2�̶���Ϣ
				}
	
				if (KeyNum == KEY_2)	//�ж��û��Ƿ����˳�����
				{
					KeyNum = 0;
					OLED_Clear();	//����
					menu = display_page1;	//�ص���ҳ��1
					

					//�洢�޸ĵĴ�������ֵ��flash��
					FLASH_W(FLASH_START_ADDR, Sensorthreshold.CO2Value, Sensorthreshold.luxValue,
							Sensorthreshold.tempValue, Sensorthreshold.humiValue,
							Sensorthreshold.soilTempValue, Sensorthreshold.soilHumiValue);
				}
				break;
			default: break;
		}
		userHandle();	//���»��������ݵ�����洢��ֵ
		gizwitsHandle((dataPoint_t *)&currentDataPoint);	//�����ϴ���������					
	}
}
