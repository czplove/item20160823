/*******************************************************************************
* �ļ����ƣ�GPIO_Control.c
* �ļ����������ļ������к����ͺ궨�����ڶ�EM357��GPIO�ڽ��п���
* �����Ա��������
* ������ڣ�20140609
* �޸ļ�¼��
*******************************************************************************/
#include "GPIO_Control.h"

/*******************************************************************************
* �������ƣ�GPIO_A_MODE_SET
* ������������������PA�����ܽŵ�����/���ģʽ
* ���������1.GPIO_ID ��GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						ʹ��ʱ����ʹ�÷��š�|������һ�������ö���ܽ�  
			2.GPIO_MODE��GPIOCFG_OUT          //�������
   						 GPIOCFG_OUT_OD      //©����·���
   						 GPIOCFG_OUT_ALT     //������������
  						 GPIOCFG_OUT_ALT_OD   //����Ŀ�©���
  						 GPIOCFG_ANALOG    //ģ���źţ��������ź�Ϊ1
  						 GPIOCFG_IN       //��������
 						 GPIOCFG_IN_PUD     //���룺������������д1��������д0������
* �����������
* ע�������
*******************************************************************************/
void GPIO_A_MODE_SET(int32u GPIO_ID,int32u GPIO_MODE)
{
	int8u i;
	int16u GPIO_ID_Temp = GPIO_ID;
	
	for(i=0; i<16; i++)
	{
		if(GPIO_ID_Temp & 0x0001) GPIO_ID = 0x0001 << i;
		GPIO_ID_Temp >> 1;
		switch((int16u)GPIO_ID)
		{
			case 0x01:GPIO_PACFGL = (GPIO_PACFGL & (~PA0_CFG_MASK)) |(GPIO_MODE << 0);				
			break;
			case 0x02:GPIO_PACFGL = (GPIO_PACFGL & (~PA1_CFG_MASK)) |(GPIO_MODE << 4);				
			break;				
			case 0x04:GPIO_PACFGL = (GPIO_PACFGL & (~PA2_CFG_MASK)) |(GPIO_MODE << 8);				
			break;
			case 0x08:GPIO_PACFGL = (GPIO_PACFGL & (~PA3_CFG_MASK)) |(GPIO_MODE << 12);				
			break;		
			case 0x10:GPIO_PACFGH = (GPIO_PACFGH & (~PA4_CFG_MASK)) |(GPIO_MODE << 0);				
			break;
			case 0x20:GPIO_PACFGH = (GPIO_PACFGH & (~PA5_CFG_MASK)) |(GPIO_MODE << 4);				
			break;				
			case 0x40:GPIO_PACFGH = (GPIO_PACFGH & (~PA6_CFG_MASK)) |(GPIO_MODE << 8);				
			break;
			case 0x80:GPIO_PACFGH = (GPIO_PACFGH & (~PA7_CFG_MASK)) |(GPIO_MODE << 12);				
			break;	
			default:
			break;
		}
	}
}

/*******************************************************************************
* �������ƣ�GPIO_B_MODE_SET
* ������������������PB�����ܽŵ�����/���ģʽ
* ���������1.GPIO_ID ��GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						ʹ��ʱ����ʹ�÷��š�|������һ�������ö���ܽ�  
			2.GPIO_MODE��GPIOCFG_OUT          //�������
   						 GPIOCFG_OUT_OD      //©����·���
   						 GPIOCFG_OUT_ALT     //������������
  						 GPIOCFG_OUT_ALT_OD   //����Ŀ�©���
  						 GPIOCFG_ANALOG    //ģ���źţ��������ź�Ϊ1
  						 GPIOCFG_IN       //��������
 						 GPIOCFG_IN_PUD     //���룺������������д1��������д0������
* �����������
* ע�������
*******************************************************************************/
void GPIO_B_MODE_SET(int32u GPIO_ID,int32u GPIO_MODE)
{
	int8u i;
	int16u GPIO_ID_Temp = GPIO_ID;
	
	for(i=0; i<16; i++)
	{
		if(GPIO_ID_Temp & 0x0001) GPIO_ID = 0x0001 << i;
		GPIO_ID_Temp >> 1;

		switch((int16u)GPIO_ID)
		{
			case 0x01:GPIO_PBCFGL = (GPIO_PBCFGL & (~PB0_CFG_MASK)) |(GPIO_MODE << 0);				
			break;
			case 0x02:GPIO_PBCFGL = (GPIO_PBCFGL & (~PB1_CFG_MASK)) |(GPIO_MODE << 4);				
			break;				
			case 0x04:GPIO_PBCFGL = (GPIO_PBCFGL & (~PB2_CFG_MASK)) |(GPIO_MODE << 8);				
			break;
			case 0x08:GPIO_PBCFGL = (GPIO_PBCFGL & (~PB3_CFG_MASK)) |(GPIO_MODE << 12);				
			break;		
			case 0x10:GPIO_PBCFGH = (GPIO_PBCFGH & (~PB4_CFG_MASK)) |(GPIO_MODE << 0);				
			break;
			case 0x20:GPIO_PBCFGH = (GPIO_PBCFGH & (~PB5_CFG_MASK)) |(GPIO_MODE << 4);				
			break;				
			case 0x40:GPIO_PBCFGH = (GPIO_PBCFGH & (~PB6_CFG_MASK)) |(GPIO_MODE << 8);				
			break;
			case 0x80:GPIO_PBCFGH = (GPIO_PBCFGH & (~PB7_CFG_MASK)) |(GPIO_MODE << 12);				
			break;	
			default:
			break;
		}
	}
}


