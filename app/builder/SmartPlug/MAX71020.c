/**
  ******************************************************************************
  * @file    MAX71020.c
  * @author  Wireless Protocol Stack Develop-Dept.
  * @version V0.1.0
  * @date    2016/3/12,yuzz
  * @brief  This file
  *
  * @verbatim
  *
  ******************************************************************************
  * @attention
  *
  *
  *
  * <h2><center>&copy; COPYRIGHT 2016 WuLianGroup</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include "MAX71020.h"
#include "app/framework/include/af.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAX71020_AFE_READ               0x01
#define MAX71020_AFE_WRITE              0x00
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
INT8U Transbuffer[sizeof(MAX71020_AFE_TransBuffer_t)];
MAX71020_AFE_Metering_t MeteringData;
MAX71020_AFE_MeteringPara_t MeteringPara;
/* Private function prototypes -----------------------------------------------*/
static INT8U MAX71020_AFE_Read(INT16U addr ,INT32U* data);
static INT8U MAX71020_AFE_Write(INT16U addr, INT32U value);
static void MAX71020_AFE_AddressTranslation(INT8U rd,INT16U addr);
INT16U Register[] = {/*0x010,0x011,0x013,0x014,0x015,0x01A,0x01B,0x01C,0x01D,0x01E,0x020,*/0x090/*,0x085*/};
//static INT32U MAX71020_AFE_GetPower(void);
/* Public functions ----------------------------------------------------------*/
/*******************************************************************************
  * @fun    MAX71020_AFE_ResetDefault
  * @brief  Reset the MAX71020 chip.
  *
  * @param  void
  *
  * @retval void
  ******************************************************************************/

void MAX71020_AFE_ResetDefault(void)
{
  INT32U defaultValue;
  EM35XX_SPI_Configure();
  MAX71020_AFE_RESETZ();
  MAX71020_AFE_Write(0x010,0x00004000);   /* cal_i0 */
  MAX71020_AFE_Write(0x011,0x00004000);   /* cal_V0 */
  MAX71020_AFE_Write(0x012,0x00000000);   /*Calibrated I/V Phase Adjustment*/
  MAX71020_AFE_Write(0x013,0x00000000);   /* Calibrated DC offset I */
  MAX71020_AFE_Write(0x014,0x00000000);   /* Calibrated DC offset V *//*!< 111 */
  MAX71020_AFE_Write(0x015,0x0000024D);   /*Nominal Temperature reading  589*/

  MAX71020_AFE_Write(0x016,0x00000040);   /* Can be set to scale IRMS output */
  MAX71020_AFE_Write(0x017,0x00004000);   /* Can be set to scale VRMS output */
  MAX71020_AFE_Write(0x018,0x00004000);   /* Can be set to scale Watts output */

  MAX71020_AFE_Write(0x01A,0x00006A8F);   //DEGSCALE

  /* Set-up default temperature compensation. */
  MAX71020_AFE_Read(0x1d,&defaultValue);
  MAX71020_AFE_Write(0x1b,defaultValue);

  MAX71020_AFE_Read(0x1e,&defaultValue);
  MAX71020_AFE_Write(0x1c,defaultValue);

  MAX71020_AFE_Write(0x20,0x40105D00);  /* 50hz sag_cnt、 pulse-slow = 0、 pulse-fast = 0*/
  MAX71020_AFE_Write(0x21,0x000009DF);  /* WRATE: Kh = 1Wh/10   脉冲常数为10000*/
  MAX71020_AFE_Write(0x22,0x00001929);

  MAX71020_AFE_Write(0x24,0x0D6783B6);  /* Voltage threshold for sag warnings  150V*/
  MAX71020_AFE_Write(0x25,0x00000000);
  MAX71020_AFE_Write(0x26,0x00000000);
  MAX71020_AFE_Write(0x27,0x00000000);
  MAX71020_AFE_Write(0x28,0x00000000);
  MAX71020_AFE_Write(0x29,0x00001000);

  MAX71020_AFE_Write(0x305,0x00006300);//{ ADC_DIV=1, PLL_FAST=1, SUM_SAMPS=768=3072/4}
  MAX71020_AFE_Write(0x306,0x0000000D);//{ SLEN = 13 (S-slot length = SLEN+3 = 16) }
  MAX71020_AFE_Write(0x307,0x000000FA);

  MAX71020_AFE_Write(0x308,0xF4F9F004);
  MAX71020_AFE_Write(0x30C,0x0050000F);//DIO   [23:22] 01: YPULSE [21:20] 01:XPULSE
  MAX71020_AFE_Write(0x30D,0x00000500); //DIFF0_E/[8]= 1 (differential ADC0-1), no pre-amp

  MAX71020_AFE_Write(0x30E,0x00000000);
  MAX71020_AFE_Write(0x30F,0x00000010);//IE_XDATA
  MAX71020_AFE_Write(0x323,0x00000004);//TEMP_PER=1 (update temperature every accumulation cycle)
  MAX71020_AFE_Write(0x326,0x00000003);//ADC_E, CE_E=1
}


