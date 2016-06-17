/**
  ******************************************************************************
  * @file    MAX71020.h
  * @author  Wireless Protocol Stack Develop-Dept.
  * @version V0.1.0
  * @date    2016/3/12,yuzz
  * @brief  This file contain the Maxim MAX71020 Single-Chip Electricity Meter
  * 		AFE Interface Service.
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

/* Define to prevent recursive inclusion -------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include "hal_defs.h"

#ifndef _MAX71020_H
#define	_MAX71020_H

#ifdef __cplusplus
extern "C" {
#endif
/* Exported types ------------------------------------------------------------*/
typedef struct
{
  INT8U addr[3];
  INT8U status;
  INT8U data[4];
}MAX71020_AFE_TransBuffer_t;

typedef struct
{
  INT32U accupower;
  INT32U current;
  INT32U voltage;
  INT32U power;
}MAX71020_AFE_Metering_t;

typedef struct
{
  INT32U accuEnergy;        //The cumulative power consumption
  INT32U cal_I0;            //Calibration coefficient for current channel A.
  INT32U cal_V0;            //Calibration coefficient for voltage channel A.
  INT32U phadj_0;           //Phase adjust coefficient for channel A
  INT32U wrate;             //Sets the meter constant for pulse outputs.
  INT32U sagThr;           //Voltage threshold for sag warnings
  INT32U ceConfig;          //Configuration register for CE operation
  INT32U energyPre;         //The cumulative power consumption last time
  INT16U rev;
  INT16U sumCheck;
}MAX71020_AFE_MeteringPara_t;
/* Exported constants --------------------------------------------------------*/
#define MAX71020_AFE_WPULSE_CTR         0x045 /*!< Pulse counter for Wh (real power) */

#define MAX71020_AFE_WSUM_X             0x084 /*!< Signed sum of real energy (Wh) from both wattmeter
                                                   elements for the previous accumulation interval */
#define MAX71020_AFE_W0SUM_X            0x085 /*!< Signed sum of real energy (Wh) from wattmeter element A */
#define MAX71020_AFE_W1SUM_X            0x086 /*!< Signed sum of real energy (Wh) from wattmeter element B */

#define MAX71020_AFE_VARSUM_X           0x088 /*!< Signed sum of reactive energy (VARh) from both
                                                   wattmeter elements for the previous accumulation interval */
#define MAX71020_AFE_VAR0SUM_X          0x086 /*!< Signed sum of reactive energy (VARh) from wattmeter
                                                   element A */
#define MAX71020_AFE_VAR1SUM_X          0x08a /*!< Signed sum of reactive energy (VARh) from wattmeter
                                                   element B */
#define MAX71020_AFE_I0SQSUM_X          0x08C /*!< Sum of squared samples from current sensor in phase A */
#define MAX71020_AFE_I1SQSUM_X          0x08D /*!< Sum of squared samples from current sensor in phase B */
#define MAX71020_AFE_V0SQSUM_X          0x090 /*!< Sum of squared samples from voltage sensor in phase A */
#define MAX71020_AFE_V1SQSUM_X          0x091 /*!< Sum of squared samples from voltage sensor in phase B */
#define MAX71020_AFE_I0SQRES_X          0x096 /*!< Residual current from current sensor in phase A */
#define MAX71020_AFE_I1SQRES_X          0x097 /*!< Residual current from current sensor in phase B */
#define MAX71020_AFE_I0_RAW             0x100 /*!< Most recent result of ADC conversion for current phase A */
#define MAX71020_AFE_V0_RAW             0x101 /*!< Most recent result of ADC conversion for voltage phase A */
#define MAX71020_AFE_I1_RAW             0x102 /*!< Most recent result of ADC conversion for current phase B */
#define MAX71020_AFE_V1_RAW             0x103 /*!< Most recent result of ADC conversion for voltage phase B */



#define MAX71020_AFE_SUM_SAMPS          3072                    //²ÉÑùÆµÂÊ
#define MAX71020_AFE_C_SQRT_SAMPS       0.000025179             //sqrt(C / SUM_SAMPS)
#define MAX71020_AFE_C_SAMPS            0.000000000634          //C / SUM_SAMPS
#define MAX71020_AFE_VMAX               708.524                 //VMAX
#define MAX71020_AFE_IMAX               88.3883                 //IMAX
/* Exported macro ------------------------------------------------------------*/
#define WL_R0147H

#if defined(WL_R0047H)||defined(WL_R0047L)
#include "hal_mcu.h"
#define MAX71020_AFE_RESETZ_DELAY()   st( { volatile INT32U i; for (i=0; i<88800; i++) { }; } )
#define MAX71020_AFE_RESET_PIN  P0_4
#define MAX71020_AFE_RESETZ()           \
{                                       \
  MAX71020_AFE_RESET_PIN = 0;           \
  MAX71020_AFE_RESETZ_DELAY();          \
  MAX71020_AFE_RESET_PIN = 1;           \
  MAX71020_AFE_RESETZ_DELAY();          \
}
#elif defined(WL_R0147H) || defined(WL_R0147L)
#define MAX71020_AFE_RESETZ_DELAY()   st( { volatile INT32U i; for (i=0; i<888000; i++) { }; } )
#define MAX71020_AFE_RESETZ()           \
{                                       \
  EXTERNAL_MAX71020_RESERZ_ACTIVE();    \
  MAX71020_AFE_RESETZ_DELAY();          \
  EXTERNAL_MAX71020_RESERZ_INACTIVE();  \
  MAX71020_AFE_RESETZ_DELAY();          \
}
#else
#define MAX71020_AFE_RESETZ()
#endif

