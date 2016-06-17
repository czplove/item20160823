/*******************************************************************************
* 文件名称：GPIO_Control.c
* 文件描述：此文件中所有函数和宏定义用于对EM357的GPIO口进行控制
* 设计人员：于明正
* 设计日期：20140609
* 修改记录：
*******************************************************************************/
#include "GPIO_Control.h"

/*******************************************************************************
* 函数名称：GPIO_A_MODE_SET
* 功能描述：用于配置PA各个管脚的输入/输出模式
* 输入参数：1.GPIO_ID ：GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						使用时可以使用符号“|”用于一次性配置多个管脚  
			2.GPIO_MODE：GPIOCFG_OUT          //推挽输出
   						 GPIOCFG_OUT_OD      //漏极开路输出
   						 GPIOCFG_OUT_ALT     //交替的推挽输出
  						 GPIOCFG_OUT_ALT_OD   //交替的开漏输出
  						 GPIOCFG_ANALOG    //模拟信号，读到的信号为1
  						 GPIOCFG_IN       //浮空输入
 						 GPIOCFG_IN_PUD     //输入：上拉或下拉，写1：上拉；写0：下拉
* 输出参数：无
* 注意事项：无
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
* 函数名称：GPIO_B_MODE_SET
* 功能描述：用于配置PB各个管脚的输入/输出模式
* 输入参数：1.GPIO_ID ：GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						使用时可以使用符号“|”用于一次性配置多个管脚  
			2.GPIO_MODE：GPIOCFG_OUT          //推挽输出
   						 GPIOCFG_OUT_OD      //漏极开路输出
   						 GPIOCFG_OUT_ALT     //交替的推挽输出
  						 GPIOCFG_OUT_ALT_OD   //交替的开漏输出
  						 GPIOCFG_ANALOG    //模拟信号，读到的信号为1
  						 GPIOCFG_IN       //浮空输入
 						 GPIOCFG_IN_PUD     //输入：上拉或下拉，写1：上拉；写0：下拉
* 输出参数：无
* 注意事项：无
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
* 函数名称：GPIO_C_MODE_SET
* 功能描述：用于配置PA各个管脚的输入/输出模式
* 输入参数：1.GPIO_ID ：GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						使用时可以使用符号“|”用于一次性配置多个管脚  
			2.GPIO_MODE：GPIOCFG_OUT          //推挽输出
   						 GPIOCFG_OUT_OD      //漏极开路输出
   						 GPIOCFG_OUT_ALT     //交替的推挽输出
  						 GPIOCFG_OUT_ALT_OD   //交替的开漏输出
  						 GPIOCFG_ANALOG    //模拟信号，读到的信号为1
  						 GPIOCFG_IN       //浮空输入
 						 GPIOCFG_IN_PUD     //输入：上拉或下拉，写1：上拉；写0：下拉
* 输出参数：无
* 注意事项：无
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
* 函数名称：GPIO_A_READ
* 功能描述：读取PA中指定管脚的输入值
* 输入参数：1.GPIO_ID ：GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						GPIO_PINS_ALL
* 输出参数：指定管脚的状态值，1或0；
* 注意事项：每次读取只能读取一个管脚的数值,或者读取全部管脚的值
*******************************************************************************/
int8u GPIO_A_READ(int32u GPIO_ID) 
{
	if(GPIO_ID == 0xff)//读取全部管脚的数据
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
* 函数名称：GPIO_B_READ
* 功能描述：读取PB中指定管脚的输入值
* 输入参数：1.GPIO_ID ：GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						GPIO_PINS_ALL
* 输出参数：指定管脚的状态值，1或0；
* 注意事项：每次读取只能读取一个管脚的数值,或者读取全部管脚的值
*******************************************************************************/
int8u GPIO_B_READ(int32u GPIO_ID) 
{
	if(GPIO_ID == 0xff)//读取全部管脚的数据
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
* 函数名称：GPIO_C_READ
* 功能描述：读取PC中指定管脚的输入值
* 输入参数：1.GPIO_ID ：GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						GPIO_PINS_ALL
* 输出参数：指定管脚的状态值，1或0；
* 注意事项：每次读取只能读取一个管脚的数值,或者读取全部管脚的值
*******************************************************************************/
int8u GPIO_C_READ(int32u GPIO_ID) 
{
	if(GPIO_ID == 0xff)//读取全部管脚的数据
	{	
		return(GPIO_PCIN & (int16u)GPIO_ID);
	}
	else
	{
		if(GPIO_PCIN & (int16u)GPIO_ID) return 1;
		else return 0;		
	}
}














