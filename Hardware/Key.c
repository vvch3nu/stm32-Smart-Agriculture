#include "key.h"

u8 key1_long_flag,key2_long_flag,key3_long_flag,key4_long_flag;
u8 key1_lock_flag,key2_lock_flag,key3_lock_flag,key4_lock_flag;
u16 key1_cnt,key2_cnt,key3_cnt,key4_cnt;
u16 key1_cnt2,key2_cnt2,key3_cnt2,key4_cnt2;
u8 key1_lock_flag,key2_lock_flag,key3_lock_flag,key4_lock_flag;
u8 key2_long_flag;



u8 KeyNum = 0;
/**
  * @brief  Key��ʼ��
  * @param  ��
  * @retval ��
  */
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN | KEY2_GPIO_PIN | KEY3_GPIO_PIN | KEY4_GPIO_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY_PROT, &GPIO_InitStructure);
}

/**
  * @brief  Key��ֵ��ȡ
  * @param  ��
  * @retval ���ش��������ļ�ֵ
  */
void Key_scan(void)
{
	if(KEY1) //���û�а�������
	{
		key1_lock_flag = 0; //����������־
		key1_cnt = 0; //���������־
		if(key1_long_flag)
		{
			key1_long_flag = 0;	//���㳤����־λ
			KeyNum = 11; //����ֵ���� ������ֵ����
		}
	}
	else if(!key1_lock_flag)
	{
		key1_cnt++; //�ۼư���������ʱ����
		if(key1_cnt > KEY_DELAY_TIME)
		{
			key1_cnt = 0; //���������־
			KeyNum = 1; //����ֵ���� �̰���ֵ����
			key1_lock_flag = 1; //������־��1 ��ֹ��δ���
		}
	}
	else if(key1_cnt < KEY_Continue_TIME)
	{
		key1_cnt++;	//�ۼư����������ܴ���ʱ��
	}
	else
	{
		key1_cnt++;	//�ۼư�������������ʱʱ��
		key1_cnt2++;	//�ۼư������������ӳ�ʱ��
		if(key1_cnt2 > KEY_Continue_Trigger_TIME)
		{
			key1_cnt2 = 0;	//���������ӳ�ʱ��
			KeyNum = 1;	//�����������ֵ
		}
		if(key1_cnt > KEY_LONG_TIME)
		{
			key1_long_flag = 1;	//��������־λ
		}
	
	}
	
	if(KEY2) //���û�а�������
	{
		key2_lock_flag = 0; //����������־
		key2_cnt = 0; //���������־
		if(key2_long_flag)
		{
			key2_long_flag = 0;	//���㳤����־λ
			KeyNum = 22; //����ֵ���� ������ֵ����
		}
	}
	else if(!key2_lock_flag)
	{
		key2_cnt++; //�ۼư���������ʱ����
		if(key2_cnt > KEY_DELAY_TIME)
		{
			key2_cnt = 0; //���������־
			KeyNum = 2; //����ֵ���� �̰���ֵ����
			key2_lock_flag = 1; //������־��1 ��ֹ��δ���
		}
	}
	else if(key2_cnt < KEY_Continue_TIME)
	{
		key2_cnt++;	//�ۼư����������ܴ���ʱ��
	}
	else
	{
		key2_cnt++;	//�ۼư�������������ʱʱ��
		key2_cnt2++;	//�ۼư������������ӳ�ʱ��
		if(key2_cnt2 > KEY_Continue_Trigger_TIME)
		{
			key2_cnt2 = 0;	//���������ӳ�ʱ��
			KeyNum = 2;	//�����������ֵ
		}
		if(key2_cnt > KEY_LONG_TIME)
		{
			key2_long_flag = 1;	//��������־λ
		}
	}
	
	if(KEY3) //���û�а�������
	{
		key3_lock_flag = 0; //����������־
		key3_cnt = 0; //���������־
		if(key3_long_flag)
		{
			key3_long_flag = 0;	//���㳤����־λ
			KeyNum = 33; //����ֵ���� ������ֵ����
		}
	}
	else if(!key3_lock_flag)
	{
		key3_cnt++; //�ۼư���������ʱ����
		if(key3_cnt > KEY_DELAY_TIME)
		{
			key3_cnt = 0; //���������־
			KeyNum = 3; //����ֵ���� �̰���ֵ����
			key3_lock_flag = 1; //������־��1 ��ֹ��δ���
		}
	}
	else if(key3_cnt < KEY_Continue_TIME)
	{
		key3_cnt++;	//�ۼư����������ܴ���ʱ��
	}
	else
	{
		key3_cnt++;	//�ۼư�������������ʱʱ��
		key3_cnt2++;	//�ۼư������������ӳ�ʱ��
		if(key3_cnt2 > KEY_Continue_Trigger_TIME)
		{
			key3_cnt2 = 0;	//���������ӳ�ʱ��
			KeyNum = 3;	//�����������ֵ
		}
		if(key3_cnt > KEY_LONG_TIME)
		{
			key3_long_flag = 1;	//��������־λ
		}
	
	}
	
	if(KEY4) //���û�а�������
	{
		key4_lock_flag = 0; //����������־
		key4_cnt = 0; //���������־
		if(key4_long_flag)
		{
			key4_long_flag = 0;	//���㳤����־λ
			KeyNum = 44; //����ֵ���� ������ֵ����
		}
	}
	else if(!key4_lock_flag)
	{
		key4_cnt++; //�ۼư���������ʱ����
		if(key4_cnt > KEY_DELAY_TIME)
		{
			key4_cnt = 0; //���������־
			KeyNum = 4; //����ֵ���� �̰���ֵ����
			key4_lock_flag = 1; //������־��1 ��ֹ��δ���
		}
	}
	else if(key4_cnt < KEY_Continue_TIME)
	{
		key4_cnt++;	//�ۼư����������ܴ���ʱ��
	}
	else
	{
		key4_cnt++;	//�ۼư�������������ʱʱ��
		key4_cnt2++;	//�ۼư������������ӳ�ʱ��
		if(key4_cnt2 > KEY_Continue_Trigger_TIME)
		{
			key4_cnt2 = 0;	//���������ӳ�ʱ��
			KeyNum = 4;	//�����������ֵ
		}
		if(key4_cnt > KEY_LONG_TIME)
		{
			key4_long_flag = 1;	//��������־λ
		}
	
	}
}