/*******************************************************************************
* �������ƣ�GPIO_C_MODE_SET
* ������������������PA�����ܽŵ�����/���ģʽ
* ���������1.GPIO_ID ��GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						ʹ��ʱ����ʹ�÷��š�|������һ�������ö���ܽ�  
			2.GPIO_MODE��GPIOCFG_OUT          //�������
   						 GPIOCFG_OUT_OD      //©����·���
   						 GPIOCFG_OUT_ALT     //������������
  						 GPIOCFG_OUT_ALT_OD   //����Ŀ�©���
  						 GPIOCFG_ANALOG    //ģ���źţ��������ź�Ϊ1
  						 GPIOCFG_IN       //��������
 						 GPIOCFG_IN_PUD     //���룺������������д1��������д0������
* �����������
* ע�������
*******************************************************************************/
void GPIO_C_MODE_SET(int32u GPIO_ID,int32u GPIO_MODE)
{
	int8u i;
	int16u GPIO_ID_Temp = GPIO_ID;
	
	for(i=0; i<16; i++)
	{
		if(GPIO_ID_Temp & 0x0001) GPIO_ID = 0x0001 << i;
		GPIO_ID_Temp >> 1;

		switch((int16u)GPIO_ID)
		{
			case 0x01:GPIO_PCCFGL = (GPIO_PCCFGL & (~PC0_CFG_MASK)) |(GPIO_MODE << 0);				
			break;
			case 0x02:GPIO_PCCFGL = (GPIO_PCCFGL & (~PC1_CFG_MASK)) |(GPIO_MODE << 4);				
			break;				
			case 0x04:GPIO_PCCFGL = (GPIO_PCCFGL & (~PC2_CFG_MASK)) |(GPIO_MODE << 8);				
			break;
			case 0x08:GPIO_PCCFGL = (GPIO_PCCFGL & (~PC3_CFG_MASK)) |(GPIO_MODE << 12);				
			break;		
			case 0x10:GPIO_PCCFGH = (GPIO_PCCFGH & (~PC4_CFG_MASK)) |(GPIO_MODE << 0);				
			break;
			case 0x20:GPIO_PCCFGH = (GPIO_PCCFGH & (~PC5_CFG_MASK)) |(GPIO_MODE << 4);				
			break;				
			case 0x40:GPIO_PCCFGH = (GPIO_PCCFGH & (~PC6_CFG_MASK)) |(GPIO_MODE << 8);				
			break;
			case 0x80:GPIO_PCCFGH = (GPIO_PCCFGH & (~PC7_CFG_MASK)) |(GPIO_MODE << 12);				
			break;	
			default:
			break;
		}
	}
}
/*******************************************************************************
* �������ƣ�GPIO_A_READ
* ������������ȡPA��ָ���ܽŵ�����ֵ
* ���������1.GPIO_ID ��GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						GPIO_PINS_ALL
* ���������ָ���ܽŵ�״ֵ̬��1��0��
* ע�����ÿ�ζ�ȡֻ�ܶ�ȡһ���ܽŵ���ֵ,���߶�ȡȫ���ܽŵ�ֵ
*******************************************************************************/
int8u GPIO_A_READ(int32u GPIO_ID) 
{
	if(GPIO_ID == 0xff)//��ȡȫ���ܽŵ�����
	{	
		return(GPIO_PAIN & (int16u)GPIO_ID);
	}
	else
	{
		if(GPIO_PAIN & (int16u)GPIO_ID) return 1;
		else return 0;		
	}
}
/*******************************************************************************
* �������ƣ�GPIO_B_READ
* ������������ȡPB��ָ���ܽŵ�����ֵ
* ���������1.GPIO_ID ��GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						GPIO_PINS_ALL
* ���������ָ���ܽŵ�״ֵ̬��1��0��
* ע�����ÿ�ζ�ȡֻ�ܶ�ȡһ���ܽŵ���ֵ,���߶�ȡȫ���ܽŵ�ֵ
*******************************************************************************/
int8u GPIO_B_READ(int32u GPIO_ID) 
{
	if(GPIO_ID == 0xff)//��ȡȫ���ܽŵ�����
	{	
		return(GPIO_PBIN & (int16u)GPIO_ID);
	}
	else
	{
		if(GPIO_PBIN & (int16u)GPIO_ID) return 1;
		else return 0;		
	}
}
/*******************************************************************************
* �������ƣ�GPIO_C_READ
* ������������ȡPC��ָ���ܽŵ�����ֵ
* ���������1.GPIO_ID ��GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						GPIO_PINS_ALL
* ���������ָ���ܽŵ�״ֵ̬��1��0��
* ע�����ÿ�ζ�ȡֻ�ܶ�ȡһ���ܽŵ���ֵ,���߶�ȡȫ���ܽŵ�ֵ
*******************************************************************************/
int8u GPIO_C_READ(int32u GPIO_ID) 
{
	if(GPIO_ID == 0xff)//��ȡȫ���ܽŵ�����
	{	
		return(GPIO_PCIN & (int16u)GPIO_ID);
	}
	else
	{
		if(GPIO_PCIN & (int16u)GPIO_ID) return 1;
		else return 0;		
	}
}