#if defined(WL_R0047H)||defined(WL_R0047L)
#include "osal_NV.h"
#define ZCD_NV_PARAM_FLASH         0x0501
#define MAX71020_NV_READ(len,pBuf) st({osal_nv_item_init(ZCD_NV_PARAM_FLASH,len,pBuf);osal_nv_read(ZCD_NV_PARAM_FLASH,0,len,pBuf);})
#define MAX71020_NV_WRITE(len,pBuf) st({osal_nv_item_init(ZCD_NV_PARAM_FLASH,len,pBuf);osal_nv_write(ZCD_NV_PARAM_FLASH,0,len,pBuf);})
#define MAX71020_CSActive()         EXTERNAL_MAX71020_CS_ACTIVE()
#define MAX71020_CSInactive()       EXTERNAL_MAX71020_CS_INACTIVE()
#define SPI_Exchange                CC2530_SPI_Exchange
#elif defined(WL_R0147H) || defined(WL_R0147L)
#include PLATFORM_HEADER
#include "stack/include/ember-types.h"
#include "hal/micro/micro-common.h"
#include "hal/micro/cortexm3/micro-common.h"
#include "hal/micro/token.h"
#include GENERATED_TOKEN_HEADER
#include BOARD_HEADER
#include "em35xx_spi.h"
#define MAX71020_NV_READ(len,pBuf)  halCommonGetToken(pBuf,TOKEN_MAX71020_AFE_PARAMTER)
#define MAX71020_NV_WRITE(len,pBuf) halCommonSetToken(TOKEN_MAX71020_AFE_PARAMTER,pBuf)
#define MAX71020_CSActive()         EXTERNAL_MAX71020_CS_ACTIVE()
#define MAX71020_CSInactive()       EXTERNAL_MAX71020_CS_INACTIVE()
#define SPI_Exchange                EM35XX_SPI_Exchange
#else
#define MAX71020_NV_READ(len,pBuf)
#define MAX71020_NV_WRITE(len,pBuf)
#endif

#define UINT32_TO_BUF_BIG_ENDIAN(pBuf,val) \
	do { \
		*(pBuf)++ = ((((INT32U)(val)) >> 24) & 0xFF); \
		*(pBuf)++ = ((((INT32U)(val)) >> 16) & 0xFF); \
		*(pBuf)++ = ((((INT32U)(val)) >>  8) & 0xFF); \
		*(pBuf)++ = ((((INT32U)(val)) >>  0) & 0xFF); \
	} while (0)
#define BUF_TO_UINT32_BIG_ENDIAN(pBuf) (((pBuf) += 4),BUILD_UINT32((pBuf)[-1], (pBuf)[-2], (pBuf)[-3], (pBuf)[-4]))

#define UINT32_TO_BUF_LITTLE_ENDIAN(pBuf,val) \
	do { \
		*(pBuf)++ = ((((INT32U)(val)) >>  0) & 0xFF); \
		*(pBuf)++ = ((((INT32U)(val)) >>  8) & 0xFF); \
		*(pBuf)++ = ((((INT32U)(val)) >> 16) & 0xFF); \
		*(pBuf)++ = ((((INT32U)(val)) >> 24) & 0xFF); \
	} while (0)

#define BUF_TO_UINT32_LITTLE_ENDIAN(pBuf) (((pBuf) += 4), BUILD_UINT32((pBuf)[-4], (pBuf)[-3], (pBuf)[-2], (pBuf)[-1]))

#define UINT48_TO_BUF_LITTLE_ENDIAN(pBuf,val) \
	do { \
		*(pBuf)++ = ((((INT64U)(val)) >>  0) & 0xFF); \
		*(pBuf)++ = ((((INT64U)(val)) >>  8) & 0xFF); \
		*(pBuf)++ = ((((INT64U)(val)) >> 16) & 0xFF); \
		*(pBuf)++ = ((((INT64U)(val)) >> 24) & 0xFF); \
		*(pBuf)++ = ((((INT64U)(val)) >> 32) & 0xFF); \
		*(pBuf)++ = ((((INT64U)(val)) >> 40) & 0xFF); \
	} while (0)

extern MAX71020_AFE_MeteringPara_t MeteringPara;
/* Exported functions ------------------------------------------------------- */
extern INT8U SPI_Exchange(INT8U byte);
extern void MAX71020_AFE_ResetDefault(void);
void MAX71020_AFE_WriteRead(void);
extern INT32U MAX71020_AFE_GetPower(void);
extern INT32U MAX71020_AFE_GetAccumulatePower(void);
extern INT32U MAX71020_AFE_GetVoltage(void);
extern INT32U MAX71020_AFE_GetCurrent(void);
extern MAX71020_AFE_Metering_t* MAX71020_AFE_GetAllMeteringData(void);
extern void MAX71020_AFE_SetDefaultMeteringPara(MAX71020_AFE_MeteringPara_t *pMeterPara);
extern void MAX71020_AFE_WriteMeteringPara(MAX71020_AFE_MeteringPara_t *pMeterPara);
extern void MAX71020_AFE_RestoreMeteringPara(MAX71020_AFE_MeteringPara_t *pMeterPara);
extern void MAX71020_AFE_StoreMeteringPara(MAX71020_AFE_MeteringPara_t *pMeterPara);
#ifdef __cplusplus
}
#endif

#endif /* _MAX71020_H */
/******************* (C) COPYRIGHT 2016 WuLianGroup ********END OF FIL*********/
