/**
  ******************************************************************************
  * @file    E93196.h
  * @author  Wireless Protocol Stack Develop-Dept.
  * @version 
  * @date    
  * @brief  
  *
  * @verbatim  
  *
  ******************************************************************************
  * @attention
  *     
  *     
  *
  * <h2><center>&copy; COPYRIGHT 2015 WuLianGroup</center></h2>
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#include "app/framework/include/af.h"

#ifndef __E93196_H
#define __E93196_H

/* Includes ------------------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/
typedef struct {
    uint8_t Sensitivity;
    uint8_t BlindTime:4;
    uint8_t PulseCounter:2;
    uint8_t WindowTime:2;
    uint8_t MotionDetect:1;
    uint8_t InterruptSource:1;
    uint8_t ADCVoltageSource:2;
    uint8_t SupplyRegulator:1;
    uint8_t StartSelfTest:1;
    uint8_t SampleCapacitor:1;
    uint8_t UserTestModes:2;
 }E93196Cfg_t;


typedef struct{
  uint8_t Sensitivity;
  uint8_t BlindTime;
  uint8_t PulseCounter;
  uint8_t WindowTime;
}E93196Cmd_t;
/**
  * @brief Supply Regulator Enable  and  Start Self-Test
  */
typedef enum{
  Enable                = 0 ,
  Disable               = 1
}SupplyRegulator_t ,StartSelfTest_t;
/**
  * @brief Motion Detect Enable
  */
typedef enum{
  MotionEnable          = 1 ,
  MotionDisable         = 0
} MotionDetect_t;

/**
  * @brief Interrupt Source
  */
typedef enum{
  InterruptSource_Motion      = 0,                   /*!<ѡ���ж�ԴΪ�˶����  */
  InterruptSource_Filter      = 1                    /*!<ѡ���ж�ԴΪ�˲���  */
} InterruptSource_t;

/**
  * @brief  ADC Input Source
  */
typedef enum{
  ADCInputSource_BPF        = 0,                         /*!< BPFģʽ         */
  ADCInputSource_LPF        = 1,                         /*!< LPFģʽ         */
  ADCInputSource_SUPPLY     = 2,                         /*!< SUPPLYģʽ      */
  ADCInputSource_TEMP       = 3                          /*!< TEMPģʽ        */
} ADCInputSource_t;
/**
  * @brief E93196 Configure Command
  */
typedef enum{
  Set_Empty                     = 0x00,
  Set_Sensitivity               = 0x01,                 /*!< ����������      */
  Set_BlindTime                 = 0x02,                 /*!< ����ä��ʱ��    */
  Set_PulseCounter              = 0x03,                 /*!< �����������    */
  Set_WindowTime                = 0x04,                 /*!< ���ô���ʱ��    */
  Set_MotionDetect              = 0x05,                 /*!< �˶����ʹ��    */
  Set_InterruptSource           = 0x06,                 /*!< �ж�Դѡ��      */
  Set_ADCVoltageSource          = 0x07,                 /*!< ADC����Դѡ��   */
  Set_SupplyRegulator           = 0x08,                 /*!< ���ù����ѹ    */
  Set_StartSelfTest             = 0x09,                 /*!< �����Բ�ģʽ    */
  Set_SampleCapacitor           = 0x0A,                 /*!< ���ò�������    */
  Set_UserTestModes             = 0x0B
}ConfigureE93196Cmd_t;
/* Exported constants --------------------------------------------------------*/
/**
  * @brief Sensitivity Configure
  */
#define SensitivityThreshold_104uV              0x10
#define SensitivityThreshold_208uV              0x20
#define SensitivityThreshold_416uV              0x30
#define SensitivityThreshold_832uV              0x40
#define SensitivityThreshold_1664uV             0x50
#define SensitivityThreshold_3328uV             0x60
#define SensitivityThreshold_6656uV             0x70
#define SensitivityThreshold_13312uV            0x80
#define SensitivityThreshold_26624uV            0x90
#define SensitivityThreshold_53248uV            0xA0
#define SensitivityThreshold_106496uV           0xB0
#define SensitivityThreshold_212992uV           0xC0
#define SensitivityThreshold_425984uV           0xD0
#define SensitivityThreshold_851968uV           0xE0
#define SensitivityThreshold_1703936uV          0xF0
/**
  * @brief Blind Time Configure
  */
#define BlindTime_0_5S                          0x00
#define BlindTime_1S                            0x01
#define BlindTime_1_5S                          0x02
#define BlindTime_2S                            0x03
#define BlindTime_2_5S                          0x04
#define BlindTime_3S                            0x05
#define BlindTime_3_5S                          0x06
#define BlindTime_4S                            0x07
#define BlindTime_4_5S                          0x08
#define BlindTime_5S                            0x09
#define BlindTime_5_5S                          0x0A
#define BlindTime_6S                            0x0B
#define BlindTime_6_5S                          0x0C
#define BlindTime_7S                            0x0D
#define BlindTime_7_5S                          0x0E
#define BlindTime_8S                            0x0F
/**
  * @brief Pulse Counter Configure
  */
