/*******************************************************************************
* 文件名称：GPIO_Control.h
* 文件描述：此文件中所有函数和宏定义用于对EM357的GPIO口进行控制
* 设计人员：于明正
* 设计日期：20140609
* 修改记录：
*******************************************************************************/
#ifndef _GPIO_CONTROL_H
#define _GPIO_CONTROL_H

#include "app/framework/include/af.h"
//允许使用的管脚模式有：
/*
   GPIOCFG_OUT          //推挽输出
   GPIOCFG_OUT_OD      //漏极开路输出
   GPIOCFG_OUT_ALT     //交替的推挽输出
  GPIOCFG_OUT_ALT_OD   //交替的开漏输出
  GPIOCFG_ANALOG    //模拟信号，读到的信号为1
  GPIOCFG_IN       //浮空输入
 GPIOCFG_IN_PUD     //输入：上拉或下拉，写1：上拉；写0：下拉
*/

//允许使用的管脚定义如下--------------------------------------------------------
#define GPIO_PIN_7 (0x00000080u)
#define GPIO_PIN_6 (0x00000040u)
#define GPIO_PIN_5 (0x00000020u)
#define GPIO_PIN_4 (0x00000010u)
#define GPIO_PIN_3 (0x00000008u)
#define GPIO_PIN_2 (0x00000004u)
#define GPIO_PIN_1 (0x00000002u)
#define GPIO_PIN_0 (0x00000001u)

#define GPIO_PINS_ALL 0x00ff

/*******************************************************************************
* 函数名称：GPIO_A_SET
* 功能描述：设定PA指定管脚的输出值为1
* 输入参数：1.GPIO_ID ：GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						GPIO_PINS_ALL
* 输出参数：无
* 注意事项：可以使用"|"用于同时设置几个管脚
*******************************************************************************/
#define  GPIO_A_SET(GPIO_ID) 		 GPIO_PASET |= (int16u)GPIO_ID	
/*******************************************************************************
* 函数名称：GPIO_B_SET
* 功能描述：设定PB指定管脚的输出值为1
* 输入参数：1.GPIO_ID ：GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						GPIO_PINS_ALL
* 输出参数：无
* 注意事项：可以使用"|"用于同时设置几个管脚
*******************************************************************************/
#define  GPIO_B_SET(GPIO_ID) 		 GPIO_PBSET |= (int16u)GPIO_ID	
/*******************************************************************************
* 函数名称：GPIO_C_SET
* 功能描述：设定PC指定管脚的输出值为1
* 输入参数：1.GPIO_ID ：GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						GPIO_PINS_ALL
* 输出参数：无
* 注意事项：可以使用"|"用于同时设置几个管脚
*******************************************************************************/
#define  GPIO_C_SET(GPIO_ID) 		 GPIO_PCSET |= (int16u)GPIO_ID		

/*******************************************************************************
* 函数名称：GPIO_A_CLR
* 功能描述：设定PA指定管脚的输出值为0
* 输入参数：1.GPIO_ID ：GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						GPIO_PINS_ALL
* 输出参数：无
* 注意事项：可以使用"|"用于同时设置几个管脚
*******************************************************************************/
#define GPIO_A_CLR(GPIO_ID)          GPIO_PACLR |= GPIO_ID
/*******************************************************************************
* 函数名称：GPIO_B_CLR
* 功能描述：设定PB指定管脚的输出值为0
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
* 注意事项：可以使用"|"用于同时设置几个管脚
*******************************************************************************/
#define GPIO_B_CLR(GPIO_ID)          GPIO_PBCLR |= GPIO_ID
/*******************************************************************************
* 函数名称：GPIO_C_CLR
* 功能描述：设定PC指定管脚的输出值为0
* 输入参数：1.GPIO_ID ：GPIO_PIN_7 
						GPIO_PIN_6 
						GPIO_PIN_5 
						GPIO_PIN_4 
						GPIO_PIN_3 
						GPIO_PIN_2 
						GPIO_PIN_1 
						GPIO_PIN_0 
						GPIO_PINS_ALL
* 输出参数：无
* 注意事项：可以使用"|"用于同时设置几个管脚
*******************************************************************************/
#define GPIO_C_CLR(GPIO_ID)          GPIO_PCCLR |= GPIO_ID

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
int8u GPIO_A_READ(int32u GPIO_ID);

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
int8u GPIO_B_READ(int32u GPIO_ID);

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
int8u GPIO_C_READ(int32u GPIO_ID);

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
void GPIO_A_MODE_SET(int32u GPIO_ID,int32u GPIO_MODE);
/*******************************************************************************
* 函数名称：GPIO_B_MODE_SET
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
void GPIO_B_MODE_SET(int32u GPIO_ID,int32u GPIO_MODE);
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
void GPIO_C_MODE_SET(int32u GPIO_ID,int32u GPIO_MODE);

#endif
