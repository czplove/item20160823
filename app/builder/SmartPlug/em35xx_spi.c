/**
  ******************************************************************************
  * @file    em35xx_spi.c
  * @author  Wireless Protocol Stack Develop-Dept.
  * @version V0.1.0
  * @date    2016/3/17
  * @brief  This file Contain em35xx SPI Interface Service
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
#include PLATFORM_HEADER
#include "hal/micro/micro.h"
#include "hal/micro/cortexm3/memmap.h"
#include BOARD_HEADER
#include "em35xx_spi.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
// Initialization constants.  For more detail on the resulting waveforms,
// see the EM35x datasheet.
#define SPI_ORD_MSB_FIRST       (0<<SC_SPIORD_BIT) // Send the MSB first
#define SPI_ORD_LSB_FIRST       (1<<SC_SPIORD_BIT) // Send the LSB first

#define SPI_PHA_FIRST_EDGE      (0<<SC_SPIPHA_BIT)  // Sample on first edge
#define SPI_PHA_SECOND_EDGE     (1<<SC_SPIPHA_BIT) // Sample on second edge

#define SPI_POL_RISING_LEAD     (0<<SC_SPIPOL_BIT) // Leading edge is rising
#define SPI_POL_FALLING_LEAD    (1<<SC_SPIPOL_BIT) // Leading edge is falling

#if    !defined(EM35XX_SPI_RATE_LINEAR)       \
    || !defined(EM35XX_SPI_RATE_EXPONENTIAL)

  #if    defined(EM35XX_SPI_RATE_LINEAR)      \
      || defined(EM35XX_SPI_RATE_EXPONENTIAL)

    #error Partial Flash serial rate definition. Please define both \

  #endif

  // configure for fastest allowable rate
  // rate = 12 MHz / ((LIN + 1) * (2^EXP))
  #define EM35XX_SPI_RATE_LINEAR  (2)     // 1MHz - FOR MAX71020

  #define EM35XX_SPI_RATE_EXPONENTIAL  (2)

#endif

#if EM35XX_SPI_RATE_LINEAR < 0 || EM35XX_SPI_RATE_LINEAR > 15
  #error EM35XX_SPI_RATE_LINEAR must be between 0 and 15 (inclusive)
#endif

#if EM35XX_SPI_RATE_EXPONENTIAL < 0 || EM35XX_SPI_RATE_EXPONENTIAL > 15
  #error EM35XX_SPI_RATE_EXPONENTIAL must be between 0 and 15 (inclusive)
#endif
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void EM35XX_SPI_Configure(void)
{
  //-----SPI Master SCx configuration
  EM35XX_SPI_SCx_RATELIN = EM35XX_SPI_RATE_LINEAR;
  EM35XX_SPI_SCx_RATEEXP = EM35XX_SPI_RATE_EXPONENTIAL;
  EM35XX_SPI_SCx_SPICFG  = 0;
  EM35XX_SPI_SCx_SPICFG  = (1 << SC_SPIMST_BIT)|  // 4; master control bit
                          (SPI_ORD_MSB_FIRST | SPI_PHA_FIRST_EDGE | SPI_POL_RISING_LEAD);
  EM35XX_SPI_SCx_MODE    = EM35XX_SPI_SCx_MODE_SPI;
}

uint8_t EM35XX_SPI_Exchange(uint8_t byte)
{
  while( (EM35XX_SPI_SCx_SPISTAT&SC_SPITXIDLE) != SC_SPITXIDLE ) {
    // wait for space available
  }
  EM35XX_SPI_SCx_DATA = byte;

  while( (EM35XX_SPI_SCx_SPISTAT&SC_SPIRXVAL) != SC_SPIRXVAL ) {
    // wait for byte to be avail
  }
  return EM35XX_SPI_SCx_DATA;
}
/******************* (C) COPYRIGHT 2016 WuLianGroup ********END OF FIL*********/