#define PulseCounter_1                          0x00
#define PulseCounter_2                          0x01
#define PulseCounter_3                          0x02
#define PulseCounter_4                          0x03
/**
  * @brief Window Time Configure
  */
#define WindowTime_4S                           0x00
#define WindowTime_8S                           0x01
#define WindowTime_12S                          0x02
#define WindowTime_16S                          0x03


/* ------------------E93196 Input/Output INT/DOCI----------*/

#define DOCI_INIT_IN()                  {GPIO_PBCFGL |=(GPIOCFG_IN  << PB3_CFG_BIT);}  /*!< DOCI��ʼ��Ϊ���� */
#define DOCI_INIT_OUT()                 {GPIO_PBCFGL |=(GPIOCFG_OUT << PB3_CFG_BIT);} /*!< DOCI��ʼ��Ϊ��� */
#define DOCI_ON()                       {GPIO_PBOUT  |=(1 <<PB3_BIT);}        /*!< DOCI����ߵ�ƽ */
#define DOCI_OFF()                      {GPIO_PBOUT  &=~(1 <<PB3_BIT);}        /*!< DOCI����͵�ƽ */
#define DOCI_PULLUP()                   \
{                                                                              \
                                        GPIO_PBCFGL |=(GPIOCFG_IN_PUD << PB3_CFG_BIT);          /*!< DOCI�������� */\
                                        (GPIOOUT_PULLUP   <<PB3_BIT);          \
}
#define DOCI_PULLDOWN()                 \
{                                                                              \
                                        GPIO_PBCFGL |=(GPIOCFG_IN_PUD << PB3_CFG_BIT);          /*!< DOCI��������*/\
                                        (GPIOOUT_PULLDOWN   <<PB3_BIT);        \
                                        }
#define DOCI_3STATE()                   {GPIO_PBCFGL |=(GPIOCFG_IN  << PB3_CFG_BIT);}         /*!< DOCI 3-state����*/

#define DOCI_ENABLE_INTERRUPT()         {INT_CFGSET = INT_IRQC;}    /*!< ʹ��DOCI�����ж�*/
#define DOCI_DISABLE_INTERRUPT()        {INT_CFGCLR = INT_IRQC;}    /*!< ��ֹDOCI�����ж�*/

/* ------------------E93196 Input SERIN----------------------*/
#define SERIN_INIT_IN()                 {GPIO_PCCFGL |=(GPIOCFG_IN << PC1_CFG_BIT);}       /*!< SERIN��ʼ��Ϊ���� */
#define SERIN_INIT_OUT()                {GPIO_PCCFGL |=(GPIOCFG_OUT<< PC1_CFG_BIT);}       /*!< SERIN��ʼ��Ϊ��� */
#define SERIN_ON()                      {GPIO_PCOUT  |=(1 <<PC1_BIT);}      /*!< SERIN����ߵ�ƽ */
#define SERIN_OFF()                     {GPIO_PCOUT  &=~(1 <<PC1_BIT);}      /*!< SERIN����͵�ƽ */
                                        
#define DOCI_SEL()       do {GPIO_IRQCSEL = PORTB_PIN(3);} while(0)


//#define WAIT_FOR_4_5US                  1
//#define WAIT_FOR_100US                  40
#define WAIT_FOR_4_5US                  3
#define WAIT_FOR_100US                  55                                        
#define WAIT_FOR_150US                  60
#define WAIT_FOR_600US                  240
/* Exported variables --------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void ConfigE93196Cfg(E93196Cmd_t *pCmd);

void PIR_ChgDefenceCfg(E93196Cmd_t *pCmd);

void InitE93196Interrupt(void);

void SetE93196Config(void);
/*  Configure the IO of  CC2530 for E93196  *****/
void InitE93196_IO(void);

void ClearE93196Interrupt(void);

void ProcessDOCIInterrupt(void);
/*  Read the pin level *****/
uint8_t ReadIntputBit(uint8_t PORT, uint8_t PIN);
/*  Read num  bytes data from registers of E93196 Controller Integrated Circuit *****/
void ReadE93196(uint8_t *ptr,uint8_t num);
/*  write 25 bytes data into registers of E93196 Controller Integrated Circuit *****/
void WriteE93196(uint8_t*ptr);

void WriteE93196Cfg(E93196Cfg_t* pCfg);

void PIR_ClearDefence(void);

void PIR_SetDefence(void);


#endif /* _E93196.h_H */
/******************* (C) COPYRIGHT 2015 WuLianGroup ********END OF FIL*********/
