/**
  ******************************************************************************
  * @file    E93196.c
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
  
/* Includes ------------------------------------------------------------------*/
#include "E93196.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/ 

E93196Cfg_t  E93196Cfg;
E93196Cmd_t  E93196DefaultCmd={0x40,0x0a,0x02,0x40};

/* Private function prototypes -----------------------------------------------*/  
static void Delay (uint16_t usec);
static unsigned char pHeader[25]={0};
/* Private functions ---------------------------------------------------------*/

void PIR_ChgDefenceCfg(E93196Cmd_t *pCmd)
{
  InitE93196_IO();
  /* ��ʼ��E931.96�����жϣ���ʹ��P0.4/INT_DOCI�����ж�*/
  InitE93196Interrupt();

  /* ���ù���ģʽ*/
  ConfigE93196Cfg(pCmd);

  DOCI_ENABLE_INTERRUPT();
  /*�����ȷ���ж�״̬*/
  ClearE93196Interrupt();

}


/**
  * @brief
  * @param  None
  * @retval None
  */
void InitE93196Interrupt(void)
{
  GPIO_INTCFGC = 0;                //disable interrupt
  INT_CFGCLR = INT_IRQC;           //clear  top level int enable
  INT_GPIOFLAG = INT_IRQCFLAG;     //clear stale  interrupt
  INT_MISS = INT_MISSIRQC;         //clear stale missed interrupt
  
  DOCI_SEL();                      //point IRQ at the desired pin
  GPIO_INTCFGC = (0 << GPIO_INTFILT_BIT); //no filter
  GPIO_INTCFGC = (3 << GPIO_INTMOD_BIT);  //1 = Rising edge
  INT_CFGSET = INT_IRQC; //set top level interrupt enable
}

void ClearE93196Interrupt(void)
{
  DOCI_INIT_OUT();
  DOCI_ON();
  Delay(WAIT_FOR_4_5US);
  DOCI_OFF();
  Delay(WAIT_FOR_4_5US);
  DOCI_3STATE();
  DOCI_INIT_IN();
}
/**
  * @brief
  * @param  None
  * @retval None
  */
void ProcessDOCIInterrupt(void)
{
  /* ���E931.96�ж�״̬*/
  DOCI_INIT_OUT();
  DOCI_OFF();
  DOCI_INIT_IN();
  //DOCI_3STATE();
}

void SetE93196Config(void)
{
  E93196Cfg.Sensitivity = SensitivityThreshold_208uV;
  E93196Cfg.BlindTime = BlindTime_4S;
  E93196Cfg.PulseCounter = PulseCounter_2;
  E93196Cfg.WindowTime = WindowTime_4S;
  E93196Cfg.MotionDetect = MotionEnable;
  E93196Cfg.InterruptSource = InterruptSource_Motion;
  E93196Cfg.ADCVoltageSource = ADCInputSource_LPF;
  E93196Cfg.SupplyRegulator = Enable;
  E93196Cfg.StartSelfTest = Enable;
  E93196Cfg.SampleCapacitor = 1;
  WriteE93196Cfg(&E93196Cfg);
}

void WriteE93196Cfg(E93196Cfg_t* pCfg)
{
  unsigned char *pdata;
  char  i, tmp;
  pdata = pHeader;
  tmp = pCfg->Sensitivity;
  for (i = 0; i<8 ;++i)
  {
    if( 0x80 == (tmp & 0x80) ){
      *pdata++ = 1;
    }
    else {
      *pdata++ = 0;
    }
    tmp = tmp << 1;                      /* ����һλ */
  }

  tmp = pCfg->BlindTime;
  for (i = 8; i < 12; ++i)            /*  ����һλһλ����         */
  {
    if(0x08 == (tmp & 0x08)) {        /* ��[11:8]λ����ä��ʱ��     */
      *pdata++  = 1 ;
    }
    else {
      *pdata++ = 0 ;
    }
    tmp = tmp << 1;                 /* ����һλ                   */
  }

  tmp = pCfg->PulseCounter;
  for (i = 12;i < 14;i++)
  {                               /* ��[13:12]λ�����������    */
    if(0x02 == (tmp & 0x02))
    {
      *pdata++ = 1 ;
    }
    else
    {
      *pdata++ = 0 ;
    }
    tmp = tmp << 1;         /* ����һλ                   */
  }

  tmp = pCfg->WindowTime;
  for (i = 14;i < 16;i++)                   /* ��[15:14]λ���ô���ʱ��    */
  {
    if (0x02 == (tmp & 0x02))
    {
      *pdata++ = 1 ;
    }
    else
    {
      *pdata++ = 0 ;
    }
    tmp = tmp << 1;               /* ����һλ                   */
  }
  *pdata++ = pCfg->MotionDetect;
  *pdata++ = pCfg->InterruptSource;

  tmp = pCfg->ADCVoltageSource;
  for(i = 18; i < 20; ++i)
  {
    if (0x02 == (tmp & 0x02))
    {
      *pdata++ = 1 ;
    }
    else
    {
      *pdata++ = 0 ;
    }
    tmp = tmp << 1;               /* ����һλ                   */
  }
  *pdata++ = pCfg->SupplyRegulator;
  *pdata++ = pCfg->StartSelfTest;
  *pdata++ = pCfg->SampleCapacitor;
  *pdata++ = 0;
  *pdata++ = 0;
  WriteE93196(pHeader);
}

