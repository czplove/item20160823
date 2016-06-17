/**
  ******************************************************************************
  * @file    em35xx_spi.h
  * @author  Wireless Protocol Stack Develop-Dept.
  * @version V0.1.0
  * @date    2016/3/21,yuzz
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _EM35XX_SPI_H
#define	_EM35XX_SPI_H

/* Includes ------------------------------------------------------------------*/
#include PLATFORM_HEADER
#include "hal/micro/micro.h"
#include "hal/micro/cortexm3/memmap.h"
#include BOARD_HEADER
#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
// Default to old behavior
#ifndef EM35XX_SPI_SERIAL_CONTROLLER
  #ifdef SPI_FLASH_SC1
    #define EM35XX_SPI_SERIAL_CONTROLLER  1
  #else
    #define EM35XX_SPI_SERIAL_CONTROLLER  2
  #endif
#endif
/* Exported macro ------------------------------------------------------------*/

// only serial controllers 1 through 4 are valid
#if !(    EM35XX_SPI_SERIAL_CONTROLLER >= 1 \
       && EM35XX_SPI_SERIAL_CONTROLLER <= 4 )
  #error "EM35XX_SPI_SERIAL_CONTROLLER out of range (1-4)."
#endif

// only serial controllers actually present on the micro are valid
#if (EMBER_MICRO_SERIAL_CONTROLLERS_MASK & (1 << (EM35XX_SPI_SERIAL_CONTROLLER - 1))) == 0

  #error EM35XX_SPI_SERIAL_CONTROLLER specifies an invalid serial \
         controller for this micro.

#endif

// Abstract away registers to make access serial controller agnostic
#if EM35XX_SPI_SERIAL_CONTROLLER == 1

  // GPIO assignments (SC1)
  // PB1: SC1MOSI / SC1SDA
  // PB2: SC1MISO / SC1SCL
  // PB3: SC1SCLK

  #if    !(EMBER_MICRO_PORT_B_GPIO & PB1) \
      || !(EMBER_MICRO_PORT_B_GPIO & PB2) \
      || !(EMBER_MICRO_PORT_B_GPIO & PB3) \
      || !(EMBER_MICRO_PORT_B_GPIO & PB4)

    #error EM35XX_SPI_SERIAL_CONTROLLER requires invalid GPIO for this micro.

  #endif

  #define EM35XX_SPI_SCx_DATA        SC1_DATA
  #define EM35XX_SPI_SCx_MODE        SC1_MODE
  #define EM35XX_SPI_SCx_RATELIN     SC1_RATELIN
  #define EM35XX_SPI_SCx_RATEEXP     SC1_RATEEXP

  #define EM35XX_SPI_MOSI_PIN        PORTB_PIN(1) // PB1
  #define EM35XX_SPI_MISO_PIN        PORTB_PIN(2) // PB2
  #define EM35XX_SPI_SCLK_PIN        PORTB_PIN(3) // PB3

  #define EM35XX_SPI_SCx_MODE_SPI    SC1_MODE_SPI
  #define EM35XX_SPI_SCx_SPISTAT     SC1_SPISTAT
  #define EM35XX_SPI_SCx_SPICFG      SC1_SPICFG

  #define EM35XX_SPI_SDA_PIN         PORTB_PIN(1) // PB1
  #define EM35XX_SPI_SCL_PIN         PORTB_PIN(2) // PB2

  #define EM35XX_SPI_SCx_MODE_I2C    SC1_MODE_I2C
  #define EM35XX_SPI_SCx_TWISTAT     SC1_TWISTAT
  #define EM35XX_SPI_SCx_TWICTRL1    SC1_TWICTRL1
  #define EM35XX_SPI_SCx_TWICTRL2    SC1_TWICTRL2

#elif EM35XX_SPI_SERIAL_CONTROLLER == 2

  // GPIO assignments (SC2)
  // PA0: SC2MOSI
  // PA1: SC2MISO / SC2SDA
  // PA2: SC2SCLK / SC2SCL
  // PA3: SC2 chip select

  #if    !(EMBER_MICRO_PORT_A_GPIO & PA0) \
      || !(EMBER_MICRO_PORT_A_GPIO & PA1) \
      || !(EMBER_MICRO_PORT_A_GPIO & PA2) \
      || !(EMBER_MICRO_PORT_A_GPIO & PA3)

    #error EM35XX_SPI_SERIAL_CONTROLLER requires invalid GPIO for this micro.

  #endif

  #define EM35XX_SPI_SCx_DATA        SC2_DATA
  #define EM35XX_SPI_SCx_MODE        SC2_MODE
  #define EM35XX_SPI_SCx_RATELIN     SC2_RATELIN
  #define EM35XX_SPI_SCx_RATEEXP     SC2_RATEEXP

  #define EM35XX_SPI_MOSI_PIN        PORTA_PIN(0) // PA0
  #define EM35XX_SPI_MISO_PIN        PORTA_PIN(1) // PA1
  #define EM35XX_SPI_SCLK_PIN        PORTA_PIN(2) // PA2

  #define EM35XX_SPI_SCx_MODE_SPI    SC2_MODE_SPI
  #define EM35XX_SPI_SCx_SPICFG      SC2_SPICFG
  #define EM35XX_SPI_SCx_SPISTAT     SC2_SPISTAT

  #define EM35XX_SPI_SDA_PIN         PORTA_PIN(1) // PA1
  #define EM35XX_SPI_SCL_PIN         PORTA_PIN(2) // PA2

  #define EM35XX_SPI_SCx_MODE_I2C    SC2_MODE_I2C
  #define EM35XX_SPI_SCx_TWISTAT     SC2_TWISTAT
  #define EM35XX_SPI_SCx_TWICTRL1    SC2_TWICTRL1
  #define EM35XX_SPI_SCx_TWICTRL2    SC2_TWICTRL2
#endif
/* Exported functions ------------------------------------------------------- */
extern void EM35XX_SPI_Configure(void);
extern uint8_t EM35XX_SPI_Exchange(uint8_t byte);
#endif /* _EM35XX_SPI_H */
/******************* (C) COPYRIGHT 2016 WuLianGroup ********END OF FIL*********/