void MAX71020_AFE_WriteRead(void)
{
  INT32U DefaultValue;
  //MAX71020_AFE_Write(0x011,0x12345678);   /* cal_V0 */
  for(INT16U i = 0 ; i< sizeof(Register)/2 ;i++)
    MAX71020_AFE_Read(Register[i],&DefaultValue);

  emberAfSimpleMeteringClusterPrintln("              ");
}
/*******************************************************************************
  * @fun    MAX71020_AFE_SetDefaultMeteringPara
  * @brief  Set Default Metering Parameter
  *
  * @param  MAX71020_AFE_MeteringPara_t *pMeterPara
  *
  * @retval None
  ******************************************************************************/
void MAX71020_AFE_SetDefaultMeteringPara(MAX71020_AFE_MeteringPara_t *pMeterPara)
{
  pMeterPara->accuEnergy   = 0x00000000;
  pMeterPara->cal_I0       = 0x00004000;
  pMeterPara->cal_V0       = 0x00004000;
  pMeterPara->phadj_0      = 0x00000000;
  pMeterPara->wrate        = 0x000009DF;
  pMeterPara->sagThr       = 0x0D6783B6;
  pMeterPara->ceConfig     = 0x40105D00;
  pMeterPara->energyPre    = 0x00000000;
  MAX71020_AFE_WriteMeteringPara(pMeterPara);
}

/*******************************************************************************
  * @fun    MAX71020_AFE_WriteMeteringPara
  * @brief  Write the Metering parameter to the MAX71020 chip.
  *
  * @param  MAX71020_AFE_MeteringPara_t *pMeterPara
  *
  * @retval None
  ******************************************************************************/
void MAX71020_AFE_WriteMeteringPara(MAX71020_AFE_MeteringPara_t *pMeterPara)
{
  MAX71020_AFE_Write(0x045,0x00000000);                     //累计用电量值

  MAX71020_AFE_Write(0x010,pMeterPara->cal_I0);             //电流校准值

  MAX71020_AFE_Write(0x011,pMeterPara->cal_V0);             //电压校准值

  MAX71020_AFE_Write(0x012,pMeterPara->phadj_0);            //相位校准值

  MAX71020_AFE_Write(0x021,pMeterPara->wrate);              //脉冲常数---固定为10000，不做更改

  MAX71020_AFE_Write(0x024,pMeterPara->sagThr);             //低电压阀值

  MAX71020_AFE_Write(0x020,pMeterPara->ceConfig);           //频率值
}
/*******************************************************************************
  * @fun    MAX71020_AFE_RestoreMeteringPara
  * @brief  Restore Metering parameter from flash to the MAX71020 chip.
  *
  * @param  MAX71020_AFE_MeteringPara_t *pMeterPara
  *
  * @retval None
  ******************************************************************************/
