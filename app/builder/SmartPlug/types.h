/**
  ******************************************************************************
  * @file    types.h
  * @author  Wireless Protocol Stack Develop-Dept.
  * @version --
  * @date    2016/3/21,yuzz
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TYPES_H
#define	_TYPES_H
/* Includes ------------------------------------------------------------------*/
#if defined(CORTEXM3_EMBER_MICRO)
#include "hal/micro/cortexm3/compiler/iar.h"
#elif defined(HAL_MCU_CC2530)
#include "hal_types.h"
#endif
#ifdef __cplusplus
extern "C" {
#endif
/* Exported types ------------------------------------------------------------*/
#if defined(CORTEXM3_EMBER_MICRO)


typedef int8u INT8U;
typedef int8s INT8S;
typedef int16u INT16U;
typedef int16s INT16S;
typedef int32u INT32U;
typedef int32s INT32S;
typedef int64u INT64U;
typedef int64s INT64S;
typedef boolean BOOL;

#elif defined(HAL_MCU_CC2530)

typedef int8 INT8S;
typedef uint8 INT8U;
typedef int16 INT16S;
typedef uint16 INT16U;
typedef int32 INT32S;
typedef uint32 INT32U;
typedef bool BOOL;

/* ----------- IAR Compiler ----------- */
#ifdef __IAR_SYSTEMS_ICC__
#define  CODE   __code
#define  XDATA  __xdata
#define ASM_NOP    asm("NOP")

/* ----------- KEIL Compiler ----------- */
#elif defined __KEIL__
#define  CODE   code
#define  XDATA  xdata
#define ASM_NOP   __nop()

/* ----------- CCS Compiler ----------- */
#elif defined __TI_COMPILER_VERSION
#define ASM_NOP    asm(" NOP")

/* ----------- GNU Compiler ----------- */
#elif defined __GNUC__
#define ASM_NOP __asm__ __volatile__ ("nop")

/* ---------- MSVC compiler ---------- */
#elif _MSC_VER
#define ASM_NOP __asm NOP

/* ----------- Unrecognized Compiler ----------- */
#else
#error "ERROR: Unknown compiler."
#endif
#endif
/* Exported constants --------------------------------------------------------*/
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* _TYPES_H */
/******************* (C) COPYRIGHT 2016 WuLianGroup ********END OF FIL*********/