/**
  * @brief
  * @param
  * @retval None
  */
void InitE93196_IO( void )
{
  /* SERIN��ʼ��Ϊ��� */
  SERIN_INIT_OUT();

  /* SERIN��ʼ��Ϊ�͵�ƽ */
  SERIN_OFF();

  /* DICO��ʼ��Ϊ���*/
  DOCI_INIT_OUT();
}
/**........................
  * @brief
  * @param
  * @retval None
  */
unsigned char ReadIntputBit(unsigned char Port , unsigned char Pin)
{
  unsigned char bit;
  if((Port&Pin) == 0 )
    bit = 0;
  else
    bit = 1;
  return  bit;
}
/**
  * @brief
  * @param
  * @retval None
  */
void ReadE93196(unsigned char * ptr, unsigned char num)
{
  DOCI_INIT_OUT();                                      /*!<  DICO��ʼ��Ϊ���        */
  DOCI_ON();                                            /*!<  ǿ�����߹ܽ�һ��ʱ��    */
  Delay(65);                                           /*!<  ������ʱ����ڵ���65us  */
  DOCI_OFF();
  for(unsigned char  n = 0; n < num; ++n)
  {
    Delay(1);
    DOCI_ON();                                          /*!<  ����������      */
    DOCI_PULLUP();
    DOCI_INIT_IN();                                     /*!<  �ȴ�оƬ�ı����ߵ�ƽ */
    Delay(1);
    *(ptr+n) = ReadIntputBit(GPIO_PBIN,PORTB_PIN(3))+'0';    /*!<  ��ȡһλ����    */
    Delay(1);
    DOCI_INIT_OUT();
    DOCI_OFF();                                         /*!<  ��DOCI��Ϊ�͵�ƽ*/
  }
  Delay(125);                                        /*!<  ������ʱ����ڵ���125us  */
  DOCI_INIT_IN();                                       /*!<  DICO��ʼ��Ϊ����*/
}
/**
  * @brief
  * @param
  * @retval None
  */
void WriteE93196( uint8_t* ptr )
{
  for (uint8_t i = 0; i < 25; ++i)   /*!<  ѭ��д��25λ���� */
  {
    SERIN_OFF();
    Delay(WAIT_FOR_4_5US);
    SERIN_ON();
    Delay(WAIT_FOR_4_5US);
    if(*ptr++)
    {
      SERIN_ON();
    }else{
      SERIN_OFF();
    }
    Delay(WAIT_FOR_100US);
  }
  SERIN_OFF();
  emberAfAppPrintln("Data is finsihed!");
  Delay(WAIT_FOR_600US);
}


/**
  * @brief
  * @param
  * @retval None
  */
//static void Delay (uint16 usec)
//{
//  while (usec--){
//    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
//    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
//    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
//    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
//    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
//    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
//    asm("nop");asm("nop");
//  }
//}

static void Delay (uint16_t usec)
{
  while (usec--){
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");asm("nop");
  }
}

void ConfigE93196Cfg(E93196Cmd_t *pCmd)
{
  E93196Cfg.Sensitivity = pCmd->Sensitivity;
  E93196Cfg.BlindTime = ((pCmd->BlindTime)/5-1);
  E93196Cfg.PulseCounter = (pCmd->PulseCounter - 1);
  E93196Cfg.WindowTime = (pCmd->WindowTime/4 -1);
  E93196Cfg.MotionDetect = MotionEnable;
  E93196Cfg.InterruptSource = InterruptSource_Motion;
  E93196Cfg.ADCVoltageSource = ADCInputSource_LPF;
  E93196Cfg.SupplyRegulator = Enable;
  E93196Cfg.StartSelfTest = Enable;
  E93196Cfg.SampleCapacitor = 1;
  WriteE93196Cfg(&E93196Cfg);
}
void PIR_ClearDefence(void)
{
  /* ��ֹ PIR�ж�*/
  DOCI_DISABLE_INTERRUPT();
  /* �ر�PIR��Դ*/
  E93196Cfg.Sensitivity = E93196DefaultCmd.Sensitivity;
  E93196Cfg.BlindTime = ((E93196DefaultCmd.BlindTime)/5-1);
  E93196Cfg.PulseCounter = (E93196DefaultCmd.PulseCounter - 1);
  E93196Cfg.WindowTime = (E93196DefaultCmd.WindowTime/4 -1);
  E93196Cfg.MotionDetect = MotionEnable;
  E93196Cfg.InterruptSource = InterruptSource_Motion;
  E93196Cfg.ADCVoltageSource = ADCInputSource_LPF;
  E93196Cfg.SupplyRegulator = Disable;
  E93196Cfg.StartSelfTest = Enable;
  E93196Cfg.SampleCapacitor = 1;
  WriteE93196Cfg(&E93196Cfg);
}

void PIR_SetDefence(void)
{
  InitE93196_IO();
  /* ��ʼ��E931.96�����жϣ���ʹ��P0.4/INT_DOCI�����ж�*/
  //InitE93196Interrupt();

  /* ���ù���ģʽ*/
  ConfigE93196Cfg(&E93196DefaultCmd);

  //DOCI_ENABLE_INTERRUPT();
  /*�����ȷ���ж�״̬*/
  //ClearE93196Interrupt();
}

/******************* (C) COPYRIGHT 2015 WuLianGroup ********END OF FIL*********/ 