void MAX71020_AFE_RestoreMeteringPara(MAX71020_AFE_MeteringPara_t *pMeterPara)
{
  INT8U* p = (INT8U*)pMeterPara;
  INT16U sumCheck = 0;

  MAX71020_NV_READ(sizeof(MAX71020_AFE_MeteringPara_t),(INT8U*)pMeterPara);

  for(INT8U i = 0; i < sizeof(MAX71020_AFE_MeteringPara_t)-2; i++)
    sumCheck += *p++;

  if(pMeterPara->rev != 0x90EB || pMeterPara->sumCheck != sumCheck)
  {
    MAX71020_AFE_SetDefaultMeteringPara(pMeterPara);
    MAX71020_AFE_StoreMeteringPara(pMeterPara);
    return ;
  }
  if(pMeterPara->energyPre)
  pMeterPara->accuEnergy = pMeterPara->energyPre;
  MAX71020_AFE_StoreMeteringPara(pMeterPara);
  MAX71020_AFE_WriteMeteringPara(pMeterPara);
}
/*******************************************************************************
  * @fun    MAX71020_AFE_StoreMeteringPara
  * @brief  Store Metering parameter to flash.
  *
  * @param  MAX71020_AFE_MeteringPara_t *pMeterPara
  *
  * @retval None
  ******************************************************************************/
void MAX71020_AFE_StoreMeteringPara(MAX71020_AFE_MeteringPara_t *pMeterPara)
{
  INT8U* p = (INT8U*)pMeterPara;
  pMeterPara->rev = 0x90EB;
  pMeterPara->sumCheck = 0;
  for(INT8U i = 0; i < sizeof(MAX71020_AFE_MeteringPara_t)-2; ++i)
    pMeterPara->sumCheck += *p++;

  MAX71020_NV_WRITE(sizeof(MAX71020_AFE_MeteringPara_t),(INT8U*)pMeterPara);
}
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
  * @fun    MAX71020_AFE_GetAccumulatePower
  * @brief  Get Accumulate Power
  *
  * @param  void
  *
  * @retval INT32U unit 100mWh
  ******************************************************************************/
INT32U MAX71020_AFE_GetAccumulatePower(void)
{
  INT32U accupower;

  MAX71020_AFE_Read(MAX71020_AFE_WPULSE_CTR,&accupower);

  return accupower;
}

/*******************************************************************************
  * @fun    MAX71020_AFE_GetVoltage
  * @brief  Read the current power supply voltage RMS
  *
  * @param  void
  *
  * @retval INT32U unit 1mV
  ******************************************************************************/
INT32U MAX71020_AFE_GetVoltage(void)
{
  INT32U voltage;

  MAX71020_AFE_Read(MAX71020_AFE_V0SQSUM_X,&voltage);

  voltage = (INT32U)(1000*(MAX71020_AFE_VMAX*MAX71020_AFE_C_SQRT_SAMPS*sqrt(voltage)));

  return voltage;
}
/*******************************************************************************
  * @fun    MAX71020_AFE_GetCurrent
  * @brief  Read the current power supply current RMS
  *
  * @param  void
  *
  * @retval INT32U unit 1mA
  ******************************************************************************/
INT32U MAX71020_AFE_GetCurrent(void)
{
  INT32U current;
  INT32U rescurrent;

  MAX71020_AFE_Read(MAX71020_AFE_I0SQSUM_X,&current);
  MAX71020_AFE_Read(MAX71020_AFE_I0SQRES_X,&rescurrent);

  current = (INT32U)(1000*(MAX71020_AFE_IMAX*MAX71020_AFE_C_SQRT_SAMPS*
                          sqrt(((float)rescurrent/2048)+current)));
  return current;
}
/*******************************************************************************
  * @fun    MAX71020_AFE_GetPower
  * @brief  Get active power
  *
  * @param  void
  *
  * @retval INT32U unit 1mW
  ******************************************************************************/
INT32U MAX71020_AFE_GetPower(void)
{
  INT32S powerdata;
  INT32U power;

  MAX71020_AFE_Read(MAX71020_AFE_W0SUM_X,(INT32U*)&powerdata);

  power = (INT32U)(1000*(MAX71020_AFE_VMAX*MAX71020_AFE_IMAX*MAX71020_AFE_C_SAMPS*fabs(powerdata)));

  return power;
}
/*******************************************************************************
  * @fun    MAX71020_AFE_GetAllMeteringData
  * @brief  Get Metering data
  *
  * @param  void
  *
  * @retval INT32U unit 100mW
  ******************************************************************************/
MAX71020_AFE_Metering_t* MAX71020_AFE_GetAllMeteringData(void)
{
  MAX71020_AFE_Metering_t *pMeter = &MeteringData;
  pMeter->voltage = MAX71020_AFE_GetVoltage();
  pMeter->current = MAX71020_AFE_GetCurrent();
  pMeter->power = MAX71020_AFE_GetPower();
  pMeter->accupower = (INT32U)(MAX71020_AFE_GetAccumulatePower())+ MeteringPara.accuEnergy;
  if(pMeter->accupower >= 16000000)
  {
    pMeter->accupower = 0;
    MeteringPara.accuEnergy = 0;
    MAX71020_AFE_StoreMeteringPara(&MeteringPara);
  }
  MeteringPara.energyPre = pMeter->accupower;
  MAX71020_AFE_StoreMeteringPara(&MeteringPara);
  return pMeter;
}
/*******************************************************************************
  * @fun    MAX71020_AFE_Read
  * @brief  Read 32 bit data from MAX71020 Register.
  *
  * @param  INT16U addr
  * @param  INT32U* data
  *
  * @retval INT8U
  ******************************************************************************/
static INT8U MAX71020_AFE_Read(INT16U addr ,INT32U* data)
{
  MAX71020_AFE_AddressTranslation(MAX71020_AFE_READ,addr);

  INT8U *pdata = ((MAX71020_AFE_TransBuffer_t*)Transbuffer)->data;

  ((MAX71020_AFE_TransBuffer_t*)Transbuffer)->status = 0x00;

  UINT32_TO_BUF_BIG_ENDIAN(pdata,0);

  MAX71020_CSActive();

  for(INT8U i = 0; i < sizeof(MAX71020_AFE_TransBuffer_t); ++i)
  {
      Transbuffer[i] = SPI_Exchange(Transbuffer[i]);
  }
  MAX71020_CSInactive();

  pdata = ((MAX71020_AFE_TransBuffer_t*)Transbuffer)->data;

  *data = BUF_TO_UINT32_BIG_ENDIAN(pdata);

//  emberAfSimpleMeteringClusterPrintln("Register Addr 0x%2x  Value 0x%4x",addr ,*data);

  return ((MAX71020_AFE_TransBuffer_t*)Transbuffer)->status;
}
/*******************************************************************************
  * @fun    MAX71020_AFE_Write
  * @brief  Write 32 bit data to MAX71020 Register.
  *
  * @param  INT16U addr
  * @param  INT32U value
  *
  * @retval INT8U
  ******************************************************************************/
static INT8U MAX71020_AFE_Write(INT16U addr, INT32U value)
{
  MAX71020_AFE_AddressTranslation(MAX71020_AFE_WRITE,addr);

  INT8U* pdata = ((MAX71020_AFE_TransBuffer_t*)Transbuffer)->data;

  ((MAX71020_AFE_TransBuffer_t*)Transbuffer)->status = 0x00;

  UINT32_TO_BUF_BIG_ENDIAN(pdata,value);

  MAX71020_CSActive();

  for(INT8U i = 0; i < sizeof(MAX71020_AFE_TransBuffer_t); ++i)
    Transbuffer[i] = SPI_Exchange(Transbuffer[i]);

  MAX71020_CSInactive();

  return ((MAX71020_AFE_TransBuffer_t*)Transbuffer)->status;
}
/*******************************************************************************
  * @fun    MAX71020_AFE_AddressTranslation
  * @brief  Translate the Register to SPI Write/Read Mode.
  *
  * @param  INT8U rd  MAX71020_AFE_READ if Read data from MAX71020 else MAX71020_AFE_WRITE
  * @param  INT16U addr 16-bit MAX71020 Register address.
  *
  * @retval None
  ******************************************************************************/
static void MAX71020_AFE_AddressTranslation(INT8U rd , INT16U addr)
{
  INT16U address1, address2;
  INT8U* p = ((MAX71020_AFE_TransBuffer_t*)Transbuffer)->addr;

  if(rd)
    address1 = addr<<5 |0x10;
  else
    address1 = addr<<5;
  address2 = ~address1;

  *p++ = address1>>8 & 0xFF;
  *p++ = (address1&0xF0)|(address2>>12 &0x0F);
  *p++ = address2>>4 & 0xFF;
}
/******************* (C) COPYRIGHT 2015 WuLianGroup ********END OF FIL*********/